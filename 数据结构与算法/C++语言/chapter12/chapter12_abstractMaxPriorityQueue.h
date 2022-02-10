#pragma once
#ifndef chapter12_abstractMaxPriorityQueue_
#define chapter12_abstractMaxPriorityQueue_
using namespace std;
template<class T>
class abstractMaxPriorityQueue
{
public:
    virtual ~abstractMaxPriorityQueue() {}
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual const T& top() = 0;
    virtual void pop() = 0;
    virtual void push(const T& theElement) = 0;
};
#endif // !chapter12_abstractMaxPriorityQueue_
