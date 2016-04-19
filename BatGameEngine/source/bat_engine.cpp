#include <bat_engine.h>

namespace BAT
{
	CBatCore::CBatCore() : sConfig(&(ISingleton<CConfigManager>::Instance())), sLog(&(ISingleton<CLogManager>::Instance())), sWindow(&(ISingleton<CWindow>::Instance()))
	{
		sLog->LogToChannel("system", "engine class %f", 1.0f);
	}
	void CBatCore::Run()
	{
		sWindow->SetResolution(800U, 600U);
		sWindow->SetScreenMode(false);
		sWindow->Initialize();
		while(sWindow->IsRun())
		{
			sWindow->ProcessMessage();
		}
		sWindow->Shutdown();
	}
}