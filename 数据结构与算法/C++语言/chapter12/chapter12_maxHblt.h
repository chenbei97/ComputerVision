#pragma once
#ifndef chapter12_maxHblt_
#define chapter12_maxHblt_
#include <iostream>
#include <sstream>
#include "chapter11_binaryTreeNode.h"
#include "chapter9_arrayQueueSimple.h"
#include "chapter11_linkedBinaryTree.h"
#include "chapter12_abstractMaxPriorityQueue.h"
// �̳���������ȼ����г���������������
// ����˵������������ȼ�����Ҳ�Ƕ�����
using namespace std;
template<class T>
class maxHblt :public abstractMaxPriorityQueue<T>,public linkedBinaryTree<pair<int,T>>{
public:
	bool empty() const { return this->treeSize == 0; } // �̳е�˽�б���Ҫ��this->
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
		{cout <<t->data.second << "  "; } // ������Ľڵ����,����Ϊ��̬�������������ʵ����ʹ����1�ַ�ʽ���
	}// ������Ϊ������������visit����

};
template<class T>
void maxHblt<T>::initialize(T* theArray, int theSize) {
	// ���ĺ���,��������Ķ��������ܹ�ִ��meld�ϲ�����
	// ������������[1,size]��Ԫ�ع���Ϊ1����������
	arrayQueueSimple<binaryTreeNode<pair<int, T> >*> q(theSize); //����
	this->erase();  // �ڲ����ù��к������ɾ����root��ÿ���ڵ�

	// ��ʼ�������������ΪԪ�صĽڵ㲢�������
	for (int i = 1; i <= theSize; i++) // [1,Size]
		q.push(new binaryTreeNode<pair<int, T> >
			(pair<int, T>(1, theArray[i]))); // �������������������ڵ�,��Ŷ���ʼ��Ϊ1

	for (int i = 1; i <= theSize - 1; i++) // ����1��������
	{
		binaryTreeNode<pair<int, T> >* b = q.front(); // ��Ϊ��ڵ�
		q.pop();
		binaryTreeNode<pair<int, T> >* c = q.front(); // ��Ϊ�ҽڵ�
		q.pop();
		meld(b, c); // ��������2���ڵ���Ϊ���ҽڵ�Ȼ��ϲ��õ���������
		q.push(b); // ������������������Ϊ��һ���Ļ���
	}
	// ���е����1������Ԫ�ؾ������յ���������
	if (theSize > 0)
		this->root = q.front();
	this->treeSize = theSize;
}

template<class T>
void maxHblt<T>::merge(maxHblt<T>& theHblt) {
	meld(this->root, theHblt.root); // ���з���,����2�����ĸ�,��thisΪ׼
	this->treeSize += theHblt.treeSize;
	theHblt.root = NULL; // �ÿձ���Ұָ��
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

	// ��Ҫ�Ļ�������������,��xΪ׼,ÿ�������xֵһ������y
	if (x->data.second < y->data.second)
		swap(x, y);
	// �ϲ�x����������y
	meld(x->rightChild, y);

	// ���x��������Ϊ��,��֤������������,��������,ͬʱ���ڵ�x��űض���1
	if (x->leftChild == NULL)
	{
		x->leftChild = x->rightChild;
		x->rightChild = NULL;
		x->data.first = 1;
	}
	else
	{ // x,y����Ϊ�ջ���x��Ϊ��yΪ��,��Ҫ�Ļ�����2���ڵ�,��ڵ���С���ҽڵ���ʱ����
		if (x->leftChild->data.first < x->rightChild->data.first)
			swap(x->leftChild, x->rightChild);
		// ��ʱ���ڵ��Ȼ���ҽڵ���+1
		x->data.first = x->rightChild->data.first + 1;
	}
}

template<class T>
ostream& operator<<<>(ostream&out,const maxHblt<T>& x) {
	x.output(out); return out;
}

template<class T>
void maxHblt<T>::output() {
	// ʹ�ú������?,ʹ�ò�α�����,maxHbltOutput����visit����
	this->levelOrder(maxHbltOutput); cout << endl; // ��Ϊ�����������ص�,��ʱ��α����ض�����
}

template<class T>
const T& maxHblt<T>::top() {
	if (this->treeSize == 0)
		throw queueEmpty();
	return this->root->data.second;
}

template<class T>
void maxHblt<T>::push(const T& theElement) {
	binaryTreeNode<pair<int, T> >* q =// new1���½ڵ�,������������Ľڵ�
		new binaryTreeNode<pair<int, T> >(pair<int, T>(1, theElement)); // ���1,Ԫ��ֵΪҪ�����Ԫ��
	meld(this->root, q); // ��Ȼqֻ��1�����ڵ�,����Ҳ�������ϲ���this
	this->treeSize++;
}

template<class T>
void maxHblt<T>::pop() {
	if (this->root == NULL)
		throw queueEmpty();
	// ����Ϊ��ʱ����ɾ��,ɾ���������ĸ�,���Ժϲ�����������������
	binaryTreeNode<pair<int, T> >* left = this->root->leftChild,
		* right = this->root->rightChild; // ����2����ָ��
	delete this->root; // ɾ��ԭ����root�ڵ�,����ָ���������ڵ�
	this->root = left;
	meld(this->root, right); // ���кϲ�����
	this->treeSize--;
}
#endif // !chapter12_maxHblt_

