#ifndef _BAT_SINGLETON_H_
#define _BAT_SINGLETON_H_

#include "bat_interfaces.h"

namespace BAT
{

	template<typename T>
	class ISingleton : INonCopyable
	{
	public:
		static T& Instance()
		{
			static T instance;
			return instance;
		}
	private:
		explicit ISingleton<T>() { }
	};

}
#endif