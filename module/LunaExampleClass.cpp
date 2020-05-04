#include "LunaExampleClass.h"

#ifndef _WIN32
	#include <sys/stat.h>
#endif

LunaExampleClass::LunaExampleClass(lua_State*)
{
	
}

LunaExampleClass::~LunaExampleClass()
{
	
}

int LunaExampleClass::memberMethod(lua_State* lua_vm)
{
	return 0;
}
