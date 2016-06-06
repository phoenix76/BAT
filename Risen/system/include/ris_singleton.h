#ifndef RIS_SINGLETON_H
#define RIS_SINGLETON_H

template<typename T>
class ISingleton
{
public:
	explicit ISingleton<T>() {}
	
	static T* Instance()
	{
		static T _instance;
		return &_instance;
	}
};

#endif