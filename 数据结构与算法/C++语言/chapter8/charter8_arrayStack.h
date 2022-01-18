#pragma once
#ifndef charter8_arrayStack_
#define charter8_arrayStack_
#include "charter8_abstractStack.h"
#include "charter8_stackEmpty.h"
#include "charter1_illegalParameterValue.h"
#include <sstream>
// 不借助数组描述的线性表的具体类派生,直接通过抽象栈类派生具体了效率更高
// 如果借助数组线性表具体类派生,见头文件<charter8_derivedArrayStack.h>
template<class T>
class arrayStack : public abstractStack<T>
{
public:
    arrayStack(int initialCapacity = 10);
    ~arrayStack() { delete[] stack; }
    bool empty() const { return stackTop == -1; }
    int size() const{return stackTop + 1;}
    T& top();
    void pop();
    void push(const T& theElement);
    friend ostream& operator <<<>(ostream&, const arrayStack<T>&);
private:
    int stackTop;         // 栈顶元素对外索引是0,但是在内部是stack[stackTop],栈底是stack[0]
    int arrayLength;      // 栈容量
    T* stack;           // 存储栈元素
};

template<class T>
arrayStack<T>::arrayStack(int initialCapacity)
{
    if (initialCapacity < 1)
    {
        ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }
    arrayLength = initialCapacity;
    stack = new T[arrayLength];
    stackTop = -1; // 默认栈空此时为-1
}

template<class T>
T& arrayStack<T>::top()
{
    if (stackTop == -1)
        throw stackEmpty();
    return stack[stackTop]; 
}

template<class T>
void arrayStack<T>::pop()
{
    if (stackTop == -1) 
        throw stackEmpty();
    stack[stackTop--].~T();  // 直接析构掉stack的最后1个元素即可无需借助erase
}

template<class T>
void arrayStack<T>::push(const T& theElement)
{
    if (stackTop == arrayLength - 1) // 没有容量,扩充2倍
    {
        T* temp = new T[2 * arrayLength];
        std::copy(stack, stack + arrayLength, temp);
        delete[] stack;
        stack = temp;
        arrayLength *= 2;
    }
    stack[++stackTop] = theElement; // 先++,也就是在后1位存储该元素
}

template<class T>
ostream& operator <<<>(ostream&out, const arrayStack<T>& theStack)
{
    if (theStack.empty())
        out << "Stack is empty!" ;
    for (int i = 0; i < theStack.size(); i++)
    {
        out << theStack.stack[i] << "  ";
        if ((i + 1) % 10 == 0)
            out << endl;
    }    
    return out;
}
#endif // !charter8_arrayStack_