#include <bat_engine.h>

namespace BAT
{
	CBatCore::CBatCore() : sConfig(&(ISingleton<CConfigManager>::Instance())), sLog(&(ISingleton<CLogManager>::Instance()))
	{
		sLog->LogToChannel("system", "engine class %f", 1.0f);
	}
}