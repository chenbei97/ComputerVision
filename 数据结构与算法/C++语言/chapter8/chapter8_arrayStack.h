#pragma once
#ifndef chapter8_arrayStack_
#define chapter8_arrayStack_
#include "chapter8_abstractStack.h"
#include "chapter8_stackEmpty.h"
#include "chapter1_illegalParameterValue.h"
#include <sstream>
// �������������������Ա�ľ���������,ֱ��ͨ������ջ������������Ч�ʸ���
// ��������������Ա����������,��ͷ�ļ�<charter8_derivedArrayStack.h>
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
    int stackTop;         // ջ��Ԫ�ض���������0,�������ڲ���stack[stackTop],ջ����stack[0]
    int arrayLength;      // ջ����
    T* stack;           // �洢ջԪ��
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
    stackTop = -1; // Ĭ��ջ�մ�ʱΪ-1
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
    stack[stackTop--].~T();  // ֱ��������stack�����1��Ԫ�ؼ����������erase
}

template<class T>
void arrayStack<T>::push(const T& theElement)
{
    if (stackTop == arrayLength - 1) // û������,����2��
    {
        T* temp = new T[2 * arrayLength];
        std::copy(stack, stack + arrayLength, temp);
        delete[] stack;
        stack = temp;
        arrayLength *= 2;
    }
    stack[++stackTop] = theElement; // ��++,Ҳ�����ں�1λ�洢��Ԫ��
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
#endif // !chapter8_arrayStack_