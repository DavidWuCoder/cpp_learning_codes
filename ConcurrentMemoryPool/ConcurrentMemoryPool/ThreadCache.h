#pragma once

#include "Common.h"

class ThreadCache
{
public:
	// 申请和释放内存对象
	void* Allocate(size_t size);
	void* Deallocate(void* ptr, size_t size);

	// 从中⼼缓存获取对象
	void* FetchFromCentralCache(size_t index, size_t size);

	void ListTooLong(FreeList& list, size_t size);
private:
	FreeList _freeLists[NFREE_LISTS];
};

static _declspec(thread) ThreadCache* pTLSThreadCache = nullptr;