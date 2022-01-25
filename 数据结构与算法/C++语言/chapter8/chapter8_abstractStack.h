#pragma once
#ifndef chapter8_abstractStack_
#define chapter8_abstractStack_
template<class T>
class abstractStack
{
public:
	virtual ~abstractStack() {};
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual T& top() = 0;
	virtual void pop() = 0;
	virtual void push(const T& theElement) = 0;
};
#endif // !chapter8_abstractStack_
