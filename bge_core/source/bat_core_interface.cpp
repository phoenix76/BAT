#include <bat_core_interface.h>

namespace BAT_ENGINE
{
	HRESULT CEngineCore::Initialize()
	{
		if(FAILED(CFrameworkCore::Initialize()))
		{
			BGE_Rls_Log("Error init framework");
			return E_FAIL;
		}
		else
			BGE_Dbg_Log("Init framework succeded");

		if(FAILED(CGraphicsCore::Initialize()))
		{
			BGE_Rls_Log("Error init graphics");
			return E_FAIL;
		}
		else
			BGE_Dbg_Log("Init graphics succeded");

		if(FAILED(CAudioCore::Initialize()))
		{
			BGE_Rls_Log("Error init audio");
			return E_FAIL;
		}
		else
			BGE_Dbg_Log("Init audio succeded");

		return S_OK;
	}
}