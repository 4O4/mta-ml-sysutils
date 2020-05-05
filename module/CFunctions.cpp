#include "Module.h"
#include "CFunctions.h"
#include "Utils.h"
#include <cstdlib>
#include "process.hpp"

#ifndef _WIN32
#include <sys/stat.h>
#endif

using namespace TinyProcessLib;

typedef struct Result {
  int exitCode;
  std::string stdout;
  std::string stderr;
} Result;

int CFunctions::ExecuteSystemCommand(lua_State* luaVM) {
  // bool executeSystemCommand(string command, function callback)
  if (lua_type(luaVM, 1) != LUA_TSTRING ||
      lua_type(luaVM, 2) != LUA_TFUNCTION) {
    pModuleManager->ErrorPrintf("Bad argument @ executeSystemCommand\n");
    lua_pushboolean(luaVM, false);
    return 1;
  }

  const char* command = lua_tostring(luaVM, 1);

  // Save reference of the Lua callback function
  // See: http://lua-users.org/lists/lua-l/2008-12/msg00193.html
  lua_pushvalue(luaVM, -1);
  int funcRef = luaL_ref(luaVM, LUA_REGISTRYINDEX);

  g_Module->GetJobManager().PushTask(
      [command]() {
        // cout << "entered lambda" << endl;
        std::string stdout, stderr;
        Process process(command, "",
                        [&stdout](const char* bytes, size_t n) {
                          // cout << "Output from stdout: " << string(bytes, n);
                          stdout = (std::string(bytes, n));
                        },
                        [&stderr](const char* bytes, size_t n) {
                          stderr = std::string(bytes, n);
                          // cout << "Output from stderr: " << string(bytes, n);
                        });

        // cout << "finished lambda" << endl;
        return Result{process.get_exit_status(), stdout, stderr};

      },
      [ luaVM = lua_getmainstate(luaVM), funcRef ](auto result) {
        // Validate LuaVM (use ResourceStart/-Stop to manage valid lua states)
        if (!g_Module->HasLuaVM(luaVM))
          return;

        // cout << "task finished, gonna process result" << endl;
        const Result res = std::any_cast<Result>(result);
        // cout << "result casted" << endl;

        // Push stored reference to callback function to the stack
        lua_rawgeti(luaVM, LUA_REGISTRYINDEX, funcRef);

        // 	// Push arguments to the stack
        lua_pushnumber(luaVM, res.exitCode);
        lua_pushstring(luaVM, res.stdout.c_str());
        lua_pushstring(luaVM, res.stderr.c_str());

        // Finally, call the function
        int err = lua_pcall(luaVM, 3, 0, 0);
        if (err != 0)
          pModuleManager->ErrorPrintf("%s\n", lua_tostring(luaVM, -1));

      });

  lua_pushboolean(luaVM, true);
  return 1;
}

int CFunctions::GetSystemEnvVariable(lua_State* luaVM) {
  // bool executeSystemCommand(string command, function callback)
  if (lua_type(luaVM, 1) != LUA_TSTRING) {
    pModuleManager->ErrorPrintf("Bad argument @ getSystemEnvVariable\n");
    lua_pushboolean(luaVM, false);
    return 1;
  }

  const char* command = lua_tostring(luaVM, 1);

  lua_pushstring(luaVM, std::getenv(command));
  return 1;
}