#pragma once
#include "charter5_linearList.h"
#include "charter6_chainNode.h"
#include "myExceptions.h"
#include <sstream>
#include <ostream>
template <class T>
class _charter6_chainList : public _charter5_linearList<T>
{
public:
	// constructed
	_charter6_chainList(int initialCapacity = 10);
	_charter6_chainList(const _charter6_chainList<T>& theList);
	~_charter6_chainList();

	// method
	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(std::ostream& out) const;

protected:
	// attribute
	int listSize;
	_charter6_chainNode<T>* firstNode; // 链表类的实例都有属性firstNode指针指向第1个节点
	// method
	void checkIndex(int theIndex) const;
};

template<class T>
_charter6_chainList<T>::_charter6_chainList(int initialCapacity)
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
_charter6_chainList<T>::_charter6_chainList(const _charter6_chainList<T>& theList)
{
	listSize = theList.listSize; // 私有属性listSize复制

	if (listSize == 0) // 如果复制构造对象是个空链表,不执行后续复制的相关操作
	{
		firstNode = NULL;
		return;
	}

	// 1个指向theList头节点的指针
	_charter6_chainNode<T>* sourceNode = theList.firstNode; 
	// std::cout<<firstNode->element<<"   "<< endl; 此时自身的firstNode什么都没有呢,打印element或next会报错
	firstNode = new _charter6_chainNode<T>(sourceNode->element); // 只复制了theList头节点的数据
	//printf("firstNode->element = %d", firstNode->element);
	//std::cout << firstNode->next << std::endl; // 没有复制theList头节点的指针信息
	
	// 后面也不会复制theList其它节点的指针信息,因为那是theList的,这里的firstNode只需要记录自己的下一个节点地址即可
	// 而firstNode指向的其实是targetNode,在while循环中反复被创建并指向下一个
	// 下方只是输出信息,sourceNode本身没有更新
	/*
		std::cout << sourceNode->next << "  " << sourceNode->next->next << "  " << sourceNode->next->next->next
		<<"   " << sourceNode->next->next->next->next->element << endl;
		输出都是没初始化的地址
	*/
	sourceNode = sourceNode->next; // 更改指向theList的第2个节点
	_charter6_chainNode<T>* targetNode = firstNode; // 指向theList的第1个节点
	while (sourceNode != NULL) // 当下一个节点不为空就会执行
	{
		// new是开辟的新节点,当前targetNode的指针指向这个新开辟的节点地址
		// 新节点的地址构造好后只有1个地址没有变量实体,后面想移动targetNode 只能通过targetNode =targetNode ->next来更改
		// 开辟的新节点只以element构造来复制theList的节点
		targetNode->next = new _charter6_chainNode<T>(sourceNode->element);
		targetNode = targetNode->next; // 
		sourceNode = sourceNode->next;//更新指向下1个节点
	}
	targetNode->next = NULL; 
	/*
	* 此时再打印不会报错,复制构造已经完成
	std::cout << "复制构造完成以后打印：" << std::endl;
	std::cout << "firstNode = "<<firstNode << "\n"
		<< "firstNode->element = "<<firstNode->element << "   firstNode->next = " << firstNode->next << "\n"
		<< "firstNode->next->next = "<<firstNode->next->next << "   firstNode->next->next->next = " << firstNode->next->next->next << "\n"
		<< "firstNode->next->next->next->next = "<<firstNode->next->next->next->next << "   firstNode->next->next->next->next->next = " << firstNode->next->next->next->next->next << "\n" << std::endl;
	std::cout << "firstNode和theList.firstNode是2个不同的地址！" << std::endl;
	std::cout << "theList.firstNode = " << theList.firstNode << "\n"
		<< "theList.firstNode->element = " << theList.firstNode->element << "   theList.firstNode->next = " << theList.firstNode->next << "\n"
		<< "theList.firstNode->next->next = " << theList.firstNode->next->next << "   theList.firstNode->next->next->next = " << theList.firstNode->next->next->next << "\n"
		<< "theList.firstNode->next->next->next->next = " << theList.firstNode->next->next->next->next << "   theList.firstNode->next->next->next->next->next = " << theList.firstNode->next->next->next->next->next << "\n" << std::endl;
	*/
}

template<class T>
_charter6_chainList<T>:: ~_charter6_chainList()
{
	// 复制构造或者插入的节点都是new出来的,需要析构掉
	while (firstNode != NULL)
	{
		//当前节点不为空就一个指针指向它包含的下一个节点
		_charter6_chainNode<T>* nextNode = firstNode->next;
		delete firstNode; // 删除当前节点
		firstNode = nextNode; // 再把当前节点指向下一个节点
		listSize--; // 节点元素也变为0
	}
	//printf("listSize = %d\n", listSize);
}

