
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
	for (size_t i = k + 1; i < NPAGES; i++)
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

			// 存储nSpan的前后首尾页号和nSpan樱花色色，方面page chache会后内存时候进行查找
			_idSpanMap[nSpan->_PageId] = nSpan;
			_idSpanMap[nSpan->_PageId + nSpan->_n - 1] = nSpan;


			// 建立id和span的映射，方便central cache回收
			for (PAGE_ID i = 0; i < kSpan->_n; i++)
			{
				_idSpanMap[kSpan->_PageId + i] = kSpan;
			}

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

Span* PageCache::MapObjectToSpan(void* obj)
{
	PAGE_ID id = ((PAGE_ID)obj >> PAGE_SHIFT);
	auto ret = _idSpanMap.find(id);
	if (ret != _idSpanMap.end())
	{
		return ret->second;
	}
	else
	{
		assert(false);
	}
}

// 释放空闲span回到Pagecache，并合并相邻的span
void PageCache::ReleaseSpanToPageCache(Span* span)
{
	// 对span前后的页，尝试进行合并，环节内存碎片（外碎片）
	// 向前合并
	while (true)
	{
		PAGE_ID prevId = span->_PageId - 1;
		auto ret = _idSpanMap.find(prevId);
		// 前面的页号不存在
		if (ret == _idSpanMap.end())
		{
			break;
		}

		// 前面相邻页的Span在使用，就不合并了
		Span* prevSpan = ret->second;
		if (prevSpan->_isUse == true)
		{
			break;
		}

		// 合并出超过128页的span没办法管理
		if (prevSpan->_n + span->_n > NPAGES - 1)
		{
			break;
		}

		span->_PageId = prevSpan->_PageId;
		span->_n += prevSpan->_n;

		_spanLists[prevSpan->_n].Erase(prevSpan);

		delete prevSpan;
	}
	// 向后合并
	while (true)
	{
		PAGE_ID nextId = span->_PageId + span->_n;
		auto ret = _idSpanMap.find(nextId);
		// 前面的页号不存在
		if (ret == _idSpanMap.end())
		{
			break;
		}

		// 前面相邻页的Span在使用，就不合并了
		Span* nextSpan = ret->second;
		if (nextSpan->_isUse == true)
		{
			break;
		}

		// 合并出超过128页的span没办法管理
		if (nextSpan->_n + span->_n > NPAGES - 1)
		{
			break;
		}

		span->_n += nextSpan->_n;
		_spanLists[nextSpan->_n].Erase(nextSpan);

		delete nextSpan;
	}

	_spanLists[span->_n].PushFront(span);
	span->_isUse = false;
	_idSpanMap[span->_PageId] = span;
	_idSpanMap[span->_PageId + span->_n - 1] = span;
}
