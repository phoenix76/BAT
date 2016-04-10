#ifndef _BAT_CSTRING_H_
#define _BAT_CSTRING_H_

#include <iostream>
#include "bat_platform.h"
#include "bat_types.h"

namespace BAT
{
	class _BAT_API_ CBatCString
	{
	public:
		CBatCString();
		CBatCString(const char*);

		//Copy constructor
		CBatCString(const CBatCString& obj);

		~CBatCString();

		friend _BAT_API_ std::ostream & operator<<(std::ostream &, const CBatCString &);

	private:
		char* _str;
		int _length;
	};

	class _BAT_API_ CBatWCString
	{

	};
}

#endif