#include <bat_engine.h>
#include <bat_config_mgr.h>

namespace BAT
{
	IEngine::IEngine() : m_pLog(&(ISingleton<CLogManager>::Instance())), m_pWindow(&(ISingleton<CWindowManager>::Instance())), m_pConfig(&(ISingleton<CConfigManager>::Instance())),
		m_pInput(&(ISingleton<CInputManager>::Instance())), m_pGraphics(&(ISingleton<CGraphicsManager>::Instance())), m_pSound(&(ISingleton<CSoundManager>::Instance())),
		m_pFileSystem(&(ISingleton<CFileManager>::Instance()))
	{
	}
	bool IEngine::InitializeEngine()
	{
		
		//Config init
		if(m_pConfig->Initialize() == false)
		{
			m_pLog->RLog("system", "Error config init");
			return false;
		}
		m_pLog->DebugLog("system", "Config init succeded");

		//Window init
		if(!m_WindowInitialize())
		{
			m_pLog->RLog("system", "Error create window");
			return false;
		}
		m_pLog->DebugLog("system", "Window init succeded");

		//Input init
		if(!m_pInput->InitializeInputSystem(m_pWindow->GetHWND(), m_pWindow->GetInstance()))
		{
			m_pLog->RLog("system", "Error input init");
			return false;
		}
		m_pLog->DebugLog("system", "Input init succeded");

		//Sound init
		if(!m_pSound->Initialize(m_pWindow->GetHWND()))
		{
			m_pLog->RLog("system", "Sound input init");
			return false;
		}
		m_pLog->DebugLog("system", "Sound init succeded");

		m_pSound->PlayWaveFile();
		return true;
	}
	void IEngine::WindowUpdate()
	{
		m_pWindow->ProcessMessage();
	}
	void IEngine::InputUpdate()
	{
		POINT pt = m_pWindow->GetMouseCoordinates();
		m_pInput->UpdateInput(pt.x, pt.y);
	}
	void IEngine::ShutdownEngine()
	{
		m_pWindow->Shutdown();	
		m_pInput->Shutdown();
		m_pConfig->RewriteConfigFile();
		m_pSound->Shutdown();
	}

	CWindowManager* IEngine::Window()
	{
		return m_pWindow;
	}
	CLogManager* IEngine::Log()
	{
		return m_pLog;
	}
	CConfigManager* IEngine::Config()
	{
		return m_pConfig;
	}
	CInputManager* IEngine::Input()
	{
		return m_pInput;
	}

	bool IEngine::m_WindowInitialize()
	{
		std::string fullscreen = "";
		bool result;
		std::string wWidth;
		std::string wHeight;

		if(m_pConfig->GetValue(CP_FULLSCREEN, fullscreen) == true && fullscreen == "true")
		{
			result = m_pWindow->InitializeWindow(L"Engine", LoadCursor(NULL, IDC_ARROW), WC_CREATE_WINDOW_FULLSCREEN);
			if(!result)
				return false;
		}
		else if(m_pConfig->GetValue(CP_WINDOW_WIDTH, wWidth) == true && m_pConfig->GetValue(CP_WINDOW_HEIGHT, wHeight) == true)
		{
			result = m_pWindow->InitializeWindow(L"Engine", LoadCursor(NULL, IDC_ARROW), WC_CREATE_WINDOW_WITH_USER_SETTINGS, (uint32)atoi(wWidth.c_str()), (uint32)atoi(wHeight.c_str()));
			if(!result)
				return false;			
		}
		return true;
	}
}