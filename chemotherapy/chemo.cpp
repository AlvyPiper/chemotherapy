#include "chemo.h"

using namespace chemo;

bool __stdcall entry(HINSTANCE__ inst, unsigned long reason, void* reserved)
{
	if (reason == 1)
	{
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)init::finalize, 0, 0, 0);
	}
	TerminateThread(init::finalize, 0);

	return 1;
}