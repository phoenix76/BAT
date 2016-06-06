#ifndef BAT_CFG_READER_H
#define BAT_CFG_READER_H

#include <bat_sys_macroses.h>
#include <string>
#include <vector>

namespace BAT_ENGINE
{
	class DLLEXP CConfigLoader
	{
		bool ReadFile();

		std::string GetParam(const std::string& param);

	private:
		std::vector<std::pair<std::string, std::string>> m_ParamsList;
	};
}

#endif