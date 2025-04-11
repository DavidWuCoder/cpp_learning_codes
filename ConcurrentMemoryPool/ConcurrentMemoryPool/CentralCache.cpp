#include "CentralCache.h"
#include "PageCache.h"

CentralCache CentralCache::_sInst;

// 从中⼼缓存获取⼀定数量的对象给thread cache
size_t CentralCache::FetchRangeObj(void*& start, void*& end, size_t batchNum, size_t size)
{
	size_t index = SizeClass::Index(size);

	_spanLists[index]._mtx.lock();

	Span* span = GetOneSpan(_spanLists[index], size);
	assert(span);
	assert(span->_freeList);

	// 从span中获取batchNum个对象
	// 如果不够batchNum,就有多少拿多少
	start = span->_freeList;
	end = start;
	size_t i = 0;
	size_t actualNum = 1;
	while ( i < batchNum - 1 && NextObj(end) != nullptr)
	{
		end = NextObj(end);
		i++;
		++actualNum;
	}
	span->_freeList = NextObj(end);
	NextObj(end) = nullptr;

	_spanLists[index]._mtx.unlock();
	
	return actualNum;
}

// 获取⼀个⾮空的span
Span* CentralCache::GetOneSpan(SpanList& list, size_t size)
{
	// 先遍历当前spanlist是否有非空的span
	Span* it = list.Begin();
	while (it != list.End())
	{
		if (it->_freeList != nullptr)
		{
			return it;
		}
		else
		{
			it = it->_next;
		}
	}

	// 先把central cache的桶锁解掉，这样如果其他线程来释放内存对象不需要解掉
	list._mtx.unlock();

	// 走到这里说没有空闲span了，只能找page cache 要
	PageCache::GetInstance()->_pageMtx.lock();
	Span* span = PageCache::GetInstance()->NewSpan(SizeClass::NumMovePage(size));
	PageCache::GetInstance()->_pageMtx.unlock();

	// 切分不需要加锁，因为这会其他线程访问不到这个span
	// 计算span内存的骑士地址和大小（字节数）
	char* start = (char *)(span->_PageId << PAGE_SHIFT);
	size_t bytes = span->_n << PAGE_SHIFT;
	char* end = start + bytes;

	// 把大块内存切成_freeList链接起来
	// 1.先切一块做头节点方便尾插
	span->_freeList = start;
	start += size;
	void* tail = span->_freeList;
	while (start < end)
	{
		NextObj(tail) = start;
		tail = NextObj(tail);
		start += size;
	}

	//  把切好的span挂到队列当中时，需要加锁
	list._mtx.lock();
	list.PushFront(span);

	return span;
}