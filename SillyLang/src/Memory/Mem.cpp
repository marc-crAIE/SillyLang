#include "Memory/Mem.h"

void* Memory::Alloc(size_t size)
{
	if (size == 0)
		size = 1;
	return malloc(size);
}

void* Memory::Calloc(size_t elemCount, size_t elemSize)
{
	if (elemCount == 0 || elemSize == 0)
	{
		elemCount = 1;
		elemSize = 1;
	}
	return calloc(elemCount, elemSize);
}

void* Memory::Realloc(void* ptr, size_t newSize)
{
	if (newSize == 0)
		newSize = 1;
	return realloc(ptr, newSize);
}

void Memory::Free(void* ptr)
{
	free(ptr);
}
