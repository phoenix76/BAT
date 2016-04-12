#include "bat_log_mgr.h"
#include <iostream>

namespace BAT
{
	CLogManager::CLogManager()
	{
		m_LogFile.open("logfile.txt");
		std::cout << "Logfile create";
	}
	void CLogManager::Log(string msg)
	{
		m_LogFile << msg << '\n';
	}
}