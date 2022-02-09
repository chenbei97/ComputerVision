#include "chapter11_linkedBinaryTree.h"
#include <iostream>
void _chapter11_myTreeOutput(binaryTreeNode<string> * t);
int linkedBinaryTree<string> ::testStatic = 1; // ������������testStatic����
void _chapter11_linkedBinaryTree_testCode()
{
	
	linkedBinaryTree<string> tree;
	cout << "is empty ? "<<tree.empty()<<"\n";
	tree.printTestStatic(); // 1
	linkedBinaryTree<string>::printTestStatic(); // 1

	linkedBinaryTree<string>  t,x, y, z,left,right; // ��ʱ�������ڴ�����
	x.makeTree("G", t, t);
	y.makeTree("H", t, t);
	z.makeTree("D", x, y); // D->G,D->H������
	left.makeTree("B", z, t);// B->D������
	
	x.erase(); y.erase(); z.erase();//����
	x.makeTree("I", t, t); // I
	y.makeTree("E", x, t); // E->I
	z.makeTree("F", t, t); // F
	right.makeTree("C", y, z); // C->E,C->F

	tree.makeTree("A",left, right);
	// �ڲ�Ĭ�Ͻ�output������Ϊvisit����ȥʹ��
	cout << "Preorder sequence is ";
	tree.preOrderOutput();
	cout << "Inorder sequence is ";
	tree.inOrderOutput();
	cout << "Postorder sequence is ";
	tree.postOrderOutput();
	cout << "Level order sequence is ";
	tree.levelOrderOutput();

	// ʹ���Լ��ķ���Ҳ����
	tree.preOrder(_chapter11_myTreeOutput);
	cout << "\n";
	tree.inOrder(_chapter11_myTreeOutput);
	cout << "\n";
	tree.postOrder(_chapter11_myTreeOutput);
	cout << "\n";
	tree.levelOrder(_chapter11_myTreeOutput);
	cout << "\n";

	cout << "tree's height is " << tree.height() << endl;
}
void _chapter11_myTreeOutput(binaryTreeNode<string>* t)
{
	cout << "(" << t->data << ")  ";
}