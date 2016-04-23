#include <bat_engine.h>

#include <iostream>

int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hpinst, LPSTR lp, int n)
{
	BAT::CBatCore core;
	bool result = false;
	result = core.InitializeWithConfigFile();
	if(result)
	{
		while(core.Window()->IsRun())
		{
			MSG temp;
			temp = core.Window()->ProcessMessage();
			if(temp.message == WM_MBUTTONUP)
				core.Window()->HideAppCursor();
			if(temp.message == WM_RBUTTONUP)
				core.Window()->ShowAppCursor();
			if(temp.message == WM_LBUTTONUP)
				core.Window()->ChangeCursor(LoadCursor(NULL, IDC_APPSTARTING));
			if(temp.message == WM_KEYUP && temp.wParam != VK_ESCAPE)
				core.Window()->SystemAlert(L"KEYUP", L"System Alert");
			if(temp.message == WM_KEYUP && temp.wParam == VK_ESCAPE)
				core.Window()->Stop();
		}
		core.Window()->Shutdown();
	}
	return 0;
}