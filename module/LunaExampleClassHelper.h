#pragma once
#include "LunaExampleClass.h"
#include "Utils.h"

const char LunaExampleClass::className[] = "RedisClient";
Luna<LunaExampleClass>::RegType LunaExampleClass::methods[] = {
	// methods
	method(LunaExampleClass, memberMethod),

	// Do not remove, required
	{ nullptr,		nullptr}
};

class LunaExampleClassHelper
{
public:
	static inline void Register(lua_State* lua_vm) { Luna<LunaExampleClass>::Register(lua_vm); }
};
