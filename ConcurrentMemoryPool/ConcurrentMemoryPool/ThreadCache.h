#pragma once

#include "Common.h"

class ThreadCache
{
public:
	// ������ͷ��ڴ����
	void* Allocate(size_t size);
	void* Deallocate(size_t size);
private:
	FreeList _freeList[];
};