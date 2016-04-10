#ifndef _BAT_LOG_MGR_H_
#define _BAT_LOG_MGR_H_

#include "bat_platform.h"
#include "bat_singleton.h"
#include "bat_types.h"

#include <fstream>

namespace BAT
{

	class _BAT_API_ CLogManager : public CSingleton<CLogManager>, IManager
	{
		friend class CSingleton<CLogManager>;

	public:
		CLogManager();
		void Log(string msg);
		void CreateSingleton() override;

	private:
		std::ofstream m_LogFile;

	};

	_BAT_API_ CLogManager* ILogManager = &CLogManager::GetInstance();
}

#endif