#include "ThreadCache.h"
#include "CentralCache.h"

// 申请和释放内存对象
void* ThreadCache::Allocate(size_t size)
{
	assert(size < MAX_BYTES);
	size_t align_size = SizeClass::RoundUp(size);
	size_t index = SizeClass::Index(size);

	if (!_freeLists[index].Empty())
	{
		return _freeLists[index].Pop();
	}
	else
	{
		// 找下一层central cache
		return FetchFromCentralCache(index, align_size);
	}
}

void* ThreadCache::Deallocate(void* ptr, size_t size)
{
	assert(ptr);
	assert(size <= MAX_BYTES);

	// 找对应的链表桶，插入进去
	size_t index = SizeClass::Index(size);
	_freeLists[index].Push(ptr);

	return nullptr;

}


void* ThreadCache::FetchFromCentralCache(size_t index, size_t size)
{
	// 慢开始的反馈调节算法
	// 1.开始不会向central cache申请太多，因为太多了可能用不完
	// 2.这个size大小的内存需求，就会逐渐增长到上限
	// 3. size越大，一次向central cache要的batch就越小，反之亦然
	size_t batchNum = std::min(_freeLists[index].MaxSize(), SizeClass::NumMoveSize(size));
	//size_t batchNum = std::min(1, 2);
	if (_freeLists[index].MaxSize() == batchNum)
	{
		_freeLists[index].MaxSize() += 1;
	}

	void* start = nullptr;
	void* end = nullptr;

	size_t actualNum = CentralCache::GetInstance()->FetchRangeObj(start, end, batchNum, size);
	assert(actualNum > 1);

	if (actualNum == 1)
	{
		assert(start == end);

		return start;
	}
	else
	{
		_freeLists[index].PushRange(NextObj(start), end);
		return start;
	}
}

