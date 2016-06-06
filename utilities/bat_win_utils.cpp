#include <Windows.h>
#include "bat_win_utils.h"
#include <ctime>

namespace BAT_UTILS
{
	DLLEXP std::string GetTimeStamp()
	{
		time_t rawtime;
		tm * timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		std::string info = "";
		if(timeinfo->tm_mday < 10)
			info += '0' + std::to_string(timeinfo->tm_mday) + '.';
		else
			info += std::to_string(timeinfo->tm_mday) + '.';
		if(timeinfo->tm_mon < 10)
			info += '0' + std::to_string(timeinfo->tm_mon) + '.';
		else
			info += std::to_string(timeinfo->tm_mon) + '.';
		info += std::to_string(timeinfo->tm_year + 1900) + " | ";
		if(timeinfo->tm_hour < 10)
			info += '0' + std::to_string(timeinfo->tm_hour) + ':';
		else
			info += std::to_string(timeinfo->tm_hour) + ':';
		if(timeinfo->tm_min < 10)
			info += '0' + std::to_string(timeinfo->tm_min) + ':';
		else
			info += std::to_string(timeinfo->tm_min) + ':';
		if(timeinfo->tm_sec < 10)
			info += '0' + std::to_string(timeinfo->tm_sec);
		else
			info += std::to_string(timeinfo->tm_sec);
		return info;
	}

	DLLEXP bool VerifyFileExists(const wchar_t* filename)
	{
		return ::GetFileAttributes(filename) != DWORD(-1);
	}

	DLLEXP void DeleteSomeFile(const wchar_t* filePatch)
	{
		::DeleteFile(filePatch);
	}

}