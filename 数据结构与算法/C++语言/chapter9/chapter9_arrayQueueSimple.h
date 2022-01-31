#pragma once
#ifndef chapter9_arrayQueueSimple_
#define chapter9_arrayQueueSimple_
#include <sstream>
#include "chapter9_abstractQueue.h"
#include "chapter9_queueEmpty.h"
#include "chapter1_illegalParameterValue.h"
// 这个类是arrayQueue的简化版,删除log函数和各种不必要的打印信息,方便队列的后续使用(主要是工厂问题)
using namespace std;
template<class T>
class arrayQueueSimple : public abstractQueue<T>
{
public:
    arrayQueueSimple(int initialCapacity = 10);
    ~arrayQueueSimple() { if (queue != NULL) queue = NULL; delete[] queue; }
    bool empty() const { return theFront == theBack; }
    int size() const;
    T& front();
    T& back();
    void pop();
    void push(const T&);
    friend ostream& operator<<<>(ostream&, arrayQueueSimple<T>&);
    void output(ostream&) const;
private:
    int theFront;      
    int theBack;       
    int arrayLength;
    T* queue;
    bool isPop; 
};

template<class T>
arrayQueueSimple<T> ::arrayQueueSimple(int initialCapacity)
{
    if (initialCapacity < 1)
    {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }
    arrayLength = initialCapacity; // 还可以改变
    queue = new T[arrayLength];
    theFront = 0; // 初始位置都是0
    theBack = 0;
    isPop = false;
};

template<class T>
int arrayQueueSimple<T>::size() const
{
    if (theBack > theFront) // 这段程序和下方注释的程序完全等价
        return theBack - theFront;
    else
        return arrayLength + theBack - theFront;
    // return (theBack - theFront + arrayLength) % arrayLength;
}

template<class T>
T& arrayQueueSimple<T> ::front()
{
    if (theFront == theBack)
        throw queueEmpty();
    return queue[(theFront + 1) % arrayLength];
};

template<class T>
T& arrayQueueSimple<T> ::back()
{
    if (theFront == theBack)
        throw queueEmpty();
    return queue[theBack]; // theBack就是尾部元素的实际位置
};

template<class T>
void arrayQueueSimple<T> ::pop()
{
    if (theFront == theBack)
        throw queueEmpty();
    theFront = (theFront + 1) % arrayLength; 
    queue[theFront].~T();  
    isPop = true;
};

template<class T>
void arrayQueueSimple<T>::output(ostream& out) const
{
    if (empty())
    {
        out << "theQueue don't have any elements! you can add it.";
        return;
    }

    if (isPop)
    {
        for (int i = 0; i < arrayLength; i++) 
        {
            if (theFront > theBack)
            {
                if (i <= theBack || i > theFront)
                    out << queue[i] << " ";
            }
            else
            {
                if (i <= theBack && i > theFront)
                    out << queue[i] << " ";
            }
            if ((i + 1) % 5 == 0)
                out << endl;
        }
    }
    else
    {
        for (int i = 0; i <= theBack; i++) 
        {
            if (i != theFront)
                out << queue[i] << " ";
            if ((i + 1) % 5 == 0)
                out << endl;
        }
    }
}

template<class T>
ostream& operator<<<>(ostream& out, arrayQueueSimple<T>& theQueue)
{
    theQueue.output(out);
    return out;
}

template<class T>
void arrayQueueSimple<T> ::push(const T& theElement)
{
    if ((theBack + 1) % arrayLength == theFront)
    {
        T* newQueue = new T[2 * arrayLength];
        int start = (theFront + 1) % arrayLength; 
        if (start < 2) 
            copy(queue + start, queue + start + arrayLength - 1, newQueue);
        else
        {
            copy(queue + start, queue + arrayLength, newQueue);
            copy(queue, queue + theBack + 1, newQueue + arrayLength - start);
        }
        theFront = 2 * arrayLength - 1;
        theBack = arrayLength - 1 - 1;   
        arrayLength *= 2;
        queue = newQueue;
    }
    theBack = (theBack + 1) % arrayLength;
    queue[theBack] = theElement;
};
#endif // !chapter9_arrayQueueSimple_

