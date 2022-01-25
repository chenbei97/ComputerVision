#pragma once
#ifndef chapter6_linearListExtend_
#define chapter6_linearListExtend_
// 是对线性表抽象类linearList的拓展，增加了clear和push_back虚方法
#include "chapter5_linearList.h"
template<class T>
class _chapter6_linearListExtend : public _chapter5_linearList<T>
{
public:
	virtual ~_chapter6_linearListExtend() {}
	virtual void clear() = 0; 
	virtual void push_back(const T& theElement) = 0;
};
#endif // !chapter6_linearListExtend_