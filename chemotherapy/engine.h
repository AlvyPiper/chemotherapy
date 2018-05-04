#pragma once

#include "chemo.h"

namespace source_sdk
{
	struct engine_client
	{
		inline int get_local_player_idx()
		{
			using function_ptr = int32_t (__thiscall *) (void *);
			return get_virtual<function_ptr>(this, 12)(this);
		}
	};
}
extern source_sdk::engine_client *engine_client;