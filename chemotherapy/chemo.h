#pragma once

#include "sdk.h"

namespace chemo
{
	namespace hook_mngr
	{
		extern bool __fastcall create_move(void*, void*, float, source_sdk::user_cmd*);
	}

	namespace util
	{
		extern bool data_compare(const char*, const char*);
		extern uintptr_t find_pattern(uint32_t, const char*);
	}

	namespace init
	{
		extern void initalize();
		extern void do_sigscan();
		extern void do_interface();
		extern void do_hook();
		extern void finalize();
	}
}