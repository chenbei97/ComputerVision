#pragma once
#ifndef chapter9_queueNode_
#define chapter9_queueNode_
// ������stackNode�ڵ�
// ��������Ա��Ĺ��ܾ�������ṹ��ڵ�,���Դ洢������element��ָ����nextָ��
template<class T>
struct queueNode
{
	T data;
	queueNode<T>* next;
	// 4�ֹ���
	queueNode() {}
	queueNode(const T& data) { this->data = data; }
	queueNode(queueNode<T>* next) { this->next = next; }
	queueNode(const T& data, queueNode<T>* next) { this->data = data; this->next = next; }
};
#endif // !chapter9_queueNode_
