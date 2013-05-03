#ifndef __DOROTHY_MISC_OWN_H__
#define __DOROTHY_MISC_OWN_H__

NS_DOROTHY_BEGIN

/** @brief Used with Composition Relationship. */
template<class T>
class oOwn: public std::unique_ptr<T>
{
public:
	oOwn(){}
	oOwn(oOwn&& own):std::unique_ptr<T>(std::move(own)){}
	explicit oOwn(T* item):std::unique_ptr<T>(item){}
	inline operator T*() const
	{
		return get();
	}
	inline oOwn<T>& operator=(oOwn<T>&& own)
	{
		unique_ptr<T>::operator=(std::move(own));
		return *this;
	}
	inline operator bool() const
	{
		return get() != nullptr;
	}
private:
	oOwn(const oOwn& own);
};

/** Useless */
template<class T>
inline oOwn<T> __oOwnMake(T* item)
{
	return oOwn<T>(item);
}
#define oOwnMake(item) std::move(__oOwnMake(item))

NS_DOROTHY_END

#endif // __DOROTHY_MISC_OWN_H__