/***********************************
 *
 * file Singleton.h
 * ingroup GroupName
 * TODO: long description
 * author Haoyu_Zeng
 * version 1.0
 * date  2018/08/31 20:20
 * E-mail: 1150566379@qq.com
 *
 ***********************************/
#ifndef ZHY_UTILS_SINGLETON_H
#define ZHY_UTILS_SINGLETON_H

/**
* @class Singleton
* @brief This is a template class for managing singleton objects allocated
* on the heap.
* For example
* class Test : public Singleton<Test>
* {
*		friend class Singleton<Test>;
* }
*/
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
	Singleton(const Singleton<T> &) = delete;
	Singleton<T>& operator= (const Singleton<T> &) = delete;

	static T* s_instance;
};

template <class T>
T* Singleton<T>::s_instance = 0;

#endif//ZHY_UTILS_SINGLETON_H
