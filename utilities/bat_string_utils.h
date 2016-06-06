#ifndef BAT_STRING_UTILS_H
#define BAT_STRING_UTILS_H

#include <string>
#include <memory>
#include <cstring>
#include <locale>
#include "bat_sys_macroses.h"

namespace BAT_UTILS
{
	DLLEXP std::wstring STDStrToWCHAR(const std::string& s)
	{
		typedef std::codecvt<wchar_t, char, mbstate_t> codec_t;
		return std::wstring_convert<codec_t>(&std::use_facet<codec_t>(std::locale(".1251"))).from_bytes(s);
	}
}

#endif