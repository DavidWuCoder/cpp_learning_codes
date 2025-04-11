#include "ThreadCache.h"
#include "CentralCache.h"

// ������ͷ��ڴ����
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
		// ����һ��central cache
		return FetchFromCentralCache(index, align_size);
	}
}

void* ThreadCache::Deallocate(void* ptr, size_t size)
{
	assert(ptr);
	assert(size <= MAX_BYTES);

	// �Ҷ�Ӧ������Ͱ�������ȥ
	size_t index = SizeClass::Index(size);
	_freeLists[index].Push(ptr);

	return nullptr;

}


void* ThreadCache::FetchFromCentralCache(size_t index, size_t size)
{
	// ����ʼ�ķ��������㷨
	// 1.��ʼ������central cache����̫�࣬��Ϊ̫���˿����ò���
	// 2.���size��С���ڴ����󣬾ͻ�������������
	// 3. sizeԽ��һ����central cacheҪ��batch��ԽС����֮��Ȼ
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

