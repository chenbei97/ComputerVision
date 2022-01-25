#pragma once
#ifndef charter9_linkedQueue_
#define charter9_linkedQueue_
#include <sstream>
#include "charter9_abstractQueue.h"
#include "charter9_queueEmpty.h"
#include "charter9_queueNode.h"
using namespace std;
template<class T>
class linkedQueue : public abstractQueue<T>
{
public:
    linkedQueue(int initialCapacity = 10){queueBack=queueFront = NULL; queueSize = 0;}
    ~linkedQueue();
    bool empty() const{return queueSize == 0;}
    int size() const{return queueSize;}
    T& front();
    T& back();
    void pop();
    void push(const T&);
    void output(std::ostream &) const;
    friend ostream& operator <<<>(ostream&, const linkedQueue<T>&);
private:
    // 采用从头到尾的链接方式,初始时queueFront=queueBack=NULL
    // 当且仅当队列为空时queueFront=NULL,queueBack就是队尾元素,queue->next始终为NULL
    queueNode<T>* queueFront;  // 队首元素指针
    queueNode<T>* queueBack;   // 队尾元素指针
    int queueSize;            
};

template<class T>
linkedQueue<T>::~linkedQueue()
{
    while (queueFront != NULL) // 最终到达队尾就是NULL
    {
        queueNode<T>* nextNode = queueFront->next;
        delete queueFront;
        queueFront = nextNode;
    }
}

template<class T>
T& linkedQueue<T> ::front()
{
    if (queueSize == 0)
        throw queueEmpty();
    return queueFront->data;
}

template<class T>
T& linkedQueue<T> ::back()
{
    if (queueSize == 0)
        throw queueEmpty();
    return queueBack->data;
}

template<class T>
void linkedQueue<T>::pop()
{
    if (queueFront == NULL)
        throw queueEmpty();

    queueNode<T>* nextNode = queueFront->next;
    delete queueFront;
    queueFront = nextNode; // 类似于析构的代码,只是这里就删除1个
    queueSize--;
}

template<class T>
void linkedQueue<T>::push(const T& theElement)
{

   // 以新数据和NULL创建1个新节点,newNode->next=NULL,newNode->element=theElement
    queueNode<T>* newNode = new queueNode<T>(theElement, NULL);

    if (queueSize == 0)
        queueFront = newNode;       // 如果以前没节点,新节点就是队首节点
    else
        queueBack->next = newNode;  // 否则直接连接上原来的队尾节点和新节点
    queueBack = newNode; // 更新队尾节点

    queueSize++;
}

template<class T>
void linkedQueue<T>::output(ostream& out) const
{
    if (empty())
    {
        out << "the queue is empty!"<<endl; 
        return;
    }
    queueNode<T>* nextNode = queueFront;
    int idx = 0;
    while (nextNode != NULL)
    {
        out << nextNode->data << "  ";
        nextNode = nextNode->next;
        idx++;
        if (idx % 10 == 0)
            out << endl;
    }
    if (idx % 10 != 0 && idx != 0)
        out << endl;
}

template<class T>
ostream& operator <<<>(ostream& out, const linkedQueue<T>& theQueue)
{
    if (theQueue.empty())
        out << "the queue is empty!";
    else
        theQueue.output(out);
    return out;
}
#endif charter9_linkedQueue_