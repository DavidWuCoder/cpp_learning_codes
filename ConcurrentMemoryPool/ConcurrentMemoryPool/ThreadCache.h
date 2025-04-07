#pragma once

#include "Common.h"

class ThreadCache
{
public:
	// 申请和释放内存对象
	void* Allocate(size_t size);
	void* Deallocate(size_t size);
private:
	FreeList _freeList[];
};