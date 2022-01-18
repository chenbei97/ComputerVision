#pragma once
/*
为了使用链表描述线性表，需要定义一个结构chainNode，内部成员有2个
一个是element存储了当前节点的元素值(数据域)
一个是next指向下一个节点的指针(链域)
需要说明的next的指针类型就是chainNode*
自然指针也是2个成员，但不是指向本身，而是下一个chainNode

​也就是每个节点的数据类型都是chainNode，内部只有element和next两个成员
特别的最后一个节点next=NULL
结构体还有3个方法，用于改变节点的数据域或者链域
*/
template<class T>
struct _charter6_chainNode
{
	// 成员,数据域和链域
	T element;
	_charter6_chainNode<T>* next;

	// 方法
	_charter6_chainNode() {}
	// 只改变节点的数据域(元素值)
	_charter6_chainNode(const T& element) 
	{
		this->element = element;
	} // 节点的元素值改变时改变成员element的值
	// 只改变节点的链域(指向的下一个元素地址)也是可以的
	_charter6_chainNode(_charter6_chainNode<T>* next)
	{
		this->next = next;
	}
	// 同时改变节点数据与和链域
	_charter6_chainNode(const T& element, _charter6_chainNode<T>* next)
	{
		this->element = element;
		this->next = next;
	}

};
