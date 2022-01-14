#pragma once
#ifndef charter8_linkedStack_
#define charter8_linkedStack_
#include "charter8_abstractStack.h"
#include "charter8_stackEmpty.h"
#include "charter8_stackNode.h"
template<class T>
class linkedStack : public abstractStack<T>
{
public:
    linkedStack(int initialCapacity = 10) { topNode = NULL; stackSize = 0; log = false; }
    //�����topNode��NULL,����topNode��ջ��
    //next�൱�����Զ����µ�2��Ԫ�ص�ַ,һ·��ջ���ٵ�NULL
    ~linkedStack();
    bool empty() const{return stackSize == 0;}
    int size() const{return stackSize;}
    T& top();
    void pop();
    void push(const T&);
    void isLog(bool log) { this->log = log; }
    friend ostream& operator <<<>(ostream&, const linkedStack<T>&);
private:
    stackNode<T>* topNode;  // ����������ʹ��T* stack�洢����,������������ʹ��topNode�洢
    // topNode.data����ľ�����������ʱT*stack�Ĵ洢����,�Ҷ�1��nextָ�빦��
    int stackSize; 
    bool log ;
};

template<class T>
linkedStack<T>::~linkedStack()
{
    while (topNode != NULL)
    {
        stackNode<T>* nextNode = topNode->next;
        if (log == true)
            cout << "xigou~~  "<<"top = "<<topNode<<"  next = "<<nextNode<< endl;
        delete topNode; // ɾ������ֵ�������������
        topNode = nextNode; // �ظ��������������һ��,topNode����һ������NULL
    }
}

template<class T>
T& linkedStack<T>::top()
{
    if (stackSize == 0)
        throw stackEmpty();
    return topNode->data; //��ʵ�����ݴ洢�ط�
}

template<class T>
void linkedStack<T>::push(const T& theElement )
{
    if (log == true)
        if (stackSize == 0 )
            cout << "0��" << "top = " << topNode <<"  previous = unknown"<<endl; // <<topNode->next �����
    // topNode����ָ�������Ľڵ�,����nextָ��ԭ���ĵ�topNode,���ʼ��topNode=NULL
    topNode = new stackNode<T>(theElement, topNode); //�൱��newTop->data=theElement,newTop->next=oldTop
    // ���յ�topNodeһ·next��ȥ����NULL,ͨ����topNode�ı������ɵõ��洢������
    stackSize++;
    if (log == true)
        cout << "Node("<<stackSize<<") = " << topNode << "  previous = " << topNode->next << "  value = " << theElement << endl;
        // �������Ϣ֪��ջ�׵�next����NULL,ջ��Ԫ����topNode,nextΪ��1��,һ·��ջ���ٵ�NULL
}

template<class T>
void linkedStack<T>::pop()
{
    if (stackSize == 0)
        throw stackEmpty();
    stackNode<T>* nextNode = topNode->next; // ��ônextNodeΪԭ���Զ����µĵ�2��Ԫ��
    delete topNode;
    topNode = nextNode; // ��2��Ԫ�س�Ϊ�µ�ջ��
    stackSize--;
}

template<class T>
ostream& operator <<<>(ostream& out, const linkedStack<T>& theStack)
{
    if (theStack.empty())
        out << "Stack is empty!";
    stackNode<T> *Node = theStack.topNode;
    int idx = 0;
    while (Node != NULL )
    {
        out << Node->data << "  ";
        if ((idx + 1) % 10 == 0)
            out << endl;
        Node = Node->next;
        idx++;
    }
    return out;
}
#endif // !charter8_linkedStack_
