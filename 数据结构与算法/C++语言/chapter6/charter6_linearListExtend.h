#pragma once
// �Ƕ����Ա������linearList����չ��������clear��push_back�鷽��
#include "charter5_linearList.h"
template<class T>
class _charter6_linearListExtend : public _charter5_linearList<T>
{
public:
	virtual ~_charter6_linearListExtend() {}
	virtual void clear() = 0; 
	virtual void push_back(const T& theElement) = 0;
};
