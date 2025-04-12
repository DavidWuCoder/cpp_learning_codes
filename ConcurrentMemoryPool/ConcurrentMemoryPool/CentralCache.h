#pragma once

#include "Common.h"

// 单例模式
class CentralCache
{
public:
	static CentralCache* GetInstance()
	{
		return &_sInst;
	}

	// 获取⼀个⾮空的span
	Span* GetOneSpan(SpanList& list, size_t byte_size);

	// 从中⼼缓存获取⼀定数量的对象给thread cache
	size_t FetchRangeObj(void*& start, void*& end, size_t batchNum, size_t size);

	// 将⼀定数量的对象释放到span跨度
	void ReleaseListToSpans(void* start, size_t size);

private:
	// 构造函数私有，则无法创建
	CentralCache()
	{}

	// 拷贝构造也需要删除，防止拷贝出新对象
	CentralCache(const CentralCache&) = delete;

	SpanList _spanLists[NFREE_LISTS];

	static CentralCache _sInst;
};