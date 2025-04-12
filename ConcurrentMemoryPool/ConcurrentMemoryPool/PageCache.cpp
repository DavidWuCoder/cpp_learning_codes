
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
	for (size_t i = k + 1; i < NPAGES; i++)
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

			// �洢nSpan��ǰ����βҳ�ź�nSpanӣ��ɫɫ������page chache����ڴ�ʱ����в���
			_idSpanMap[nSpan->_PageId] = nSpan;
			_idSpanMap[nSpan->_PageId + nSpan->_n - 1] = nSpan;


			// ����id��span��ӳ�䣬����central cache����
			for (PAGE_ID i = 0; i < kSpan->_n; i++)
			{
				_idSpanMap[kSpan->_PageId + i] = kSpan;
			}

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

// �ͷſ���span�ص�Pagecache�����ϲ����ڵ�span
void PageCache::ReleaseSpanToPageCache(Span* span)
{
	// ��spanǰ���ҳ�����Խ��кϲ��������ڴ���Ƭ������Ƭ��
	// ��ǰ�ϲ�
	while (true)
	{
		PAGE_ID prevId = span->_PageId - 1;
		auto ret = _idSpanMap.find(prevId);
		// ǰ���ҳ�Ų�����
		if (ret == _idSpanMap.end())
		{
			break;
		}

		// ǰ������ҳ��Span��ʹ�ã��Ͳ��ϲ���
		Span* prevSpan = ret->second;
		if (prevSpan->_isUse == true)
		{
			break;
		}

		// �ϲ�������128ҳ��spanû�취����
		if (prevSpan->_n + span->_n > NPAGES - 1)
		{
			break;
		}

		span->_PageId = prevSpan->_PageId;
		span->_n += prevSpan->_n;

		_spanLists[prevSpan->_n].Erase(prevSpan);

		delete prevSpan;
	}
	// ���ϲ�
	while (true)
	{
		PAGE_ID nextId = span->_PageId + span->_n;
		auto ret = _idSpanMap.find(nextId);
		// ǰ���ҳ�Ų�����
		if (ret == _idSpanMap.end())
		{
			break;
		}

		// ǰ������ҳ��Span��ʹ�ã��Ͳ��ϲ���
		Span* nextSpan = ret->second;
		if (nextSpan->_isUse == true)
		{
			break;
		}

		// �ϲ�������128ҳ��spanû�취����
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
