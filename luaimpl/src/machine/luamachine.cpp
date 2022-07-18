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
		lua_close(m_LuaState);
	}

	std::string LuaMachine::popError() {
		std::string tmp = m_ErrorStack.top();
		m_ErrorStack.pop();
		return tmp;
	}

	void LuaMachine::checkLua(int r) {
		if (r != LUA_OK)
		{
			std::cout << lua_tostring(m_LuaState, -1);
		}
	}

	void LuaMachine::pushError(const std::string& errorMsg) {
		m_ErrorStack.push(errorMsg);
	}

	void LuaMachine::push(const std::any& arg) {

		if (arg.type() == typeid(int)) {
			lua_pushinteger(m_LuaState, std::any_cast<int>(arg));
			m_ArgCounter++;
			return;
		}

		if (arg.type() == typeid(unsigned int)) {
			lua_pushinteger(m_LuaState, std::any_cast<unsigned int>(arg));
			m_ArgCounter++;
			return;
		}

		if (arg.type() == typeid(short)) {
			lua_pushinteger(m_LuaState, std::any_cast<short>(arg));
			m_ArgCounter++;
			return;
		}

		if (arg.type() == typeid(unsigned short)) {
			lua_pushinteger(m_LuaState, std::any_cast<unsigned short>(arg));
			m_ArgCounter++;
			return;
		}

		if (arg.type() == typeid(long)) {
			lua_pushinteger(m_LuaState, std::any_cast<long>(arg));
			m_ArgCounter++;
			return;
		}

		if (arg.type() == typeid(unsigned long)) {
			lua_pushinteger(m_LuaState, std::any_cast<unsigned long>(arg));
			m_ArgCounter++;
			return;
		}

		if (arg.type() == typeid(float)) {
			lua_pushnumber(m_LuaState, std::any_cast<float>(arg));
			m_ArgCounter++;
			return;
		}

		if (arg.type() == typeid(double)) {
			lua_pushnumber(m_LuaState, std::any_cast<double>(arg));
			m_ArgCounter++;
			return;
		}

		if (arg.type() == typeid(bool)) {
			lua_pushinteger(m_LuaState, std::any_cast<bool>(arg));
			m_ArgCounter++;
			return;
		}

		if (arg.type() == typeid(const char*)) {
			lua_pushstring(m_LuaState, std::any_cast<const char*>(arg));
			m_ArgCounter++;
			return;
		}

		if (arg.type() == typeid(std::string)) {
			lua_pushstring(m_LuaState, std::any_cast<std::string>(arg).c_str());
			m_ArgCounter++;
			return;
		}

		if (arg.type() == typeid(LuaTable)) {
			push(std::any_cast<LuaTable>(arg));
			m_ArgCounter++;
			return;
		}

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

	template<>
	LuaTable LuaMachine::getResult<LuaTable>() {

		LuaTable result;

		if (lua_istable(m_LuaState, -1)) {
			lua_pushnil(m_LuaState);
			while (lua_next(m_LuaState, -2) != 0)
			{
				if (lua_istable(m_LuaState, -1)) {
					result.set(lua_tostring(m_LuaState, -2), getResult<LuaTable>());
				} else if (lua_isnumber(m_LuaState, -1))
				{
					result.set(lua_tostring(m_LuaState, -2), lua_tonumber(m_LuaState, -1));
				} else if (lua_isboolean(m_LuaState, -1)) {
					result.set(lua_tostring(m_LuaState, -2), lua_toboolean(m_LuaState, -1));
				} else if (lua_isstring(m_LuaState, -1)) {
					result.set(lua_tostring(m_LuaState, -2), std::string(lua_tostring(m_LuaState, -1)));
				} else { /* ERROR */ }

				lua_pop(m_LuaState, 1);

			}

			return result;
		} else {
			//errorhandling				
		}

		return result;

	}


}