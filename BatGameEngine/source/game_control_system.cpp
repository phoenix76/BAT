#include <game_control_system.h>

namespace AO
{
	bool CGlobalGameSystem::Initialize()
	{
		m_pEngineCore = new BAT::IEngine();
		if(!m_pEngineCore->InitializeEngine())
			return false;
		return true;
	}
	void CGlobalGameSystem::RunGame()
	{
		m_IsRun = true;
		while(m_IsRun)
		{
			m_pEngineCore->WindowUpdate();
			m_pEngineCore->InputUpdate();
			GameUpdate();
		}
	}
	void CGlobalGameSystem::GameUpdate()
	{
		int32 x, y;
		m_pEngineCore->Input()->GetMouseState(BAT::EMouseParams::MP_CURPOS, x, y);
		if(m_pEngineCore->Input()->GetKeyState(DIK_K))
			m_pEngineCore->Window()->SystemAlert((std::to_wstring(x) + std::to_wstring(y)).c_str(), L"Engine");
		if(m_pEngineCore->Input()->GetKeyState(DIK_F))
			m_IsRun = false;
	}
	void CGlobalGameSystem::Shutdown()
	{
		m_pEngineCore->ShutdownEngine();
		delete m_pEngineCore;
	}
}