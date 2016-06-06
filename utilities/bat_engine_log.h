#ifndef BAT_ENGINE_LOG_H
#define BAT_ENGINE_LOG_H

#include "bat_sys_macroses.h"
#include "bat_win_utils.h"
#include <fstream>

namespace BAT_UTILS
{
	DLLEXP void AddToLog(const char* i, ...)
	{
		std::ofstream file("logs/system.txt", std::ios::app);
		va_list args;
		va_start(args, i);
		int len = _vscprintf(i, args) + 1;
		char *buffer = static_cast<char*>(malloc(len*sizeof(char)));
		vsprintf_s(buffer, len, i, args);
		file << buffer;
		va_end(args);
		free(buffer);
		file.close();
	}

	DLLEXP void RLog(const char* i, ...)
	{
		std::ofstream file("logs/system.txt", std::ios::app);
		va_list args;
		va_start(args, i);
		int len = _vscprintf(i, args) + 1;
		char *buffer = static_cast<char*>(malloc(len*sizeof(char)));
		vsprintf_s(buffer, len, i, args);
		file << GetTimeStamp() << "-> " << buffer;
		va_end(args);
		free(buffer);
		file << '\n';
		file.close();
	}

	DLLEXP void DebugLog(const char* i, ...)
	{
#ifdef _DEBUG
		std::ofstream file("logs/system.txt", std::ios::app);
		va_list args;
		va_start(args, i);
		int len = _vscprintf(i, args) + 1;
		char *buffer = static_cast<char*>(malloc(len*sizeof(char)));
		vsprintf_s(buffer, len, i, args);
		file << GetTimeStamp() << "-> " << buffer;
		va_end(args);
		free(buffer);
		file << '\n';
		file.close();
#endif
	}
}

#define BGE_Dbg_Log( ... ) BAT_UTILS::DebugLog(__VA_ARGS__)
#define BGE_Rls_Log( ... ) BAT_UTILS::DebugLog(__VA_ARGS__)
#define BGE_Log( ... ) BAT_UTILS::AddToLog(__VA_ARGS__)

#endif