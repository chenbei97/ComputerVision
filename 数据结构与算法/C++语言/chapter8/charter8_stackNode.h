#pragma once
#ifndef stackNode_
#define stackNode_
// 功能和<charter6_chainNode.h>的结构体功能完全一样,这里是为了方便把结构体的名字重新命名
// 链表比线性表多的功能就是这个结构体节点,可以存储数据域element和指针域next指针
template<class T>
struct stackNode
{
	T data;
	stackNode<T>* next;
	// 4种构造
	stackNode() {}
	stackNode(const T& data) { this->data = data; }
	stackNode(stackNode<T>* next) { this->next = next; }
	stackNode(const T& data, stackNode<T>* next) { this->data= data; this->next = next; }
};
#endif // !stackNode_

