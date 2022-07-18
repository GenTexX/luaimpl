#pragma once
#include <types/luaTable.h>
#include <string>
#include <typeinfo>
#include <stack>
#include <functional>
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
		
		template<typename R, typename ...Args>
		void bindFunction(const std::string& functionName, std::function<R(Args...)>);

		std::string popError();

	private:
		lua_State* m_LuaState;
		size_t m_ArgCounter;
		std::stack<std::string> m_ErrorStack;

		void checkLua(int r);
		void pushError(const std::string& errorMsg);
		
		template<typename T, typename... Args>
		void pushValues(const T arg, const Args... other);
		template<typename T>
		void pushValues(const T arg);
		void pushValues() {}

		void push(const std::any&);

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

		} else pushError(functionName + " is not a function");

		return R();
		
		
	}

	template<typename R, typename ...Args>
	inline void LuaMachine::bindFunction(const std::string& functionName, std::function<R(Args...)> function) {
		lua_pushcfunction(m_LuaState, [](lua_State* L) -> int {

			//get arguments from lua stack
			//result = function(args);
			//push result to lua stack

			return 1;	//number of results
		});
		lua_setglobal(m_LuaState, functionName.c_str());
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