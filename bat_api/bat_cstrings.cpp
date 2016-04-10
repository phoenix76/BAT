#define _CRT_SECURE_NO_WARNINGS

#include "bat_cstrings.h"
#include "bat_memory.h"

namespace BAT
{
	CBatCString::CBatCString()
	{
		_str = new char[1];
		_str[0] = '\0';
		_length = 0;
	}
	CBatCString::CBatCString(const char* str)
	{
		_length = std::strlen(str);
		_str = new char[_length + 1];
		std::strcpy(_str, str);
	}
	CBatCString::~CBatCString()
	{
		DELETE_ARR(_str);
	}
	std::ostream & operator<<(std::ostream& os, const CBatCString& obj)
	{
		os << obj._str;
		return os;
	}
}