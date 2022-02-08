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
	// ʹ��ָ��new�����Ļ���Ӱ��
	// binaryTreeNode<string>* p_preOrder = A;p_preOrder���ƶ�Ҳ��ı�A��ָ��
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
	
	cout << "ǰ�������\n";
	binaryTreeNode<string>* p_preOrder = &A;
	binaryTree_preOrder(p_preOrder);

	cout << "\n���������\n";
	binaryTreeNode<string>*  p_inOrder = &A;
	binaryTree_inOrder(p_inOrder);

	cout << "\n���������\n";
	binaryTreeNode<string>* p_postOrder = &A;
	binaryTree_postOrder(p_postOrder);

	cout << "\n��α�����\n";
	binaryTreeNode<string>* p_levelOrder = &A;
	binaryTree_levelOrder(p_levelOrder);
	
	cout << "\n";
}
void binaryTree_preOrder(binaryTreeNode<string>* root)
{
	if (root != NULL)
	{
		// ǰ��ݹ����
		printTreeNode(root); // �ȷ��ʸ�(��)�ڵ�
		binaryTree_preOrder(root->leftChild); // �ٷ����������ڵ�
		binaryTree_preOrder(root->rightChild); // �������������ڵ�
	}
}
void binaryTree_inOrder(binaryTreeNode<string>* root)
{
	if (root != NULL)
	{
		// ����ݹ����
		binaryTree_inOrder(root->leftChild); // �ȷ����������ڵ�
		printTreeNode(root); // �ٷ��ʸ�(��)�ڵ�
		binaryTree_inOrder(root->rightChild); // �������������ڵ�
	}
}
void binaryTree_postOrder(binaryTreeNode<string>* root)
{
	if (root != NULL)
	{
		// ����ݹ����
		binaryTree_postOrder(root->leftChild); // �ȷ����������ڵ�
		binaryTree_postOrder(root->rightChild); // �ٷ����������ڵ�
		printTreeNode(root); // �����ʸ�(��)�ڵ�
	}
}
void binaryTree_levelOrder(binaryTreeNode<string>* root)
{
	arrayQueueSimple<binaryTreeNode<string>*> q; // ���ڵ�Ķ���,��������ڵ�ָ��
	while (root != NULL)
	{
		// ��ӡ��һ�θ��º��root
		printTreeNode(root); // A
		if (root->leftChild != NULL) // root��2�������浽����
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
		q.pop(); // ɾ��q�е�B,=>printTreeNode(root); print root=B
	}
}
void printTreeNode(binaryTreeNode<string>* node)
{
	cout << node->data << "  ";
}
