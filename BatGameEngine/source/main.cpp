#include <bat_engine.h>

#include <iostream>

int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hpinst, LPSTR lp, int n)
{
	BAT::CBatCore core;
	core.Run();
	return 0;
}
/*
int main()
{
	BAT::CBatCore core;
	core.Run();

	std::cin.get();
	return 0;
}*/