#pragma once
#ifndef chapter9_abstractQueue_
#define chapter9_abstractQueue_
template<class T>
class abstractQueue
{
public:
	virtual ~abstractQueue() {}
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual T& front()  = 0;
	virtual T& back() = 0;
	virtual void pop() = 0;
	virtual void push(const T&) = 0;
};
#endif // !chapter9_abstractQueue_
