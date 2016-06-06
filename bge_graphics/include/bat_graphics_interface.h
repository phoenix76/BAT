#ifndef BAT_GRAPHICS_INTERFACE_H
#define BAT_GRAPHICS_INTERFACE_H

#include <bat_sys_macroses.h>

namespace BAT_ENGINE
{
	class DLLEXP CGraphicsCore
	{
	public:
		bool IsInitialized();

	protected:
		HRESULT Initialize();

		bool m_IsInit;
	};
}

#endif