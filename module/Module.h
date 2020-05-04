#pragma once
#include <unordered_set>
#include <any>
#include <optional>

#include "JobManager.h"
#include "ILuaModuleManager.h"
#include "Luna.h"

struct lua_State;
class ILuaModuleManager;

class Module
{
public:
	Module(ILuaModuleManager* manager);
	~Module();

	void Start();
	void Process();

	inline void AddLuaVM(lua_State* luaVM) { _luaStates.insert(luaVM); }
	inline void RemoveLuaVM(lua_State* luaVM) { _luaStates.erase(luaVM); }
	inline bool HasLuaVM(lua_State* luaVM) { return _luaStates.find(luaVM) != _luaStates.end(); }

	inline JobManager<const std::optional<std::any>>& GetJobManager() { return _jobManager; }

	static void register_lua_global(lua_State* lua_vm, const char* name, void* value);
	static void register_table_function(lua_State* lua_vm, const char* function_name, lua_CFunction function);
	static void register_class(lua_State* lua_vm, const char* metatable, const luaL_Reg* registry);
	
private:
	ILuaModuleManager* _moduleManager;
	JobManager<const std::optional<std::any>> _jobManager;
	std::unordered_set<lua_State*> _luaStates;
};

extern Module* g_Module;
