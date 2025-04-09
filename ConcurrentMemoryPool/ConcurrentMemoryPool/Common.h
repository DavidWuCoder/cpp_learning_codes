#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <time.h>
#include <assert.h>
#include <thread>
#include <mutex>

using std::cout;
using std::endl;

static const size_t MAX_BYTES = 256 * 1024;
static const size_t NFREE_LISTS = 208;

// 注意这里的顺序
// 64位机器会同时定义_WIN64, _WIN32
#ifdef _WIN64
typedef unsigned long long PAGE_ID;
#elif _WIN32
typedef size_t PAGE_ID; 
#endif

static void*& NextObj(void* obj)
{
	return *(void**)obj;
}

// 管理切分好的小对象
class FreeList
{
public:
	void Push(void* obj)
	{
		assert(obj);
		// 头插
		NextObj(obj) = _freeList;
		_freeList = obj;
	}

	void PushRange(void* start, void* end)
	{
		NextObj(end) = _freeList;
		_freeList = start;
	}

	void*& Pop()
	{
		assert(_freeList);
		// 头删
		void* obj = _freeList;
		_freeList = NextObj(obj);
		return obj;
	}

	bool Empty()
	{
		return _freeList == nullptr;
	}

	size_t& MaxSize()
	{
		return _maxSize;
	}
private:
	void* _freeList = nullptr;
	size_t _maxSize = 1;
};


// 计算对象大小的对齐映射规则
class SizeClass
{
public:
	// 整体控制最多在 10% 左右的内碎片浪费
	// [1,128] 8byte对⻬ freelist[0,16)
	// [128+1,1024] 16byte对⻬ freelist[16,72)
	// [1024+1,81024] 128byte对⻬ freelist[72,128)
	// [8*1024+1,641024] 1024byte对⻬ freelist[128,184)
	// [64*1024+1,256*1024] 8*1024byte对⻬ freelist[184,208)

	// 计算应当分配的大小，普通做法
	//size_t _Roundup(size_t size, size_t AlignNum)
	//{
	//	size_t alignSize;
	//	if (size % AlignNum != 0)
	//	{
	//		alignSize = (size / AlignNum + 1) * AlignNum;
	//	}
	//	else
	//	{
	//		alignSize = size;
	//	}
	//	return alignSize;
	//}

	// 计算应当分配的大小，高级做法
	// 
	static inline size_t _Roundup(size_t bytes, size_t AlignNum)
	{
		return ((bytes + AlignNum - 1) & ~(AlignNum - 1));
	}

	static inline size_t RoundUp(size_t size)
	{
		if (size <= 128)
		{
			return _Roundup(size, 8);
		}
		else if (size <= 1024)
		{
			return _Roundup(size, 16);
		}
		else if (size <= 8 * 1024)
		{
			return _Roundup(size, 128);
		}
		else if (size <= 64 * 1024)
		{
			return _Roundup(size, 1024);
		}
		else if (size <= 256 * 1024)
		{
			return _Roundup(size, 8 * 1024);
		}
		else
		{
			assert(false);
		}

	}

	// 计算映射到的桶的索引，普通做法
	//size_t _Index(size_t bytes, size_t AlignNum)
	//{
	//	if (bytes % AlignNum == 0)
	//	{
	//		return bytes / AlignNum - 1;
	//	}
	//	else
	//	{
	//		return bytes / AlignNum;
	//	}
	//}

	// 计算映射到的桶的索引，高级做法
	// align_shift需要传是log_2(对齐数)
	static inline size_t _Index(size_t bytes, size_t align_shift)
	{
		return ((bytes + (1 << align_shift) - 1) >> align_shift) - 1;
	}

	// 计算映射的哪⼀个⾃由链表桶
	static inline size_t Index(size_t bytes)
	{
		assert(bytes <= MAX_BYTES);
		// 每个区间有多少个链
		static int group_array[4] = { 16, 56, 56, 56 };
		if (bytes <= 128) {
			return _Index(bytes, 3);
		}
		else if (bytes <= 1024) {
			return _Index(bytes - 128, 4) + group_array[0];
		}
		else if (bytes <= 81024) {
			return _Index(bytes - 1024, 7) + group_array[1] + group_array[0];
		}
		else if (bytes <= 64 * 1024) {
			return _Index(bytes - 8 * 1024, 10) + group_array[2] +
				group_array[1] + group_array[0];
		}
		else if (bytes <= 256 * 1024) {
			return _Index(bytes - 64 * 1024, 13) + group_array[3] +
				group_array[2] + group_array[1] + group_array[0];
		}
		else {
			assert(false);
		}
		return -1;
	}

	// thead cache⼀次从中⼼缓存获取多少个
	static size_t NumMoveSize(size_t size)
	{
		assert(size > 0);
		// [2, 512]，⼀次批量移动多少个对象的(慢启动)上限值
		// ⼩对象⼀次批量上限⾼
		// ⼩对象⼀次批量上限低
		int num = MAX_BYTES / size;
		if (num < 2)
			num = 2;
		if (num > 512)
			num = 512;
		return num;
	}
};

// 管理多个连续页的内存大块结构
struct Span
{
	PAGE_ID _PageId; // 大块内存起始页面的页号
	size_t n;		 // 页的数量

	Span* _next;	 // 双向链表的结构
	Span* _prev;

	size_t _useCount; // 切好的小块内存，被分配给thread cache的计数
	void* _freeList;  // 切好的小块内存的自由链表
};

class SpanList
{
public:
	SpanList()
	{
		_head = new Span;
		_head->_next = _head;
		_head->_prev = _head;
	}

	void Insert(Span* pos, Span* newSpan)
	{
		assert(pos);
		assert(newSpan);

		Span* prev = pos->_prev;
		prev->_next = newSpan;
		newSpan->_next = pos;
		newSpan->_prev = prev;
		pos->_prev = newSpan;
	}

	void Erase(Span* pos, Span* newSpan)
	{
		assert(pos);
		assert(newSpan);

		Span* prev = pos->_prev;
		Span* next = pos->_next;

		prev->_next = next;
		next->_prev = prev;
	}

private:
	Span* _head = nullptr;

public:
	std::mutex _mtx;
};