#include <bat_config_mgr.h>

#include <Windows.h>

namespace BAT
{

	CConfigManager::CConfigManager()
	{
	}
	bool CConfigManager::Initialize()
	{
		std::ifstream m_InFile("config.txt");
		if(!m_InFile.is_open())
		{
			MessageBox(NULL, L"Error open cfg file!", L"Error", MB_OK);
			return false;
		}

		while(m_InFile.get() != '=');	std::getline(m_InFile, m_FrameworkWidth);
		while(m_InFile.get() != '=');	std::getline(m_InFile, m_FrameworkHeight);
		while(m_InFile.get() != '=');	std::getline(m_InFile, m_FrameworkFullscreen);

		m_InFile.close();

		return true;
	}
	bool CConfigManager::GetValue(EConfigParameters param, std::string& target)
	{
		if(param == EConfigParameters::CP_WINDOW_WIDTH && m_FrameworkWidth != "")
		{
			target = m_FrameworkWidth;
			return true;
		}
		else if(param == EConfigParameters::CP_WINDOW_HEIGHT && m_FrameworkHeight != "")
		{
			target = m_FrameworkHeight;
			return true;
		}
		else if(param == EConfigParameters::CP_FULLSCREEN && m_FrameworkFullscreen != "")
		{
			target = m_FrameworkFullscreen;
			return true;
		}
		return false;
	}
	void CConfigManager::RewriteConfigFile()
	{
		m_OutFile.open("config.txt");
		if(m_OutFile.is_open())
		{
			m_OutFile << "Window width=" << m_FrameworkWidth << '\n';
			m_OutFile << "Window height=" << m_FrameworkHeight << '\n';
			m_OutFile << "Window Fullscreen=" << m_FrameworkFullscreen << '\n';

			m_OutFile.close();
		}
		else
			MessageBox(NULL, L"Error open config file for rewrite!", L"Error", MB_OK);
	}
	CConfigManager::~CConfigManager()
	{
	}
}