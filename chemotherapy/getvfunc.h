#pragma once
#include "chemo.h"

template<typename I>
inline I create_interface(const char *dll, const char *name) //nanocats
{
	return (I) (((void *(*)(const char *, void *))GetProcAddress(GetModuleHandleA(dll), "CreateInterface"))(name, 0));
}

template<typename Ex>
inline Ex get_export(const char *dll, const char *name)
{
	return (Ex) ((void *(*)(const char *, const char *))GetProcAddress(GetModuleHandleA(dll), name));
}


template<typename Fn>
inline Fn get_virtual(const void *v, int i)
{
	return (Fn) *(*(const void ***) v + i);
}