#ifndef BAT_AUDIO_INTERFACE_H
#define BAT_AUDIO_INTERFACE_H

#include <bat_sys_macroses.h>

namespace BAT_ENGINE
{
	class DLLEXP CAudioCore
	{
	public:
		bool IsInitialized();

	protected:
		HRESULT Initialize();

		bool m_IsInit;
	};
}

#endif