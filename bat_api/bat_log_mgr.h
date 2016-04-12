#ifndef _BAT_LOG_MGR_H_
#define _BAT_LOG_MGR_H_

#include "bat_platform.h"
#include "bat_singleton.h"
#include "bat_types.h"

#include <fstream>

namespace BAT
{

	class _BAT_API_ CLogManager
	{
	public:
		CLogManager();
		void Log(string msg);

	private:
		std::ofstream m_LogFile;

	};
}

#endif