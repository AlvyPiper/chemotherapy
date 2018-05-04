#include "chemo.h"

using namespace chemo;

bool __fastcall hook_mngr::create_move(void* thishook, void*, float frametime, source_sdk::user_cmd* cmd)
{
	if (cmd->command_number == 0)
		return 0;

	source_sdk::base_entity *ent = client_entity_list->get_entity_by_index(engine_client->get_local_player_idx());

	if (cmd->buttons &IN_JUMP && (!(ent->flags() &FL_ONGROUND)))
	{
			cmd->buttons &= ~IN_JUMP;
	}

	return 0;
}