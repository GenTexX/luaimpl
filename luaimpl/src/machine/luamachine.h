#pragma once
#include <types/luaTable.h>
#include <string>
#include <typeinfo>
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

typedef void (*callback_function)(void);

namespace luaimpl {

	class LuaMachine {
	public:
		LuaMachine();
		~LuaMachine();

		template<typename R, typename... Args>
		R call(const std::string& functionName, const Args ...other);

	private:
		lua_State* m_LuaState;
		size_t m_ArgCounter;

		void checkLua(int r);
		
		template<typename T, typename... Args>
		void pushValues(const T arg, const Args... other);
		template<typename T>
		void pushValues(const T arg);
		void pushValues() {}

		void push(const int);
		void push(const short);
		void push(const long);
		void push(const bool);
		void push(const float);
		void push(const double);
		void push(const char*);
		void push(const std::any&);
		void push(const std::string&);
		void push(const LuaTable&);

		template<typename R>
		R getResult();
		
	};

	template<typename R, typename ...Args>
	inline R LuaMachine::call(const std::string& functionName, const Args  ...other) {

		lua_getglobal(m_LuaState, functionName.c_str());
		if (lua_isfunction(m_LuaState, -1)) {
			m_ArgCounter = 0;
			pushValues(other...);
			int r = lua_pcall(m_LuaState, (int)m_ArgCounter, 1, 0);
			checkLua(r);

			return getResult<R>();

		} else std::cout << "[LUA ERROR] not a function" << std::endl;

		return R();
		
		
	}

	template<typename T, typename ...Args>
	inline void LuaMachine::pushValues(const T arg, const Args ...other) {
		push(arg);
		pushValues(other...);
	}

	template<typename T>
	inline void LuaMachine::pushValues(const T arg) {
		push(arg);
	}

}