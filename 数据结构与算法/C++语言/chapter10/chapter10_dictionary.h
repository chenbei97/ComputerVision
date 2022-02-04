#pragma once
#ifndef chapter10_dictionary_
#define chapter10_dictionary_
/*
template <class _Ty1, class _Ty2>
struct pair { // store a pair of values
	using first_type  = _Ty1;
	using second_type = _Ty2;
*/
template<class K , class V> // (key,value)
class dictionary
{
public :
	virtual ~dictionary() {};
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual std::pair<const K, V>* find(const K&) const = 0; // key是const的
	virtual void erase(const K&) = 0;
	virtual void insert(const std::pair<const K, V>&) = 0;
};
// pair必须指定<_T1,_T2>类型
#endif // !chapter10_dictionary_
