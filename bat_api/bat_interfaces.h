#ifndef _BAT_INTERFACES_H_
#define _BAT_INTERFACES_H_

#include "bat_platform.h"

namespace BAT
{
	class _BAT_API_ INonCopyable
	{
	protected:
		INonCopyable()
		{

		}
		~INonCopyable()
		{

		}

	private:
		INonCopyable(const INonCopyable& other);
		const INonCopyable& operator=(const INonCopyable& other);
	};

	class _BAT_API_ IManager
	{
	public:
		virtual void CreateSingleton() = 0;
	};
}

#endif