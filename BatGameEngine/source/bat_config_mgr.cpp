#include <bat_config_mgr.h>

#include <Windows.h>

namespace BAT
{
	CConfigManager::CConfigManager()
	{
		std::ifstream cfile("config.txt");
		if(!cfile.is_open())
			MessageBox(NULL, L"Error open cfg file!", L"Error", MB_OK);
		std::string temp = "";
		do
		{
			std::getline(cfile, temp);
			if(temp == "#DIRECTORIES")
			{
				while(cfile.get() != '=');
				std::getline(cfile, m_LogDirParam);
				while(cfile.get() != '=');
				std::getline(cfile, m_SavesDirParam);
				while(cfile.get() != '=');
				std::getline(cfile, m_KeyMapDirParam);
			}
			else if(temp == "#FILENAMES")
			{
				while(cfile.get() != '=');
				std::getline(cfile, m_KeyMapFileNameParam);
			}
		} while(!cfile.eof());
		cfile.close();
	}
	const std::string& CConfigManager::GetConfigParameter(EConfigParameters param) const
	{
		if(param == CONFIG_PARAM_LOG_DIR)
			return m_LogDirParam;
		else if(param == CONFIG_PARAM_SAVES_DIR)
			return m_SavesDirParam;
		else if(param == CONFIG_PARAM_KEYMAP_DIR)
			return m_KeyMapDirParam;
		else if(param == CONFIG_PARAM_KEYMAP_FILENAME)
			return m_KeyMapFileNameParam;
		return "";
	}
	CConfigManager::~CConfigManager()
	{
	}
	void CConfigManager::ReadKeyMapConfig()
	{
		std::ifstream cfile(m_KeyMapFileNameParam);
		if(!cfile.is_open())
			MessageBox(NULL, L"Error open keymap file!", L"Error", MB_OK);

		//.....

		cfile.close();
	}
}