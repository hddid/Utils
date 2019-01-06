#ifndef ZHY_UTILS_ZHYSINGLETON_H
#define ZHY_UTILS_ZHYSINGLETON_H

template <class T>
class Singleton
{
public:
	/**
	* Create a static object
	* @return T*
	*/
	static T* Instance()
	{
		if (0 == s_instance)
		{
			s_instance = new T;
		}

		return s_instance;
	}

	/**
	* Destroy Singleton object
	*/
	static void Uninstance()
	{
		if (0 != s_instance)
		{
			delete s_instance;
			s_instance = 0;
		}
	}

protected:
	Singleton() {}
	virtual ~Singleton() {}

private:
	Singleton(const Singleton<T> &);
	Singleton<T>& operator= (const Singleton<T> &);

	static T* s_instance;
};

template <class T>
T* Singleton<T>::s_instance = 0;


#endif//ZHY_UTILS_ZHYSINGLETON_H
