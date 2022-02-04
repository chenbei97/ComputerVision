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
	virtual std::pair<const K, V>* find(const K&) const = 0; // key��const��
	virtual void erase(const K&) = 0;
	virtual void insert(const std::pair<const K, V>&) = 0;
};
// pair����ָ��<_T1,_T2>����
#endif // !chapter10_dictionary_
