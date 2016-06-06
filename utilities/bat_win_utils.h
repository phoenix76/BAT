#ifndef BAT_WIN_UTILS_H
#define BAT_WIN_UTILS_H

#include <Windows.h>
#include <string>
#include "bat_sys_macroses.h"

namespace BAT_UTILS
{
	DLLEXP std::string GetTimeStamp();

	DLLEXP bool VerifyFileExists(const wchar_t* filename);

	DLLEXP void DeleteSomeFile(const wchar_t* filePatch);
}

#endif