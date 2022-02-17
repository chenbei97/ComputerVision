#pragma once
#ifndef chapter12_maxHblt_
#define chapter12_maxHblt_
#include <iostream>
#include <sstream>
#include "chapter11_binaryTreeNode.h"
#include "chapter9_arrayQueueSimple.h"
#include "chapter11_linkedBinaryTree.h"
#include "chapter12_abstractMaxPriorityQueue.h"
// 继承自最大优先级队列抽象类和链表二叉树
// 这间接说明左高树是优先级队列也是二叉树
using namespace std;
template<class T>
class maxHblt :public abstractMaxPriorityQueue<T>,public linkedBinaryTree<pair<int,T>>{
public:
	bool empty() const { return this->treeSize == 0; } // 继承的私有变量要加this->
	int size() const { return this->treeSize; }
	const T& top();
	void pop();
	void push(const T&);
	void initialize(T*, int);
	void merge(maxHblt<T>&);
	void output();
	friend ostream& operator<<<>(ostream&, const maxHblt<T>& );
protected:
	void meld(binaryTreeNode<pair<int, T>>*&, binaryTreeNode<pair<int, T>>*&);
	static void maxHbltOutput(binaryTreeNode<pair<int, T>>* t) {
		{cout <<t->data.second << "  "; } // 左高树的节点输出,声明为静态函数是所有类的实例都使用这1种方式输出
	}// 可以作为链表二叉树类的visit函数

};
template<class T>
void maxHblt<T>::initialize(T* theArray, int theSize) {
	// 核心函数,这样构造的二叉树才能够执行meld合并操作
	// 将给定的数组[1,size]的元素构造为1个最大左高树
	arrayQueueSimple<binaryTreeNode<pair<int, T> >*> q(theSize); //队列
	this->erase();  // 内部调用公有后序遍历删除了root的每个节点

	// 初始化以这个数组作为元素的节点并存入队列
	for (int i = 1; i <= theSize; i++) // [1,Size]
		q.push(new binaryTreeNode<pair<int, T> >
			(pair<int, T>(1, theArray[i]))); // 构造这样的最大左高树节点,编号都初始化为1

	for (int i = 1; i <= theSize - 1; i++) // 留出1个不构造
	{
		binaryTreeNode<pair<int, T> >* b = q.front(); // 作为左节点
		q.pop();
		binaryTreeNode<pair<int, T> >* c = q.front(); // 作为右节点
		q.pop();
		meld(b, c); // 把连续的2个节点作为左右节点然后合并得到最大左高树
		q.push(b); // 初级最大左高树继续作为下一级的基础
	}
	// 队列的最后1个就是元素就是最终的最大左高树
	if (theSize > 0)
		this->root = q.front();
	this->treeSize = theSize;
}

template<class T>
void maxHblt<T>::merge(maxHblt<T>& theHblt) {
	meld(this->root, theHblt.root); // 公有方法,传入2棵树的根,以this为准
	this->treeSize += theHblt.treeSize;
	theHblt.root = NULL; // 置空避免野指针
	theHblt.treeSize = 0;
}

template<class T>
void maxHblt<T>::meld(binaryTreeNode<pair<int, T> >*& x,
	binaryTreeNode<pair<int, T> >*& y)
{
	if (y == NULL)   // y is empty
		return;
	if (x == NULL)   // x is empty
	{
		x = y; return;
	}

	// 必要的话交换两颗子树,以x为准,每个进入的x值一定大于y
	if (x->data.second < y->data.second)
		swap(x, y);
	// 合并x的右子树和y
	meld(x->rightChild, y);

	// 如果x的左子树为空,保证最大左高树定义,交换它们,同时父节点x编号必定是1
	if (x->leftChild == NULL)
	{
		x->leftChild = x->rightChild;
		x->rightChild = NULL;
		x->data.first = 1;
	}
	else
	{ // x,y均不为空或者x不为空y为空,必要的话交换2个节点,左节点编号小于右节点编号时交换
		if (x->leftChild->data.first < x->rightChild->data.first)
			swap(x->leftChild, x->rightChild);
		// 此时父节点必然是右节点编号+1
		x->data.first = x->rightChild->data.first + 1;
	}
}

template<class T>
ostream& operator<<<>(ostream&out,const maxHblt<T>& x) {
	x.output(out); return out;
}

template<class T>
void maxHblt<T>::output() {
	// 使用后序遍历?,使用层次遍历把,maxHbltOutput看成visit函数
	this->levelOrder(maxHbltOutput); cout << endl; // 因为最大左高树的特点,此时层次遍历必定有序
}

template<class T>
const T& maxHblt<T>::top() {
	if (this->treeSize == 0)
		throw queueEmpty();
	return this->root->data.second;
}

template<class T>
void maxHblt<T>::push(const T& theElement) {
	binaryTreeNode<pair<int, T> >* q =// new1个新节点,是左高树这样的节点
		new binaryTreeNode<pair<int, T> >(pair<int, T>(1, theElement)); // 编号1,元素值为要插入的元素
	meld(this->root, q); // 虽然q只有1个根节点,但是也看成树合并到this
	this->treeSize++;
}

template<class T>
void maxHblt<T>::pop() {
	if (this->root == NULL)
		throw queueEmpty();
	// 树不为空时可以删除,删除的是树的根,所以合并根的左右子树即可
	binaryTreeNode<pair<int, T> >* left = this->root->leftChild,
		* right = this->root->rightChild; // 定义2个新指针
	delete this->root; // 删除原来的root节点,让它指向左子树节点
	this->root = left;
	meld(this->root, right); // 进行合并操作
	this->treeSize--;
}
#endif // !chapter12_maxHblt_

