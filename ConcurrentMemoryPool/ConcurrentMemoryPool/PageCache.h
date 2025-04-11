#pragma once

#include "Common.h"

class PageCache
{
public:
	static PageCache* GetInstance()
	{
		return &_sInst;
	}

	// ��ȡһ��kҳ��span
	Span* NewSpan(size_t k);

	std::mutex _pageMtx; // _pageLists��������

private:
	SpanList _spanLists[NPAGES];

	PageCache()
	{}

	PageCache(const PageCache&) = delete;

	static PageCache _sInst;
};