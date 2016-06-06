#include <bat_audio_interface.h>

namespace BAT_ENGINE
{
	HRESULT CAudioCore::Initialize()
	{
		m_IsInit = true;
		return S_OK;
	}
	bool CAudioCore::IsInitialized()
	{
		return m_IsInit;
	}
}