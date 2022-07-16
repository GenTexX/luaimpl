#include <string>
#include <iostream>
extern "C" {

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

}

int doStuff() {

	std::string cmd = "print(\"Hello Guys!\")";

	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	int r = luaL_dostring(L, cmd.c_str());

	if (r == LUA_OK)
	{
		lua_getglobal(L, "a");
		if (lua_isnumber(L, -1))
		{
			float a_in_cpp = (float)lua_tonumber(L, -1);
			std::cout << "a = " << a_in_cpp << std::endl;
		}
	} else {
		std::string error = lua_tostring(L, -1);
		std::cout << error << std::endl;
	}

	return 0;

}