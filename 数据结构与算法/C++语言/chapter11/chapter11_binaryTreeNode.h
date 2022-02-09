#pragma once
#ifndef chapter11_binaryTreeNode_
#define chapter11_binaryTreeNode_
using namespace std;
#include <iostream>
template<class T>
struct binaryTreeNode
{
	T data;
	
	binaryTreeNode<T>* leftChild, // ������
									* rightChild; // ������
	// Ĭ�Ϲ���
	binaryTreeNode() { leftChild = nullptr; rightChild = nullptr; }
	// ��ʼ��������Ĺ���
	binaryTreeNode(const T& theData):data(theData)
	{
		leftChild = rightChild = nullptr;
	}
	// ��ʼ���������ָ����Ĺ���
	binaryTreeNode(const T& theData, 
		binaryTreeNode* theLeftChild, 
		binaryTreeNode* theRightChild):data(theData)
	{
		leftChild = theLeftChild;
		rightChild = theRightChild;
	}
};
template<class T>
inline ostream& operator<<(ostream& out, const binaryTreeNode<T>& x)
{
	out << x.data << "  ";
	return out;
}
#endif // !chapter11_binaryTreeNode_
