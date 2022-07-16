#include "luamachine.h"
#include "wrongReturnTypeException.h"
#include <iostream>
namespace luaimpl {
	luaimpl::LuaMachine::LuaMachine() {

		m_LuaState = luaL_newstate();
		m_ArgCounter = 0;
		luaL_openlibs(m_LuaState);
		int r = luaL_dofile(m_LuaState, "assets/test.lua");

		if (r != LUA_OK)
		{
			std::cout << lua_tostring(m_LuaState, -1);
		}

	}

	luaimpl::LuaMachine::~LuaMachine() {
	}

	void LuaMachine::checkLua(int r) {
		if (r != LUA_OK)
		{
			std::cout << lua_tostring(m_LuaState, -1);
		}
	}

	void LuaMachine::push(const int arg) {
		lua_pushnumber(m_LuaState, arg);
		m_ArgCounter++;
	}
	void LuaMachine::push(const short arg) {
		lua_pushnumber(m_LuaState, arg);
		m_ArgCounter++;
	}
	void LuaMachine::push(const long arg) {
		lua_pushnumber(m_LuaState, arg);
		m_ArgCounter++;
	}
	void LuaMachine::push(const float arg) {
		lua_pushnumber(m_LuaState, arg);
		m_ArgCounter++;
	}
	void LuaMachine::push(const double arg) {
		lua_pushnumber(m_LuaState, arg);
		m_ArgCounter++;
	}
	void LuaMachine::push(const bool arg) {
		lua_pushboolean(m_LuaState, arg);
		m_ArgCounter++;
	}
	void LuaMachine::push(const char* arg) {
		lua_pushstring(m_LuaState, arg);
		m_ArgCounter++;
	}
	void LuaMachine::push(const std::string& arg) {
		lua_pushstring(m_LuaState, arg.c_str());
		m_ArgCounter++;
	}

	template<>
	int LuaMachine::getResult<int>() {

		if (lua_isinteger(m_LuaState, -1))
			return static_cast<int>(lua_tointeger(m_LuaState, -1));
		else {
			throw WrongReturnTypeException(typeid(int).name());
		}

		return 0;

	}

	template<>
	unsigned int LuaMachine::getResult<unsigned int>() {

		if (lua_isinteger(m_LuaState, -1))
			return static_cast<unsigned int>(lua_tointeger(m_LuaState, -1));
		else {
			//errorhandling				
		}

		return 0;

	}

	template<>
	short LuaMachine::getResult<short>() {

		if (lua_isinteger(m_LuaState, -1))
			return static_cast<short>(lua_tointeger(m_LuaState, -1));
		else {
			//errorhandling				
		}

		return 0;

	}

	template<>
	unsigned short LuaMachine::getResult<unsigned short>() {

		if (lua_isinteger(m_LuaState, -1))
			return static_cast<unsigned short>(lua_tointeger(m_LuaState, -1));
		else {
			//errorhandling				
		}

		return 0;

	}

	template<>
	long LuaMachine::getResult<long>() {

		if (lua_isinteger(m_LuaState, -1))
			return static_cast<long>(lua_tointeger(m_LuaState, -1));
		else {
			//errorhandling				
		}

		return 0;

	}

	template<>
	unsigned long LuaMachine::getResult<unsigned long>() {

		if (lua_isinteger(m_LuaState, -1))
			return static_cast<unsigned long>(lua_tointeger(m_LuaState, -1));
		else {
			//errorhandling				
		}

		return 0;

	}

	template<>
	float LuaMachine::getResult<float>() {

		if (lua_isnumber(m_LuaState, -1))
			return static_cast<float>(lua_tonumber(m_LuaState, -1));
		else {
			//errorhandling				
		}

		return 0.0f;

	}

	template<>
	double LuaMachine::getResult<double>() {

		if (lua_isnumber(m_LuaState, -1))
			return lua_tonumber(m_LuaState, -1);
		else {
			//errorhandling				
		}

		return 0.0;

	}

	template<>
	bool LuaMachine::getResult<bool>() {

		if (lua_isboolean(m_LuaState, -1))
			return lua_toboolean(m_LuaState, -1);
		else {
			//errorhandling				
		}

		return false;

	}

	template<>
	const char* LuaMachine::getResult<const char*>() {

		if (lua_isstring(m_LuaState, -1))
			return lua_tostring(m_LuaState, -1);
		else {
			//errorhandling				
		}

		return "";

	}

	template<>
	std::string LuaMachine::getResult<std::string>() {

		if (lua_isstring(m_LuaState, -1))
			return std::string(lua_tostring(m_LuaState, -1));
		else {
			//errorhandling				
		}

		return "";

	}


}