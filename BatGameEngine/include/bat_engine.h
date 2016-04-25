#ifndef _BAT_ENGINE_H_
#define _BAT_ENGINE_H_

#include <bat_platform.h>
#include <bat_types.h>
#include <bat_singleton.h>
#include <bat_log_mgr.h>
#include <bat_memory.h>
#include <bat_window_api.h>
#include <bat_config_mgr.h>
#include <bat_input_mgr.h>
#include <bat_graphics_mgr.h>
#include <bat_sound_mgr.h>

namespace BAT
{

	class IEngine
	{
	public:
		IEngine();

		bool InitializeWithConfigFile();

		void ShutdownEngine();

		CWindowManager* Window();
		CLogManager* Log();
		CConfigManager* Config();
		CInputManager* Input();

	private:
		bool m_WindowInitializeWithConfig();
		bool m_InputIntialize();

		CConfigManager*		m_pConfig;
		CLogManager*		m_pLog;
		CWindowManager*		m_pWindow;
		CInputManager*		m_pInput;
		CGraphicsManager*	m_pGraphics;
		CSoundManager*		m_pSound;
	};

}

#endif