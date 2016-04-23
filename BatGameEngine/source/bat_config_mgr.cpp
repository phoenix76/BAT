#include <bat_config_mgr.h>

#include <Windows.h>

namespace BAT
{

	CConfig::CConfig()
	{
	}
	bool CConfig::Initialize()
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
	bool CConfig::GetValue(EConfigParameters param, std::string& target)
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
	CConfig::~CConfig()
	{
	}
}