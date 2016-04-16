#ifndef _BAT_INTERFACES_H_
#define _BAT_INTERFACES_H_

namespace BAT
{
	class INonCopyable
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
}

#endif