#pragma once
#include <map>
#include <string>
#include <any>

namespace luaimpl {

	class LuaTable {
	public:
		LuaTable() {}
		~LuaTable() {}

		template<typename T>
		void set(const std::string& key, const T val);
		template<typename T>
		T get(const std::string& key);


		std::map<std::string, std::any>::const_iterator begin() const { return m_Map.begin();  }
		std::map<std::string, std::any>::const_iterator end() const { return m_Map.end();  }

	private:
		std::map<std::string, std::any> m_Map;

	};
	template<typename T>
	inline void LuaTable::set(const std::string& key, const T val) {
		m_Map[key] = val;
	}
}