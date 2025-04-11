
#include "PageCache.h"

PageCache PageCache::_sInst;

// ��ȡһ��kҳ��span
Span* PageCache::NewSpan(size_t k)
{
	assert(k > 0 && k < NPAGES);

	if (!_spanLists[k].Empty())
	{
		return _spanLists[k].PopFront();
	}

	// ���һ�º����Ͱ����û��span������У����԰��������з�
	for (size_t i = k + 1; k < NPAGES; i++)
	{
		if (!_spanLists[i].Empty())
		{
			Span* nSpan = _spanLists[i].PopFront();
			Span* kSpan = new Span;

			// ��nspan��ͷ����һ������
			kSpan->_PageId = nSpan->_PageId;
			kSpan->_n = k;

			nSpan->_PageId += k;
			nSpan->_n -= k;

			_spanLists[nSpan->_n].PushFront(nSpan);

			return kSpan;
		}
	}

	// ����˵��û�д�ҳ�棬��Ҫ�����һ��128ҳ���span
	Span* bigSpan = new Span;
	void* ptr = SystemAlloc(NPAGES - 1);
	bigSpan->_PageId = (PAGE_ID)ptr >> (PAGE_SHIFT);
	bigSpan->_n = NPAGES - 1;

	_spanLists[bigSpan->_n].PushFront(bigSpan);

	return NewSpan(k);
}