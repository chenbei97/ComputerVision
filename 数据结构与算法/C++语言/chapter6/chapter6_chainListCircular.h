#pragma once
#ifndef chapter6_chainListCircular_
#define chapter6_chainListCircular_
#include "chapter5_linearList.h"
#include "chapter6_chainNode.h"
#include "myExceptions.h"
#include <sstream>
#include <ostream>
template<class T>
class _chapter6_chainListCircular
{
public:
    _chapter6_chainListCircular();
    int size() const { return listSize; }
    int indexOf(const T& theElement) const;
    void insert(int theIndex, const T& theElement);
    void output(ostream& out) const;

protected:
    void checkIndex(int theIndex) const;
    _chapter6_chainNode<T>* headerNode;  // 头节点,就是firstNode
    int listSize;            
};

template<class T>
_chapter6_chainListCircular <T>::_chapter6_chainListCircular()
{
    headerNode = new _chapter6_chainNode<T>(); // 默认构造会带有1个头节点

    headerNode->next = headerNode;//头节点初始化绑定的信息就是自身
    listSize = 0;
}

template<class T>
void _chapter6_chainListCircular<T>::checkIndex(int theIndex) const
{
    if (theIndex < 0 || theIndex >= listSize)
    {
        ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }

}

template<class T>
int _chapter6_chainListCircular<T>::indexOf(const T& theElement) const
{
    headerNode->element = theElement; // 把查找的元素赋值给头节点的元素

    _chapter6_chainNode<T>* currentNode = headerNode->next; // 注意指针指向的不是头节点而是首节点
    int index = 0;  
    while (currentNode->element != theElement)//无需再比较currentNode!=NULL 只比较元素,从首节点开始判断的
    {
        currentNode = currentNode->next; // index如果到达了listSize-1判断不等,下一个是listSize
        index++; // 此时currentNode = headerNone还是可以继续判断的,且headerNone已经赋值就是theElement,发现相等后退出循环
    }

    if (currentNode == headerNode) // 只需要判断是否又回到头节点即可 while退出循环时必定是headerNone
        return -1;
    else
        return index;
}

template<class T>
void _chapter6_chainListCircular<T>::insert(int theIndex, const T& theElement)
{
    if (theIndex < 0 || theIndex > listSize)
    {
        ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }

    _chapter6_chainNode<T>* p = headerNode; // 头节点的指针是真实的头节点,和首节点不相等
    for (int i = 0; i < theIndex; i++)
        p = p->next; 
    p->next = new _chapter6_chainNode<T>(theElement, p->next); 
    // 如果是头插不会执行for,用自身构建新节点,这个新节点指回了头节点,再让当前的头指针指向新节点即可
    // 如果不是头插,p总是移动theIndex次指向插入位置的前1个,因为头节点不是首节点
    // 用p指向的下一个也就是第theIndex个节点构建新的,再更新p指向这个新节点,这点是相同的
    // 特别的是尾插,theIndex=listSize时,p指向的就是listSize-1,这个节点在头插时已经指回了头节点
    // 构建的新节点也有这个信息,此时p更新指向新节点,新节点指向headerNode
    
    /*
    由于循环节点,不必分是不是头插,都以p->next构建,headerNode初始化指向的是自己而不是NULL
    比较原本的代码实现
    if (theIndex == 0)
        this->firstNode = new _charter6_chainNode<T>(theElement, firstNode); ①
    else
    {
        _charter6_chainNode<T>* p = firstNode; ②
        for (int i = 0; i < theIndex - 1; i++) ③
                p = p->next; ④
        p->next = new _charter6_chainNode<T>(theElement, p->next); ⑤
    }
    ① 该行代码和原来的完全一致没有变化
            如果是头插,则构造的新节点以原本的firstNode(构造函数中已经指向NULL)的信息构造的,再更新首节点指向这个节点
           头插的过程在charter6_chainListWithIterator.h已经详细说明
           
    ② 如果链表不是头插,构造1个首节点指针,这个指针总会运行到插入的节点的前1个位置
    ③ theIndex取值范围为[1,listSize] 至少已经有1个节点且该节点的next在①中准备好了(尾节点指向NULL)
         1. 取1,④不执行,当前的p就是指向firstNode(0),即插入位置的前1个
         2. 取2,④执行1次,当前p指向位置1,是插入位置的前1个
         3. 取index,④执行index-1次,p指向位置index-1,是插入位置的前1个
         4. 取listSize-1,④执行listSize-2次,p指向位置listSize-2
            是插入位置listSize-1(尾节点)的前1个(也是尾节点的前1个,倒数第2个)
         5. 取listSize,④执行listSize-1次,p指向位置listSize-1,这说明插入的节点是尾插(紧跟)
    ⑤  以当前p指向的节点信息(插入位置的上1个)来构造新节点(上1个才有插入位置这个节点信息)
          插入操作就是2个核心,上一个节点的next指向新的节点,同时新的节点继续保留原来的信息(构造的时候就保留了原节点的信息)
          1. 取1,用1节点信息构建的新节点移动到2号节点(就是移动),现在的1节点(就是p)指向了新节点(2号节点)的地址
          2. 取2,同理p移动到2号节点(位置1),用它的信息(下1个是NULL)构建新节点,再更新p指向这个新节点
          3. 取index,p指向index-1,以index(p->next)构建新节点(包含了p->next->next信息),再让p指向新节点即可
          4. 取listSize-1,以listSize-1的节点(listSize-2 ->next)构建新节点(包含了listSize-1的信息),再让p->next指向构建的新节点
          5. 取listSize,以listSize-1的next(是NULL)构建新节点,p->next从listSize-1指向了NULL新节点
*/
    listSize++;
}

template<class T>
void _chapter6_chainListCircular<T>::output(ostream& out) const
{
    for (_chapter6_chainNode<T>* currentNode = headerNode->next;
        currentNode != headerNode; // 当前节点没有再次返回头节点的话就执行
        currentNode = currentNode->next)
        out << currentNode->element << "  ";
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const _chapter6_chainListCircular<T>& x)
{
    x.output(out); return out;
}
#endif chapter6_chainListCircular_