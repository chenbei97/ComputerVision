#pragma once
#include "charter5_linearList.h"
#include "charter6_chainNode.h"
#include "myExceptions.h"
#include <sstream>
#include <ostream>
template<class T>
class _charter6_chainListCircular
{
public:
    _charter6_chainListCircular();
    int size() const { return listSize; }
    int indexOf(const T& theElement) const;
    void insert(int theIndex, const T& theElement);
    void output(ostream& out) const;

protected:
    void checkIndex(int theIndex) const;
    _charter6_chainNode<T>* headerNode;  // 头节点
    int listSize;            
};

template<class T>
_charter6_chainListCircular <T>::_charter6_chainListCircular()
{
    headerNode = new _charter6_chainNode<T>(); // 默认构造会带有1个头节点

    headerNode->next = headerNode;//头节点初始化绑定的信息就是自身
    listSize = 0;
}

template<class T>
void _charter6_chainListCircular<T>::checkIndex(int theIndex) const
{
    if (theIndex < 0 || theIndex >= listSize)
    {
        ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }

}

template<class T>
int _charter6_chainListCircular<T>::indexOf(const T& theElement) const
{
    headerNode->element = theElement; // 把查找的元素赋值给头节点的元素

    _charter6_chainNode<T>* currentNode = headerNode->next;
    int index = 0;  
    while (currentNode->element != theElement)//无需再比较currentNode!=NULL 只比较元素
    {
        currentNode = currentNode->next;
        index++;
    }

    if (currentNode == headerNode) // 只需要判断是否又回到头节点即可
        return -1;
    else
        return index;
}

template<class T>
void _charter6_chainListCircular<T>::insert(int theIndex, const T& theElement)
{
    if (theIndex < 0 || theIndex > listSize)
    {
        ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }

    _charter6_chainNode<T>* p = headerNode; // 头节点的指针
    for (int i = 0; i < theIndex; i++)
        p = p->next; // 因为不怕为空执行theIndex次就可以而不是theIndex-1次

    p->next = new _charter6_chainNode<T>(theElement, p->next);

    listSize++;
}

template<class T>
void _charter6_chainListCircular<T>::output(ostream& out) const
{
    for (_charter6_chainNode<T>* currentNode = headerNode->next;
        currentNode != headerNode; // 当前节点没有再次返回头节点的话就执行
        currentNode = currentNode->next)
        out << currentNode->element << "  ";
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const _charter6_chainListCircular<T>& x)
{
    x.output(out); return out;
}
