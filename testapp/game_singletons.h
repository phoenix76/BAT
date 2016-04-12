#ifndef _GAME_SINGLETONES_H_
#define _GAME_SINGLETONES_H_

#include <bat_log_mgr.h>
#include <bat_file_system.h>
#include <bat_singleton.h>

namespace BAT
{
	CLogManager& ILogManager = ISingleton<CLogManager>::Instance();
	CFileManager& IFileManager = ISingleton<CFileManager>::Instance();
}

#endif