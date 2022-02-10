#pragma once
#ifndef chapter12_abstractMinPriorityQueue_
#define chapter12_abstractMinPriorityQueue_
using namespace std;
template<class T>
class abstractMinPriorityQueue
{
public:
    virtual ~abstractMinPriorityQueue() {}
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual const T& top() = 0;
    virtual void pop() = 0;
    virtual void push(const T& theElement) = 0;
};
#endif // !chapter12_abstractMinPriorityQueue_
