#include <bat_engine.h>

namespace BAT
{
	CBatCore::CBatCore() : /*sLog(&(ISingleton<CLogManager>::Instance())),*/ sWindow(&(ISingleton<CWindow>::Instance()))
	{
		/*sLog->LogToChannel("system", "engine class %f", 1.0f);*/
	}
	void CBatCore::Run()
	{
		bool result = false;
		result = sWindow->InitializeWindow(L"Engine", LoadCursor(NULL, IDC_ARROW), WC_CREATE_WINDOW_CONFIG_2);
		if(result)
		{
			while(sWindow->IsRun())
			{
				sWindow->ProcessMessage();
			}
			sWindow->Shutdown();
		}
	}
}