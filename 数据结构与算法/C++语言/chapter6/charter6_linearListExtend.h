#pragma once
// 是对线性表抽象类linearList的拓展，增加了clear和push_back虚方法
#include "charter5_linearList.h"
template<class T>
class _charter6_linearListExtend : public _charter5_linearList<T>
{
public:
	virtual ~_charter6_linearListExtend() {}
	virtual void clear() = 0; 
	virtual void push_back(const T& theElement) = 0;
};
