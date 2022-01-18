#pragma once
#ifndef stackNode_
#define stackNode_
// ���ܺ�<charter6_chainNode.h>�Ľṹ�幦����ȫһ��,������Ϊ�˷���ѽṹ���������������
// ��������Ա��Ĺ��ܾ�������ṹ��ڵ�,���Դ洢������element��ָ����nextָ��
template<class T>
struct stackNode
{
	T data;
	stackNode<T>* next;
	// 4�ֹ���
	stackNode() {}
	stackNode(const T& data) { this->data = data; }
	stackNode(stackNode<T>* next) { this->next = next; }
	stackNode(const T& data, stackNode<T>* next) { this->data= data; this->next = next; }
};
#endif // !stackNode_

