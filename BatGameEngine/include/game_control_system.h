#ifndef _GAME_CONTROL_SYSTEM_H_
#define _GAME_CONTROL_SYSTEM_H_

#include <bat_engine.h>

namespace AO
{
	class CGlobalGameSystem
	{
	public:
		bool Initialize();
		void RunGame();
		void GameUpdate();
		void Shutdown();

	private:
		BAT::IEngine* m_pEngineCore;
		bool m_IsRun;

	};
}

#endif