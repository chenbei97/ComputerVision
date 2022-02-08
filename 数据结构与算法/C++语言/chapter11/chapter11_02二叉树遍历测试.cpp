#include "chapter11_binaryTreeNode.h"
#include "chapter9_arrayQueueSimple.h"
#include <iostream>
using namespace std;
void binaryTree_preOrder(binaryTreeNode<string>* root);
void binaryTree_inOrder(binaryTreeNode<string>* root);
void binaryTree_postOrder(binaryTreeNode<string>* root);
void binaryTree_levelOrder(binaryTreeNode<string>* root);
void printTreeNode(binaryTreeNode<string>* node);
void _chapter11_binaryTree_through()
{
	// 使用指针new出来的会有影响
	// binaryTreeNode<string>* p_preOrder = A;p_preOrder的移动也会改变A的指向
	//binaryTreeNode<string> *A = new binaryTreeNode<string> ("A");
	//binaryTreeNode<string>* B = new binaryTreeNode<string>("B");
	//binaryTreeNode<string>* C = new binaryTreeNode<string>("C");
	//binaryTreeNode<string>* D = new binaryTreeNode<string>("D");
	//binaryTreeNode<string>* E = new binaryTreeNode<string>("E");
	//binaryTreeNode<string>* F = new binaryTreeNode<string>("F");
	//binaryTreeNode<string>* G = new binaryTreeNode<string>("G");
	//binaryTreeNode<string>* H = new binaryTreeNode<string>("H");
	//binaryTreeNode<string>* I = new binaryTreeNode<string>("I");
	//A->leftChild = B; A->rightChild = C;
	//B->leftChild = D;
	//C->leftChild = E; C->rightChild = F;
	//D->leftChild = G; D->rightChild = H;
	//E->leftChild = I;
	binaryTreeNode<string> A("A");
	binaryTreeNode<string> B("B"); 
	binaryTreeNode<string> C("C");
	binaryTreeNode<string> D("D");
	binaryTreeNode<string> E("E");
	binaryTreeNode<string> F("F");
	binaryTreeNode<string> G("G");
	binaryTreeNode<string> H("H");
	binaryTreeNode<string> I("I");
	A.leftChild = &B; A.rightChild = &C;
	B.leftChild = &D; 
	C.leftChild = &E; C.rightChild = &F;
	D.leftChild = &G; D.rightChild = &H;
	E.leftChild = &I;
	
	cout << "前序遍历：\n";
	binaryTreeNode<string>* p_preOrder = &A;
	binaryTree_preOrder(p_preOrder);

	cout << "\n中序遍历：\n";
	binaryTreeNode<string>*  p_inOrder = &A;
	binaryTree_inOrder(p_inOrder);

	cout << "\n后序遍历：\n";
	binaryTreeNode<string>* p_postOrder = &A;
	binaryTree_postOrder(p_postOrder);

	cout << "\n层次遍历：\n";
	binaryTreeNode<string>* p_levelOrder = &A;
	binaryTree_levelOrder(p_levelOrder);
	
	cout << "\n";
}
void binaryTree_preOrder(binaryTreeNode<string>* root)
{
	if (root != NULL)
	{
		// 前序递归遍历
		printTreeNode(root); // 先访问父(根)节点
		binaryTree_preOrder(root->leftChild); // 再访问左子树节点
		binaryTree_preOrder(root->rightChild); // 最后访问右子树节点
	}
}
void binaryTree_inOrder(binaryTreeNode<string>* root)
{
	if (root != NULL)
	{
		// 中序递归遍历
		binaryTree_inOrder(root->leftChild); // 先访问左子树节点
		printTreeNode(root); // 再访问父(根)节点
		binaryTree_inOrder(root->rightChild); // 最后访问右子树节点
	}
}
void binaryTree_postOrder(binaryTreeNode<string>* root)
{
	if (root != NULL)
	{
		// 后序递归遍历
		binaryTree_postOrder(root->leftChild); // 先访问左子树节点
		binaryTree_postOrder(root->rightChild); // 再访问右子树节点
		printTreeNode(root); // 最后访问父(根)节点
	}
}
void binaryTree_levelOrder(binaryTreeNode<string>* root)
{
	arrayQueueSimple<binaryTreeNode<string>*> q; // 树节点的队列,存的是树节点指针
	while (root != NULL)
	{
		// 打印上一次更新后的root
		printTreeNode(root); // A
		if (root->leftChild != NULL) // root的2个子树存到队列
			q.push(root->leftChild); // B
		if (root->rightChild != NULL)
			q.push(root->rightChild); // C 

		try
		{
			root = q.front(); // update root = B
		}
		catch (queueEmpty)
		{
			return;
		}
		q.pop(); // 删除q中的B,=>printTreeNode(root); print root=B
	}
}
void printTreeNode(binaryTreeNode<string>* node)
{
	cout << node->data << "  ";
}
