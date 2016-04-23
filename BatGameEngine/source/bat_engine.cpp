#include <bat_engine.h>
#include <bat_config_mgr.h>

namespace BAT
{
	CBatCore::CBatCore() : m_pLog(&(ISingleton<CLogger>::Instance())), m_pWindow(&(ISingleton<CWindow>::Instance())), m_pConfig(&(ISingleton<CConfig>::Instance()))
	{
		m_pLog->RLog("system", "engine class %f", 1.0f);
	}
	bool CBatCore::InitializeWithConfigFile()
	{
		std::string fullscreen = "";
		bool result;
		std::string wWidth;
		std::string wHeight;

		if(m_pConfig->Initialize() == false)
		{
			m_pLog->RLog("system", "Error config init");
			return false;
		}
			m_pLog->DebugLog("system", "Config init succeded");

		if(m_pConfig->GetValue(CP_FULLSCREEN, fullscreen) == true && fullscreen == "true")
		{
			result = m_pWindow->InitializeWindow(L"Engine", LoadCursor(NULL, IDC_ARROW), WC_CREATE_WINDOW_FULLSCREEN);
			if(!result)
			{
				m_pLog->RLog("system", "Error create window");
				return false;
			}
			m_pLog->DebugLog("system", "Window init succeded");
		}
		else if(m_pConfig->GetValue(CP_WINDOW_WIDTH, wWidth) == true && m_pConfig->GetValue(CP_WINDOW_HEIGHT, wHeight) == true && wWidth != "" && wHeight != "")
		{
			result = m_pWindow->InitializeWindow(L"Engine", LoadCursor(NULL, IDC_ARROW), WC_CREATE_WINDOW_WITH_USER_SETTINGS, (uint32)atoi(wWidth.c_str()), (uint32)atoi(wHeight.c_str()));
			if(!result)
			{
				m_pLog->RLog("system", "Error create window");
				return false;
			}
			m_pLog->DebugLog("system", "Window init succeded");
		}
		return true;
	}
	CWindow* CBatCore::Window()
	{
		return m_pWindow;
	}
	CLogger* CBatCore::Log()
	{
		return m_pLog;
	}
}