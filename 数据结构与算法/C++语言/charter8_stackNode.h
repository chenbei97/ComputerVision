#pragma once
#ifndef stackNode_
#define stackNode_
// 功能和<charter6_chainNode.h>的结构体功能完全一样,这里是为了方便把结构体的名字重新命名
template<class T>
struct stackNode
{
	T element;
	stackNode<T>* next;
	stackNode() {}
	stackNode(const T& element) { this->element = element; }
	stackNode(stackNode<T>* next) { this->next = next; }
	stackNode(const T& element, stackNode<T>* next) { this->element = element; this->next = next; }
};
#endif // !stackNode_

