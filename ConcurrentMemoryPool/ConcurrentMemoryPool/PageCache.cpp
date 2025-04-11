
#include "PageCache.h"

PageCache PageCache::_sInst;

// 获取一个k页的span
Span* PageCache::NewSpan(size_t k)
{
	assert(k > 0 && k < NPAGES);

	if (!_spanLists[k].Empty())
	{
		return _spanLists[k].PopFront();
	}

	// 检查一下后面的桶里有没有span，如果有，可以把它进行切分
	for (size_t i = k + 1; k < NPAGES; i++)
	{
		if (!_spanLists[i].Empty())
		{
			Span* nSpan = _spanLists[i].PopFront();
			Span* kSpan = new Span;

			// 在nspan的头部切一个下来
			kSpan->_PageId = nSpan->_PageId;
			kSpan->_n = k;

			nSpan->_PageId += k;
			nSpan->_n -= k;

			_spanLists[nSpan->_n].PushFront(nSpan);

			return kSpan;
		}
	}

	// 到这说明没有大页面，需要向堆找一个128页面的span
	Span* bigSpan = new Span;
	void* ptr = SystemAlloc(NPAGES - 1);
	bigSpan->_PageId = (PAGE_ID)ptr >> (PAGE_SHIFT);
	bigSpan->_n = NPAGES - 1;

	_spanLists[bigSpan->_n].PushFront(bigSpan);

	return NewSpan(k);
}