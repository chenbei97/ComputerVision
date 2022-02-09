#pragma once
#ifndef chapter11_binaryTreeNode_
#define chapter11_binaryTreeNode_
using namespace std;
#include <iostream>
template<class T>
struct binaryTreeNode
{
	T data;
	
	binaryTreeNode<T>* leftChild, // 左子树
									* rightChild; // 右子树
	// 默认构造
	binaryTreeNode() { leftChild = nullptr; rightChild = nullptr; }
	// 初始化数据域的构造
	binaryTreeNode(const T& theData):data(theData)
	{
		leftChild = rightChild = nullptr;
	}
	// 初始化数据域和指针域的构造
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
