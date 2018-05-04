#pragma once

#include "chemo.h"

namespace source_sdk
{
	struct base_entity
	{
		int &flags()
		{
			return *(int *)((int32_t)this + 0x100); //TODO: fix later.
		}
	};
}