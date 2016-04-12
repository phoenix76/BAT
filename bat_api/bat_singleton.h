#ifndef _BAT_SINGLETON_H_
#define _BAT_SINGLETON_H_

#include "bat_interfaces.h"

namespace BAT
{
	
	template<typename T>
	class _BAT_API_ ISingleton : INonCopyable
	{
	public:
		static T& Instance()
		{
			static T instance;
			return instance;
		}
	private:
		ISingleton() {}
	};
	
}
#endif