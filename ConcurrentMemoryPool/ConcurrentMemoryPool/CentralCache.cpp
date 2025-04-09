﻿#include "CentralCache.h"

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
Span* CentralCache::GetOneSpan(SpanList& list, size_t byte_size)
{
	return nullptr;
}