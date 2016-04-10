#ifndef _BAT_SINGLETON_H_
#define _BAT_SINGLETON_H_

#include "bat_memory.h"
#include "bat_interfaces.h"

namespace BAT
{
	template <typename T>
	class _BAT_API_ CSingleton : INonCopyable
	{
	public:
		static T& GetInstance()
		{
			static T _instance;
			return _instance;
		}

	protected:
		explicit CSingleton<T>() {}
	};
}
#endif