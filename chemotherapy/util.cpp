#include "chemo.h"

using namespace chemo;

uintptr_t util::find_pattern(uint32_t address, const char* pattern)
{
	for (unsigned long i = 0; i < 0x7FFFFFFF; ++i, ++address)
	if (util::data_compare((const char*) address, pattern))
		return address;

	return 0;
}

bool util::data_compare(const char* base, const char* pattern)
{
	for (; *pattern; ++base, ++pattern)
	if (*pattern != '?' && *base != *pattern)
		return 0;

	return *pattern == 0;
}