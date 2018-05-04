#pragma once

#include "chemo.h"

namespace source_sdk 
{
	struct client_entity_list 
	{
		source_sdk::base_entity *get_entity_by_index(int32_t index) 
		{
			using function_ptr = source_sdk::base_entity *(__thiscall *) (void *, int32_t);
			return get_virtual<function_ptr>(this, 3)(this, index);
		}
	};
}
extern source_sdk::client_entity_list *client_entity_list;