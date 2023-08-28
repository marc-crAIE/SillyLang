#pragma once

#include "port.h"

class Memory final
{
public:
	static void* Alloc(size_t size);
	static void* Calloc(size_t elemCount, size_t elemSize);
	static void* Realloc(void* ptr, size_t newSize);
	static void Free(void* ptr);
};