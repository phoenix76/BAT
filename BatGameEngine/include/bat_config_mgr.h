#ifndef _BAT_CONFIG_MGR_H_
#define _BAT_CONFIG_MGR_H_

#include "bat_platform.h"

#include <string>
#include <fstream>

namespace BAT
{
	enum EConfigParameters
	{
		CONFIG_PARAM_LOG_DIR = 0,
		CONFIG_PARAM_SAVES_DIR = 1,
		CONFIG_PARAM_KEYMAP_DIR = 2,

		CONFIG_PARAM_KEYMAP_FILENAME,
	};
	class CConfigManager
	{
	public:
		CConfigManager();
		const std::string& GetConfigParameter(EConfigParameters param) const;
		void ReadKeyMapConfig();
		~CConfigManager();

	private:
		std::string m_LogDirParam;
		std::string m_SavesDirParam;

		std::string m_KeyMapDirParam;
		std::string m_KeyMapFileNameParam;
	};
}

#endif