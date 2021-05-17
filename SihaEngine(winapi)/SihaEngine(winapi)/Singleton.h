#pragma once

template <class T>
class CSingleton
{
private:
	static T* mSingleton;
public:
	CSingleton() {};
	~CSingleton()
	{
		delete mSingleton;
	}

	static T* GetInstance()
	{
		if (mSingleton == NULL)
		{
			mSingleton = new T();
		}
		return mSingleton;
	}
};


template <class T>T* CSingleton<T>::mSingleton = 0;