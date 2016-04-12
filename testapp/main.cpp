#include <iostream>
#include "game_singletons.h"

using namespace BAT;

int main()
{
	ILogManager.Log("my func");
	ILogManager.Log("");
	std::cin.get();
	return 0;
}