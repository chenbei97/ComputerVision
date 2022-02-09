#include "chapter11_binaryTreeNode.h"
#include <iostream>
using namespace std;
void _chapter11_binaryTreeNode_testCode()
{
	binaryTreeNode<int> node;
	node.data = 5;
	binaryTreeNode<int> *leftSon, *rightSon;
	leftSon = new binaryTreeNode<int>(5); // 左子树没有子树
	rightSon = new binaryTreeNode<int>(10,
		new binaryTreeNode<int>(1),
		new binaryTreeNode<int>(2)); // 右子树还有2个子树
	node.rightChild = rightSon;
	node.leftChild = leftSon;
	cout << node.leftChild << "  " << leftSon << endl; // 地址是一样的
	cout << node.rightChild->leftChild->data << endl;
	cout << node << endl; // 测试<<重载
}