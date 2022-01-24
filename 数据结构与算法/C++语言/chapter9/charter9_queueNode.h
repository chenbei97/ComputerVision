#pragma once
#ifndef queueNode_
#define queueNode_
// 类似于stackNode节点
// 链表比线性表多的功能就是这个结构体节点,可以存储数据域element和指针域next指针
template<class T>
struct queueNode
{
	T data;
	queueNode<T>* next;
	// 4种构造
	queueNode() {}
	queueNode(const T& data) { this->data = data; }
	queueNode(queueNode<T>* next) { this->next = next; }
	queueNode(const T& data, queueNode<T>* next) { this->data = data; this->next = next; }
};
#endif // !queueNode_
