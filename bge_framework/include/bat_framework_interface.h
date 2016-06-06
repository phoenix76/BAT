#ifndef BAT_FRAMEWORK_INTERFACE_H
#define BAT_FRAMEWORK_INTERFACE_H

#include <bat_sys_macroses.h>

namespace BAT_ENGINE
{
	class DLLEXP CFrameworkCore
	{
	public:
		bool IsInitialized();

	protected:
		HRESULT Initialize();

		bool m_IsInit;
	};
}

#endif