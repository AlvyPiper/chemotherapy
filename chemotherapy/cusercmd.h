#pragma once

#include "chemo.h"
namespace source_sdk
{
	struct user_cmd
	{
		virtual ~user_cmd() {}; //deconstructor/4 bytes
		int command_number; //8
		int tick_count; //12
		Vector viewangles; //24
		Vector aimdir; //36
		Vector move; //48
		int buttons; //52
		char impulse; //53
		int weaponselect; //57
		int weaponsubtype; //61
		int random_seed; //65
		short mousedx; //68
		short mousedy; //69
		bool hasbeenpredicted; //70
		char pad01[24]; //70+24 = 94
	};
}