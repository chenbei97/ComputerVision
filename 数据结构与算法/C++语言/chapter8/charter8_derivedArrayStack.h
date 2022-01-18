#pragma once
#ifndef derivedArrayStack_
#define derivedArrayStack_
// 本类是派生自数组描述的线性表的具体类arrayList和抽象栈类abstractStack
// 因为派生的关系,本类的执行效率比较低,在头文件<charter8_arrayStack.h>中会定义由abstractStack直接实现的具体类
// 而继承的派生数组类头文件为<charter5_arrayList.h>,但是这个文件鉴于历史原因没有把定义和实现写在一起
// 其实现部分放在了<charter5_arrayList的分文件实现.cpp>当中，现在把定义和声明要放在一起
// 那么继承这个头文件会出问题,所以把声明和定义放在一起的数组线性表,放在了头文件<charter8_arrayList.h>中
#include "charter8_arrayList.h"
#include "charter8_abstractStack.h"
#include "charter8_stackEmpty.h"
template<class T>
class derivedArrayStack : private _charter8_arrayList<T>, public abstractStack<T>
{
public:
	derivedArrayStack(int initialCapacity = 10) : _charter8_arrayList<T>(initialCapacity) {} // 构造函数直接继承
	bool empty() const { return _charter8_arrayList<T> ::empty(); } // empty直接继承
	int size() const { return _charter8_arrayList<T>::size(); } // size直接继承
	// 抽象栈类的具体实现
	T& top(); 
	void pop();
	void push(const T&);
	friend ostream& operator<<<>(ostream&, const derivedArrayStack<T>&);
private:
	void output(std::ostream& out) const ; // 重写output方法
};

template<class T>
T& derivedArrayStack<T> ::top()
{
	// 下方程序是正确的,但是有个地方需要改善,get的索引出错时抛出的异常是illegalParameterValue
	// 那么对于外部的使用人员来说,他并不知道这个继承的逻辑,所以应该把这种类型异常转为栈空类型的异常
	//if (_charter8_arrayList<T>::empty())
	//	throw stackEmpty();
	//return  _charter8_arrayList<T>::get(_charter8_arrayList<T>::size() - 1); // 获取右端的元素 即listSize-1
	try { return _charter8_arrayList<T>::get(_charter8_arrayList<T>::size() - 1); }
	catch (illegalParameterValue) { throw stackEmpty(); } // 借助try_catch结构进行转换
}

template<class T>
void derivedArrayStack<T> ::pop()
{
	if (_charter8_arrayList<T>::empty())
		throw stackEmpty();
	  _charter8_arrayList<T>::erase(_charter8_arrayList<T>::size() - 1); // 删除的是listSize-1的元素
}

template<class T>
void derivedArrayStack<T> ::push(const T& theElement)
{
	  _charter8_arrayList<T>::insert(_charter8_arrayList<T>::size(), theElement); // 插入的位置在listSize
}

template<class T>
void derivedArrayStack<T> ::output(std::ostream &out) const
{
	// 原来的实现方法
	/*std::copy(element, element + listSize, std::ostream_iterator<T>(std::cout, "   "));*/
	if (_charter8_arrayList<T>::size() == 0)
		throw stackEmpty();
	for (int i = 0; i < _charter8_arrayList<T>::size(); i++)
	{
		cout << _charter8_arrayList<T>::element[i] << "  ";
		if ((i + 1) % 10 == 0)
			out << endl;
	}
}

template<class T>
ostream& operator<<<>(ostream& out, const derivedArrayStack<T>& theStack)
{
	theStack.output(out);
	return out;
}
#endif // !derivedArrayStack_
