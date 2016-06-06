#include <bat_graphics_interface.h>

namespace BAT_ENGINE
{
	HRESULT CGraphicsCore::Initialize()
	{
		m_IsInit = true;
		return S_OK;
	}
	bool CGraphicsCore::IsInitialized()
	{
		return m_IsInit;
	}
}