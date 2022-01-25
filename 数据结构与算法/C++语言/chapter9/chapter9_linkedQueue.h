#pragma once
#ifndef chapter9_linkedQueue_
#define chapter9_linkedQueue_
#include <sstream>
#include "chapter9_abstractQueue.h"
#include "chapter9_queueEmpty.h"
#include "chapter9_queueNode.h"
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
    // ���ô�ͷ��β�����ӷ�ʽ,��ʼʱqueueFront=queueBack=NULL
    // ���ҽ�������Ϊ��ʱqueueFront=NULL,queueBack���Ƕ�βԪ��,queue->nextʼ��ΪNULL
    queueNode<T>* queueFront;  // ����Ԫ��ָ��
    queueNode<T>* queueBack;   // ��βԪ��ָ��
    int queueSize;            
};

template<class T>
linkedQueue<T>::~linkedQueue()
{
    while (queueFront != NULL) // ���յ����β����NULL
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
    queueFront = nextNode; // �����������Ĵ���,ֻ�������ɾ��1��
    queueSize--;
}

template<class T>
void linkedQueue<T>::push(const T& theElement)
{

   // �������ݺ�NULL����1���½ڵ�,newNode->next=NULL,newNode->element=theElement
    queueNode<T>* newNode = new queueNode<T>(theElement, NULL);

    if (queueSize == 0)
        queueFront = newNode;       // �����ǰû�ڵ�,�½ڵ���Ƕ��׽ڵ�
    else
        queueBack->next = newNode;  // ����ֱ��������ԭ���Ķ�β�ڵ���½ڵ�
    queueBack = newNode; // ���¶�β�ڵ�

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
#endif chapter9_linkedQueue_