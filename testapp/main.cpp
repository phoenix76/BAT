#include <iostream>
#include <bat_log_mgr.h>

using namespace BAT;

int main()
{
	ILogManager->CreateSingleton();
	ILogManager->CreateSingleton();
	ILogManager->Log("Log() func");
	std::cin.get();
	return 0;
}