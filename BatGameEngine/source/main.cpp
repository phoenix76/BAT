#include <bat_engine.h>

#include <dinput.h>
#include <iostream>

int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hpinst, LPSTR lp, int n)
{
	BAT::IEngine core;
	bool result = false;
	result = core.InitializeWithConfigFile();
	if(result)
	{
		while(core.Window()->IsRun())
		{
			MSG temp;
			temp = core.Window()->ProcessMessage();
			core.Input()->UpdateInput();
			if(core.Input()->GetKeyState(DIK_F))
				core.Window()->SystemAlert(L"DINPUT", L"MESSAGE");
			/*if(temp.message == WM_MBUTTONUP)
				core.Window()->HideAppCursor();
			if(temp.message == WM_RBUTTONUP)
				core.Window()->ShowAppCursor();
			if(temp.message == WM_LBUTTONUP)
				core.Window()->ChangeCursor(LoadCursor(NULL, IDC_APPSTARTING));
			if(temp.message == WM_KEYUP && temp.wParam != VK_ESCAPE)
				core.Window()->SystemAlert(L"KEYUP", L"System Alert");
			if(temp.message == WM_KEYUP && temp.wParam == VK_ESCAPE)
				core.Window()->Stop();*/
		}
		core.ShutdownEngine();
	}
	return 0;
}