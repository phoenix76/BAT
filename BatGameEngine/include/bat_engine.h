#ifndef _BAT_ENGINE_H_
#define _BAT_ENGINE_H_

#include <bat_platform.h>
#include <bat_types.h>
#include <bat_singleton.h>
#include <bat_log_mgr.h>
#include <bat_memory.h>
#include <bat_window_api.h>
#include <bat_config_mgr.h>

namespace BAT
{

	class CBatCore
	{
	public:
		CBatCore();
		bool InitializeWithConfigFile();
		CWindow* Window();
		CLogger* Log();

	private:

		CConfig* m_pConfig;
		CLogger* m_pLog;
		CWindow* m_pWindow;
	};

}

#endif