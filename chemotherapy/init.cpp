#include "chemo.h"

using namespace chemo;

source_sdk::engine_client				*engine_client;
source_sdk::base_client					*base_client;
source_sdk::base_input					*base_input;
source_sdk::client_mode_shared			*client_mode_shared;
source_sdk::global_vars					*global_vars;
source_sdk::user_cmd					*user_cmd;
source_sdk::base_entity					*base_entity;
source_sdk::client_entity_list			*client_entity_list;

void init::do_sigscan()
{
	DWORD* client_table = (DWORD*) *(DWORD*) base_client; //TODO: Fix this.
	client_mode_shared = **(source_sdk::client_mode_shared***) (util::find_pattern(client_table[10], "\x8B\x0D????\x8B") + 0x02);
}

void init::do_interface()
{
	base_client = create_interface<source_sdk::base_client*>("client.dll", "VClient018");
	engine_client = create_interface<source_sdk::engine_client*>("engine.dll", "VEngineClient014");
	client_entity_list = create_interface<source_sdk::client_entity_list*>("client.dll", "VClientEntityList003");

	init::do_sigscan();

	/*msg("[CHEMO] Found ClientMode at 0x%x\n", clientmode); //NOTE: This is for debug purposes only!
	msg("[CHEMO] Found CClient at 0x%x\n", client);
	msg("[CHEMO] Found CEntityList at 0x%x\n", elist);
	msg("[CHEMO] Found CEngine at 0x%x\n", engine);
	msg("[CHEMO] Size of CUserCmd is %i\n", sizeof(cusercmd));*/
}

void init::do_hook()
{
	init::do_interface();

	VMT *vmt_client = new VMT(client_mode_shared);
	vmt_client->hook(24, hook_mngr::create_move, 0);
}

void init::finalize() //NOTE: This is bad practice, this was used for debugging purposes before. You would normally want to just pass init::do_hook() to DLLMain.
{
	init::do_hook();
}