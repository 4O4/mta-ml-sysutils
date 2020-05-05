#include "Common.h"
#include "CFunctions.h"
#include "include/ILuaModuleManager.h"
#include "Module.h"
#include "LunaExampleClass.h"
#include "LunaExampleClassHelper.h"
#include <cstring>

#ifndef WIN32
	#include "luaimports/luaimports.linux.h"
#endif

ILuaModuleManager10* pModuleManager = nullptr;

// Initialization function (module entrypoint)
MTAEXPORT bool InitModule(ILuaModuleManager10* pManager, char* szModuleName, char* szAuthor, float* fVersion)
{
#ifndef WIN32
	ImportLua();
#endif

    pModuleManager = pManager;

	// Set the module info
    const auto module_name	= "System Utilities Module";
    const auto author		= "4O4 <pk.pawelo@gmail.com>";
	std::memcpy(szModuleName, module_name,	MAX_INFO_LENGTH);
	std::memcpy(szAuthor,     author,		MAX_INFO_LENGTH);
	*fVersion = 1.0f;
	
	// Load module
	g_Module = new Module(pManager);
	g_Module->Start();

    return true;
}

MTAEXPORT void RegisterFunctions(lua_State* luaVM)
{
	if (!pModuleManager || !luaVM)
		return;

	// Add lua vm to states list (to check validity)
	g_Module->AddLuaVM(luaVM);

	// Register luna classes
	// LunaExampleClassHelper::Register(luaVM);
	pModuleManager->RegisterFunction(luaVM, "executeSystemCommand", &CFunctions::ExecuteSystemCommand);
	pModuleManager->RegisterFunction(luaVM, "getSystemEnvVariable", &CFunctions::GetSystemEnvVariable);
}

MTAEXPORT bool DoPulse()
{
	g_Module->Process();

	return true;
}

MTAEXPORT bool ShutdownModule()
{
	// Unload module
	delete g_Module;

    return true;
}

MTAEXPORT bool ResourceStopping(lua_State* luaVM)
{
	// Invalidate lua vm by removing it from the valid list
	g_Module->RemoveLuaVM(luaVM);

	return true;
}

MTAEXPORT bool ResourceStopped(lua_State* luaVM)
{
	return true;
}
