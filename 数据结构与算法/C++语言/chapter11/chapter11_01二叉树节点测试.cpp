#include "chapter11_binaryTreeNode.h"
#include <iostream>
using namespace std;
void _chapter11_binaryTreeNode_testCode()
{
	binaryTreeNode<int> node;
	node.data = 5;
	binaryTreeNode<int> *leftSon, *rightSon;
	leftSon = new binaryTreeNode<int>(5); // ������û������
	rightSon = new binaryTreeNode<int>(10,
		new binaryTreeNode<int>(1),
		new binaryTreeNode<int>(2)); // ����������2������
	node.rightChild = rightSon;
	node.leftChild = leftSon;
	cout << node.leftChild << "  " << leftSon << endl; // ��ַ��һ����
	cout << node.rightChild->leftChild->data << endl;
}