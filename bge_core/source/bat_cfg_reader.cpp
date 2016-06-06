#include <bat_cfg_reader.h>
#include <bat_win_utils.h>

#include <fstream>

namespace BAT_ENGINE
{
	bool CConfigLoader::ReadFile()
	{
		if(!BAT_UTILS::VerifyFileExists(L"configs\\system.ini"))
			return false;
		std::ifstream file("configs/system.ini", std::ios::app);
		std::vector<std::string> tmpParams;
		std::string temp = "";

		std::getline(file, temp);
		if(file.eof())
			return false;
		while(true)
		{
			m_ParamsList.push_back(std::pair<std::string, std::string>(temp.substr(0, temp.find('=')), temp.substr(temp.find('=') + 1, temp.length())));
			std::getline(file, temp);
			if(file.eof())
			{
				m_ParamsList.push_back(std::pair<std::string, std::string>(temp.substr(0, temp.find('=')), temp.substr(temp.find('=') + 1, temp.length())));
				break;
			}
		}
		return true;
	}

	std::string CConfigLoader::GetParam(const std::string& param)
	{
		for(auto it = m_ParamsList.begin(); it != m_ParamsList.end(); it++)
		{
			if(it->first == param)
				return it->second;
		}
		return std::string("NULL");
	}

}