#pragma once
#include "Module.h"

class ILuaModuleManager10;
struct lua_State;

extern ILuaModuleManager10* pModuleManager;

// http://lua-users.org/wiki/SimplerCppBinding
class LunaExampleClass
{
public:
	static const char className[];
	static Luna<LunaExampleClass>::RegType methods[];

	LunaExampleClass(lua_State*);
	~LunaExampleClass();

	int memberMethod(lua_State* lua_vm);
};

