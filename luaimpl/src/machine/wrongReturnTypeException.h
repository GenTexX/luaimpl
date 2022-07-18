#pragma once
#include <exception>

namespace luaimpl {

	class WrongReturnTypeException : public std::exception{
	public:
		WrongReturnTypeException(const char* expected) {
		
			m_Expected = expected;
		
		}
		~WrongReturnTypeException() {}
		const char* what() const override {
			return std::string(std::string("Expected ") + m_Expected + " as return type.").c_str();
		}

	private:
		const char* m_Expected;

	};


}