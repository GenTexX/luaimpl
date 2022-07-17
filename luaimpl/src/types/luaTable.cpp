#include "luaTable.h"

namespace luaimpl {

	template<>
	int LuaTable::get<int>(const std::string& key) {

		return (int)std::any_cast<double>(m_Map[key]);

	}

	template<>
	unsigned int LuaTable::get<unsigned int>(const std::string& key) {

		return std::any_cast<unsigned int>(m_Map[key]);

	}

	template<>
	short LuaTable::get<short>(const std::string& key) {

		return std::any_cast<short>(m_Map[key]);

	}

	template<>
	unsigned short LuaTable::get<unsigned short>(const std::string& key) {

		return std::any_cast<unsigned short>(m_Map[key]);

	}

	template<>
	long LuaTable::get<long>(const std::string& key) {

		return std::any_cast<long>(m_Map[key]);

	}

	template<>
	unsigned long LuaTable::get<unsigned long>(const std::string& key) {

		return std::any_cast<unsigned long>(m_Map[key]);

	}

	template<>
	float LuaTable::get<float>(const std::string& key) {

		return std::any_cast<float>(m_Map[key]);

	}

	template<>
	double LuaTable::get<double>(const std::string& key) {

		return std::any_cast<double>(m_Map[key]);

	}

	template<>
	bool LuaTable::get<bool>(const std::string& key) {

		return std::any_cast<bool>(m_Map[key]);

	}

	template<>
	std::string LuaTable::get<std::string>(const std::string& key) {

		return std::any_cast<std::string>(m_Map[key]);

	}

	template<>
	LuaTable LuaTable::get<LuaTable>(const std::string& key) {

		return std::any_cast<LuaTable>(m_Map[key]);

	}

}