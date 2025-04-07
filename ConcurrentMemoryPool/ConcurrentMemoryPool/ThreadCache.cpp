#include "ThreadCache.h"

// 申请和释放内存对象
void* ThreadCache::Allocate(size_t size)
{
	assert(size < MAX_BYTES);

}
void* ThreadCache::Deallocate(size_t size)
{

}