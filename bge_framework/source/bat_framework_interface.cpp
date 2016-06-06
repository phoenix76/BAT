#include <bat_framework_interface.h>

namespace BAT_ENGINE
{
	HRESULT CFrameworkCore::Initialize()
	{
		m_IsInit = true;
		return S_OK;
	}
	bool CFrameworkCore::IsInitialized()
	{
		return m_IsInit;
	}
}