#pragma once

#include <iostream>
#include <vector>
#include <time.h>
#include <assert.h>
using std::cout;
using std::endl;

static const size_t MAX_BYTES = 256 * 1024;

void*& NextObj(void* obj)
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

	void*& Pop()
	{
		assert(_freeList);
		// 头删
		void* obj = _freeList;
		_freeList = NextObj(obj);
		return obj;
	}
private:
	void* _freeList;
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


};