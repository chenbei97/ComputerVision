#pragma once
#ifndef stackNode_
#define stackNode_
// ���ܺ�<charter6_chainNode.h>�Ľṹ�幦����ȫһ��,������Ϊ�˷���ѽṹ���������������
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

