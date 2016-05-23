#include <game_control_system.h>

#include <dinput.h>
#include <iostream>

int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hpinst, LPSTR lp, int n)
{
	AO::CGlobalGameSystem* pGame = new AO::CGlobalGameSystem;
	if(pGame->Initialize())
		pGame->RunGame();
	pGame->Shutdown();

	return 0;
}