template<class T>
T& _charter6_chainList<T>::get(int theIndex) const
{
	checkIndex(theIndex);
	// 1个头指针进行节点遍历
	_charter6_chainNode<T>* currentNode = firstNode;
	for (int i = 0; i < theIndex; i++)
		currentNode = currentNode->next; // 执行了theIndex次
	return currentNode->element; // 此时p已经是theIndex节点 返回数据域即可
}

template<class T>
int _charter6_chainList<T>::indexOf(const T& theElement) const
{
	// 查找某个元素的索引,需要借助头指针遍历每个节点,比较和element的信息即可
	_charter6_chainNode<T>* currentNode = firstNode; 
	int index = 0;  // 因为索引不像数组没有实体,需要自己定义索引值
	while (currentNode != NULL &&
		currentNode->element != theElement) // 不为空且没找到时执行while
	{
		// 移动头指针到下1个节点
		currentNode = currentNode->next;
		index++;
	}

	// while结束,如果没找到就返回-1否则返回index
	if (currentNode == NULL)
		return -1;
	else
		return index;

}

template<class T>
void _charter6_chainList<T>::erase(int theIndex)
{
	checkIndex(theIndex);
	_charter6_chainNode<T>* deleteNode; // 创建1个局部指针
	if (theIndex == 0)
	{
		// 删除头节点只需要让firstNode指向下1个节点,这个节点的地址是firstNode->next
		deleteNode = firstNode;// 原来的头节点地址在最后会被delete
		firstNode = firstNode->next;//头节点指针信息更新为原来头节点指向的下1个即firstNode->next
	}
	else
	{  
		_charter6_chainNode<T>* p = firstNode;
		for (int i = 0; i < theIndex - 1; i++)
			p = p->next;
		// 此时p到达index-1的位置
		deleteNode = p->next; // 删除的index节点的地址信息在index-1,所以使用p->next
		p->next = p->next->next; // 把当前index-1的指针指向到index+1,即p->next->next(记录在index的指针)
	}
	listSize--;
	delete deleteNode; // 删除地址是真正的删除
}

template<class T>
void _charter6_chainList<T>::insert(int theIndex, const T& theElement)
{
	if (theIndex < 0 || theIndex > listSize)
	{// invalid index
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}

	if (theIndex == 0)// 如果在头节点之前插入节点,让新创建的节点指向原来的头节点即可
	{
		// 1.使用1个指针指向用原来头节点信息创建的新节点
		// newfirstNode必须用指针接收,和firstNode就是一类指针
		_charter6_chainNode<T> *newfirstNode = new _charter6_chainNode<T>(theElement, firstNode);
		// 2.把现在的头节点指向原来的头节点,数据域和链域信息都保留
		this->firstNode = newfirstNode;//更新头节点
		// 3.以前的头节点不影响指向的下一个节点,无需更新,插入执行完毕
	}
	else // index是要插入的节点,需要找到index-1的节点,只能借助一个指向头节点的指针遍历查找
	{  
		_charter6_chainNode<T>* p = firstNode;//一个指向自身头节点的指针
		for (int i = 0; i < theIndex - 1; i++)//移动index-1次就到达前1个节点的地址
			p = p->next; // 等价于p->next->next->next->...->next(index-1个next) 

		// 这里只执行了index-1次,此时p指向的是第index-1个节点,它的再下一个才是index节点
		// 1.创建1个新节点保留index节点的信息(在p->next中),要以(theElement, p->next)方式创建
		_charter6_chainNode<T> * theIndexNode = new _charter6_chainNode<T>(theElement, p->next); // 创建节点就要使用new
		// 2.要把index-1的指针信息(p->next)指向当前新创建的节点
		p->next = theIndexNode;
		// 3.theIndexNode创建时就有了原来index节点的信息了,无需更改后续
	}
	listSize++; // 成员+1
}

template<class T>
void _charter6_chainList<T>::output(std::ostream& out) const
{
	for (_charter6_chainNode<T>* currentNode = firstNode;
		currentNode != NULL;
		currentNode = currentNode->next) // 不为空时就继续更新地址到下一个节点
		out << currentNode->element << "  ";//打印元素
}

template <class T>
ostream& operator<<(ostream& out, const _charter6_chainList<T>& x)
{
	x.output(out); return out;
}

template<class T>
void _charter6_chainList<T>:: checkIndex(int theIndex) const
{
	if (theIndex < 0 || theIndex >= listSize)
	{
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}

}




