#pragma once

#include "includes.h"

typedef void(__cdecl *MsgFn)(const char *, ...);
typedef void(__cdecl *WarningFn)(const char *, ...);

extern MsgFn msg;
extern WarningFn warning;