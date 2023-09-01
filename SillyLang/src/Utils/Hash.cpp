#include "Utils/Hash.h"

Si_hash_t Hash::Double(SiObject* instance, double d)
{
	int e, sign;
	double m;
	Si_uhash_t x, y;

	m = frexp(d, &e);

	sign = 1;
	if (m < 0)
	{
		sign = -1;
		m = -m;
	}

	x = 0;
	while (m)
	{
		x = ((x << 28) & _SiHash_Modulus) | x >> (_SiHash_Bits - 28);
		m *= 268435456.0;
		e -= 28;
		y = (Si_uhash_t)m;
		m -= y;
		x += y;
		if (x >= _SiHash_Modulus)
			x -= _SiHash_Modulus;
	}

	e = e >= 0 ? e % _SiHash_Bits : _SiHash_Bits - 1 - ((-1 - e) % _SiHash_Bits);
	x = ((x << e) & _SiHash_Modulus) | x >> (_SiHash_Bits - e);

	x = x * sign;
	if (x == (Si_uhash_t)-1)
		x = (Si_uhash_t)-2;
	return (Si_hash_t)x;
}

Si_hash_t Hash::CRC32B(const char* str)
{
	Si_uint32_t byte, crc, mask;
	int i = 0, j;
	crc = 0xFFFFFFFF;
	while (str[i] != 0)
	{
		byte = str[i];
		crc = crc ^ byte;
		for (j = 7; j >= 0; j--)
		{
			mask = -(crc & 1);
			crc = (crc >> 1) ^ (0xEDB88320 & mask);
		}
		i = i + 1;
	}
	return ~crc;
}
