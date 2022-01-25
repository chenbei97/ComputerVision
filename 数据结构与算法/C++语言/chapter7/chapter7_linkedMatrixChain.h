#pragma once
#ifndef chapter7_linkedMatrixChain_
#define chapter7_linkedMatrixChain_
#include "chapter5_linearList.h"
#include "chapter6_chainNode.h"
#include "myExceptions.h"
#include <sstream>
#include <ostream>
#include <iterator>
template <class T>
class linkedMatrixChain : public _chapter5_linearList<T>
{
public:
	linkedMatrixChain(int initialCapacity = 10);
	linkedMatrixChain(const linkedMatrixChain<T>& theList);
	~linkedMatrixChain();
	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(std::ostream& out) const;
	void zero(){this->firstNode = NULL; this->listSize = 0;}
	void push_back(const T& theElement);
	void clear();
	linkedMatrixChain<T>& operator = (const linkedMatrixChain<T> &);
	class iterator;
	iterator begin() { return iterator(firstNode); }
	iterator end() { return iterator(NULL); }
	class iterator
	{
	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;
		iterator(_chapter6_chainNode<T>* theNode = NULL){node = theNode;}
		T& operator*() const { return node->element; }
		T* operator->() const { return &node->element; } 
		iterator& operator++() { node = node->next; return *this; }
		iterator operator++(int){iterator old = *this;node = node->next;return old; }
		bool operator!=(const iterator right) const{return node != right.node; }
		bool operator==(const iterator right) const{return node == right.node; }
	protected:
		_chapter6_chainNode<T>* node; 
	};

protected:
	int listSize;
	_chapter6_chainNode<T>* firstNode;
	_chapter6_chainNode<T>* lastNode;
	void checkIndex(int theIndex) const;
};

template<class T>
linkedMatrixChain<T>::linkedMatrixChain(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		ostringstream s;
		s << "Initial capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
	}
	firstNode = NULL; // 初始化时也是NULL,下一个元素是谁并不知道
	listSize = 0;
}

template<class T>
linkedMatrixChain<T>::linkedMatrixChain(const linkedMatrixChain<T>& theList)
{
	listSize = theList.listSize; 
	if (listSize == 0) {firstNode = NULL;return;}
	_chapter6_chainNode<T>* sourceNode = theList.firstNode;
	firstNode = new _chapter6_chainNode<T>(sourceNode->element); 
	sourceNode = sourceNode->next; 
	_chapter6_chainNode<T>* targetNode = firstNode; 
	while (sourceNode != NULL) 
	{
		targetNode->next = new _chapter6_chainNode<T>(sourceNode->element);
		targetNode = targetNode->next; 
		sourceNode = sourceNode->next;
	}
	targetNode->next = NULL;
}

template<class T>
linkedMatrixChain<T>& linkedMatrixChain<T> :: operator = (const linkedMatrixChain<T>& theList)
{
	listSize = theList.listSize;
	if (listSize == 0) { firstNode = NULL; return *this; }
	_chapter6_chainNode<T>* sourceNode = theList.firstNode;
	firstNode = new _chapter6_chainNode<T>(sourceNode->element);
	sourceNode = sourceNode->next;
	_chapter6_chainNode<T>* targetNode = firstNode;
	while (sourceNode != NULL)
	{
		targetNode->next = new _chapter6_chainNode<T>(sourceNode->element);
		targetNode = targetNode->next;
		sourceNode = sourceNode->next;
	}
	targetNode->next = NULL;
	return *this;
}

template<class T>
linkedMatrixChain<T>:: ~linkedMatrixChain()
{
	while (firstNode != NULL)
	{
		_chapter6_chainNode<T>* nextNode = firstNode->next;
		delete firstNode; // 删除当前节点
		firstNode = nextNode; // 再把当前节点指向下一个节点
		listSize--; // 节点元素也变为0
	}
}

template<class T>
T& linkedMatrixChain<T>::get(int theIndex) const
{
	checkIndex(theIndex);
	_chapter6_chainNode<T>* currentNode = firstNode;
	for (int i = 0; i < theIndex; i++)
		currentNode = currentNode->next; // 执行了theIndex次
	return currentNode->element; // 此时p已经是theIndex节点 返回数据域即可
}

template<class T>
int linkedMatrixChain<T>::indexOf(const T& theElement) const
{
	_chapter6_chainNode<T>* currentNode = firstNode;
	int index = 0;  
	while (currentNode != NULL &&
		currentNode->element != theElement) 
	{
		currentNode = currentNode->next;
		index++;
	}
	if (currentNode == NULL)
		return -1;
	else
		return index;
}

template<class T>
void linkedMatrixChain<T>::erase(int theIndex)
{
	checkIndex(theIndex); 
	_chapter6_chainNode<T>* deleteNode;
	if (theIndex == 0)
	{
		deleteNode = this->firstNode;
		this->firstNode = this->firstNode->next;
	}
	else
	{
		_chapter6_chainNode<T>* p = this->firstNode;
		for (int i = 0; i < theIndex - 1; i++)
			p = p->next;
		deleteNode = p->next;
		p->next = p->next->next;
		if (deleteNode == lastNode) 
			lastNode = p; 
	}
	this->listSize--;
	delete deleteNode;
}

template<class T>
void linkedMatrixChain<T>::clear()
{
	while (this->firstNode != NULL)
	{
		_chapter6_chainNode<T>* nextNode = this->firstNode->next;
		delete this->firstNode;
		this->firstNode = nextNode;
	}
	this->listSize = 0;
}

template<class T>
void linkedMatrixChain<T>::insert(int theIndex, const T& theElement)
{
	if (theIndex < 0 || theIndex > this->listSize)
	{
		ostringstream s;
		s << "index = " << theIndex << " size = " << this->listSize;
		throw illegalIndex(s.str());
	}
	if (theIndex == 0)
	{
		this->firstNode = new _chapter6_chainNode<T>(theElement, this->firstNode);
		if (this->listSize == 0)
			lastNode = this->firstNode; 
	}
	else
	{ 
		_chapter6_chainNode<T>* p = this->firstNode;
		for (int i = 0; i < theIndex - 1; i++)
			p = p->next;
		p->next = new _chapter6_chainNode<T>(theElement, p->next);
		if (this->listSize == theIndex)
			lastNode = p->next;
	}
	this->listSize++;
}

template<class T>
void linkedMatrixChain<T>::output(std::ostream& out) const
{
	for (_chapter6_chainNode<T>* currentNode = firstNode;
		currentNode != NULL;
		currentNode = currentNode->next) 
		out << currentNode->element << "  ";
}

template <class T>
ostream& operator<<(ostream& out, const linkedMatrixChain<T>& x)
{
	x.output(out); return out;
}

template<class T>
void linkedMatrixChain<T>::checkIndex(int theIndex) const
{
	if (theIndex < 0 || theIndex >= listSize)
	{
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}

}

template<class T>
void linkedMatrixChain<T>::push_back(const T& theElement)
{
	_chapter6_chainNode<T>* newNode = new _chapter6_chainNode<T>(theElement, NULL);
	if (this->firstNode == NULL) 
		this->firstNode = lastNode = newNode;
	else
	{  
		lastNode->next = newNode;
		lastNode = newNode; 
	}
	this->listSize++;
}
#endif chapter7_linkedMatrixChain_