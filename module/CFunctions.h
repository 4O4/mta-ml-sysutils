#pragma once
#include <iostream>

#include "extra/CLuaArguments.h"

class ILuaModuleManager10;
struct lua_State;

extern ILuaModuleManager10* pModuleManager;

class CFunctions
{
public:
    static int ExecuteSystemCommand(lua_State* luaVM);
    static int GetSystemEnvVariable(lua_State* luaVM);
};
