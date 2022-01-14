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
    //最初的topNode是NULL,最后的topNode是栈顶
    //next相当于是自顶向下第2个元素地址,一路到栈底再到NULL
    ~linkedStack();
    bool empty() const{return stackSize == 0;}
    int size() const{return stackSize;}
    T& top();
    void pop();
    void push(const T&);
    void isLog(bool log) { this->log = log; }
    friend ostream& operator <<<>(ostream&, const linkedStack<T>&);
private:
    stackNode<T>* topNode;  // 数组描述的使用T* stack存储数据,链表描述则是使用topNode存储
    // topNode.data代替的就是数组描述时T*stack的存储功能,且多1个next指针功能
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
        delete topNode; // 删除的是值而不是这个属性
        topNode = nextNode; // 重复等于它自身的下一个,topNode的下一个总是NULL
    }
}

template<class T>
T& linkedStack<T>::top()
{
    if (stackSize == 0)
        throw stackEmpty();
    return topNode->data; //真实的数据存储地方
}

template<class T>
void linkedStack<T>::push(const T& theElement )
{
    if (log == true)
        if (stackSize == 0 )
            cout << "0：" << "top = " << topNode <<"  previous = unknown"<<endl; // <<topNode->next 会出错
    // topNode总是指向新增的节点,并让next指向原来的的topNode,最初始的topNode=NULL
    topNode = new stackNode<T>(theElement, topNode); //相当于newTop->data=theElement,newTop->next=oldTop
    // 最终的topNode一路next下去就是NULL,通过对topNode的遍历即可得到存储的数据
    stackSize++;
    if (log == true)
        cout << "Node("<<stackSize<<") = " << topNode << "  previous = " << topNode->next << "  value = " << theElement << endl;
        // 从输出信息知道栈底的next就是NULL,栈顶元素是topNode,next为下1个,一路到栈底再到NULL
}

template<class T>
void linkedStack<T>::pop()
{
    if (stackSize == 0)
        throw stackEmpty();
    stackNode<T>* nextNode = topNode->next; // 那么nextNode为原来自顶向下的第2个元素
    delete topNode;
    topNode = nextNode; // 第2个元素成为新的栈顶
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
