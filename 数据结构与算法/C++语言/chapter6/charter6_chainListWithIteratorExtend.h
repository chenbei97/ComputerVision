#pragma once
// 拓展的抽象类的具体类实现: 继承本抽象类,继承已经实现好的chainListWithIterator类
// 增加clear和push_back的方法实现,push_back需要1个私有成员lastNode指向尾节点
// 尾插时候就不必再使用insert函数,直接使用push_back函数,速度很快
// 但是insert和erase函数会改变尾节点,所以这2个函数要重写增加对lastNode的更新
// 本具体类还额外多了zero方法,头节点指向空以及listSize=0
#include <iostream>
#include <sstream>
#include <string>
#include "myExceptions.h"
#include "charter6_chainNode.h"
#include "charter6_linearListExtend.h" // 继承拓展
#include "charter6_chainListWithIterator.h" // 借助已经实现的chain修改2个函数和增加成员即可
template<class T>
class _charter6_chainListWithIteratorExtend : public _charter6_chainListWithIterator<T>, _charter6_linearListExtend<T>
{
public:
    // 构造函数不同于普通方法,需要继承_charter6_chainListWithIterator
    // 注意如何继承的形参,前后需要一致
    _charter6_chainListWithIteratorExtend(int initialCapacity = 10)  : 
        _charter6_chainListWithIterator<T>(initialCapacity) {} 
    _charter6_chainListWithIteratorExtend(const _charter6_chainListWithIteratorExtend<T>& theList) : 
        _charter6_chainListWithIterator<T>(theList) {}
    
    // 子类继承父类的同名函数会被覆盖,empty,size,get,indexOf,output都会被覆盖,this->无法调用父类
    // 构造函数、没有覆盖的方法checkIndex、<<重载，没有覆盖的类_charter6_iterator，普通成员firstNode、listSize都直接继承可被this调用
    // 如果想重写函数,erase,insert直接重写即可
    // 如果不想重写函数直接使用父类的方法,需要 class :: method的格式调用父类方法
    bool empty() const { return this->listSize == 0; }// 使用继承,自己写this->empy()是错误的,但是可以使用return this->listSize == 0和_charter6_chainListWithIterator<T>::empty();
    int size() const { return this->listSize; } // 自己写的话要记得返回this->listSize而不是listSize否则报错不识别 ,也可以return _charter6_chainListWithIterator<T>::listSize; 
    T& get(int theIndex) const
    {
        return _charter6_chainListWithIterator<T>::get(theIndex); // 使用继承调用方法
    }
    int indexOf(const T& theElement) const
    {
        return _charter6_chainListWithIterator<T>::indexOf(theElement);
    }
    void output(ostream& out) const
    {
        _charter6_chainListWithIterator<T>::output(out);
    }
    void clear()
    {
        // 和析构函数的代码一样
        while (this->firstNode != NULL)
        {
            _charter6_chainNode<T>* nextNode = this->firstNode->next;
            delete this->firstNode;
            this->firstNode = nextNode;
        }
        this->listSize = 0;
    }   // 需要实现
    void erase(int theIndex); // 重新实现
    void insert(int theIndex, const T& theElement); // 重新实现
    void push_back(const T& theElement);
    void zero()
    {
        this->firstNode = NULL; this->listSize = 0;
    }
protected:
    _charter6_chainNode<T>* lastNode;  // 尾节点指针
};

// erase函数重新实现
template<class T>
void _charter6_chainListWithIteratorExtend<T>::erase(int theIndex)
{
    this->checkIndex(theIndex); // 调用的是继承的方法
    _charter6_chainNode<T>* deleteNode;
    if (theIndex == 0)
    {
        deleteNode = this->firstNode;
        this->firstNode = this->firstNode->next;
    }
    else
    {  
        _charter6_chainNode<T>* p = this->firstNode;
        for (int i = 0; i < theIndex - 1; i++)
            p = p->next;

        deleteNode = p->next;
        p->next = p->next->next; 
        if (deleteNode == lastNode) // 增加的代码修改:如果index删除的是尾节点需要更新否则不需要
            lastNode = p; // 说明现在的p(index-1)是尾节点了,更新即可
    }
    this->listSize--;
    delete deleteNode;
}

// insert函数重新实现
template<class T>
void _charter6_chainListWithIteratorExtend<T>::insert(int theIndex, const T& theElement)
{
    if (theIndex < 0 || theIndex > this->listSize)
    {
        ostringstream s;
        s << "index = " << theIndex << " size = " << this->listSize;
        throw illegalIndex(s.str());
    }

    if (theIndex == 0)
    {
        this->firstNode = new _charter6_chainNode<T>(theElement, this->firstNode);
        // 和erase不同,清除的不是尾节点就不影响,insert一定会影响尾节点
        if (this->listSize == 0)
            lastNode = this->firstNode; // 如果一开始没有节点,插入的节点既是头节点也是尾节点
        // 如果一开始有头节点,且插入的节点在头节点之前,没有影响
        // 因为插入第2个元素必定已经插入了第1个元素,那时候lastNode就已经指向了头节点(也就是现在的第2个节点)
    }
    else
    { // 如果一开始有头节点,但是插入的节点是在头节点之后,就会有影响
        // 因为尾节点不是以前的头节点了,而是新创建的节点
        _charter6_chainNode<T>* p = this->firstNode;
        for (int i = 0; i < theIndex - 1; i++)
            p = p->next;
        p->next = new _charter6_chainNode<T>(theElement, p->next);//新创建的index节点的信息在上1个index-1(p)存储，如果是尾插theIndex=listSize，p执行了listSize-1次,p绑定的信息就是listSize位置的节点
        if (this->listSize == theIndex)//如果节点不是尾插,尾节点本身没有改变没有影响 lastNode依然指向了原本的尾节点
            lastNode = p->next; // 如果是尾插,说明p是新的尾节点的上一个(theIndex=listSize-1位置),p->next就是尾节点地址(theIndex=listSize位置)
    }
    this->listSize++;
}

// push_back的实现
template<class T>
void _charter6_chainListWithIteratorExtend<T>::push_back(const T& theElement)
{
    // 创建1个指向NULL的新节点的指针
    _charter6_chainNode<T>* newNode = new _charter6_chainNode<T>(theElement, NULL);
    if (this->firstNode == NULL) // 头节点不存在说明是空的链表,头尾相同和newNode一样
        this->firstNode = lastNode = newNode;
    else
    {  // 不为空链表
        lastNode->next = newNode;// lastNode绑定的下一节点指针指向更新
        lastNode = newNode; // lastNode更新
    }
    this->listSize++;
}
