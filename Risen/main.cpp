#include <Windows.h>
#include "system\include\ris_api_connector.h"

int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hpinst, LPSTR lp, int n)
{
	BGE_Engine->Initialize();
	BGE_Dbg_Log("test %d", BGE_Engine->QueryInterface()->Audio()->IsInitialized());
	return 0;
}