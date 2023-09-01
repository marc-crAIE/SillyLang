#pragma once

#include "Objects/SiObject.h"

#define _SiHash_Multiplier	0xF4243UL
#define _SiHash_Bits		61

#define _SiHash_Modulus		(((Si_size_t)1 << _SiHash_Bits) - 1)
#define _SiHash_Infinite	3141592

class Hash final
{
public:
	static Si_hash_t Double(SiObject* instance, double d);

	static Si_hash_t CRC32B(const char* str);
};