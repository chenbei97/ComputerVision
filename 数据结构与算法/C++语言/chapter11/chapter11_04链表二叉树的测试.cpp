#include "chapter11_linkedBinaryTree.h"
#include <iostream>
void _chapter11_myTreeOutput(binaryTreeNode<string> * t);
int linkedBinaryTree<string> ::testStatic = 1; // 类外重新声明testStatic变量
void _chapter11_linkedBinaryTree_testCode()
{
	
	linkedBinaryTree<string> tree;
	cout << "is empty ? "<<tree.empty()<<"\n";
	tree.printTestStatic(); // 1
	linkedBinaryTree<string>::printTestStatic(); // 1

	linkedBinaryTree<string>  t,x, y, z,left,right; // 临时变量用于创建树
	x.makeTree("G", t, t);
	y.makeTree("H", t, t);
	z.makeTree("D", x, y); // D->G,D->H的子树
	left.makeTree("B", z, t);// B->D的子树
	
	x.erase(); y.erase(); z.erase();//复用
	x.makeTree("I", t, t); // I
	y.makeTree("E", x, t); // E->I
	z.makeTree("F", t, t); // F
	right.makeTree("C", y, z); // C->E,C->F

	tree.makeTree("A",left, right);
	// 内部默认将output函数作为visit函数去使用
	cout << "Preorder sequence is ";
	tree.preOrderOutput();
	cout << "Inorder sequence is ";
	tree.inOrderOutput();
	cout << "Postorder sequence is ";
	tree.postOrderOutput();
	cout << "Level order sequence is ";
	tree.levelOrderOutput();

	// 使用自己的方法也可以
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