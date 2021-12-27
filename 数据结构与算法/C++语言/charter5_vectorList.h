#pragma once
/*
本头文件定义的类_charter5_vectorList和charter5_arrayList.h的类_charter5_arrayList有相同点也有不同点
_charter5_arrayList的数组长度需要动态增加,_charter5_vectorList类似按照原容量的50%-100%增加
_charter5_vectorList没有一个构造函数和_charter5_arrayList的构造函数等价
两者都有empty、size、output和重载<<方法,是等价的
_charter5_vectorList的erase和insert方法略有不同,需要给定内存地址,或者说迭代器位置,数组给定索引即可
最后两者抛出的异常类型是不同的,checkIndex中体现

arrayList借助数组实现,需要私有变量arrayLength,在默认构造函数中传递
还需要私有变量listSize,初始化为0,通过insert函数中进行++
element是一个T类型的动态数组的指针
从而empy函数是通过listSize是否为0来判定,size也是通过listSize
get函数核心就是return element[theIndex];这是数组索引的方式,数组指针也可以使用[]索引
indexOf函数查找theElement元素是借助element在数组两端的指针,使用find函数查找
insert函数需要借助changeLength1D实现,自行更新索引
erase需要借助copy实现,然后清除元素更新索引
checkIndex函数抛出类型为illegalParameterValue

vectorList借助vector实现,无需私有变量,element是一个vector<T>的指针
empy,size直接使用vector的内置方法empy和size,这是因为数组没有这两个方法
get函数核心语句return (*element)[theIndex];因为vector支持[]索引,区别需要解引用,容器指针不支持直接[]索引
indexOf函数查找theElement元素也是借助element,区别在于element是容器类型的指针,那么就自带迭代器方法,使用箭头运算符即可使用
insert函数借助vector自带的方法inser(iterator,val) or inser(iterator,n,val)=>插入n个val  无需自己编写动态拓展宽度的函数
erase函数和insert函数同理,调用vector自带方法 erase
checkIndex函数抛出类型为illegalIndex

output和<<重载的实现2个类完全一样

*/#include "charter5_linearList.h"
#include "charter1_illegalIndex.h"
#include "charter1_illegalParameterValue.h"
#include <vector>
#include <ostream>
#include <iostream>
#include <sstream>
// statement
template<class T>
class _charter5_vectorList : public _charter5_linearList<T>
{
public:
	_charter5_vectorList(int initialCapacity = 10);
	_charter5_vectorList(const _charter5_vectorList<T>& theList);
	~_charter5_vectorList() { delete element; }
	bool empty() const { return element->empty(); }// 借助vector的方法empty
	int size() const { return (int)element->size(); }// 借助vector的方法size
	int indexOf(const T& theElement) const; // theElement是vector类型,元素是T类型
	T& get(int theIndex) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);// 传入的是T类型的元素
	void output(std::ostream& out) const;
	int capacity() const { return (int)element->capacity(); };// 借助vector的方法capacity

	typedef typename std::vector<T> ::iterator iterator; // 把std::vector<T> ::iterator改名为iterator
	iterator begin() { return element->begin(); }// 返回的就是vector的迭代器类型
	iterator end() { return element->end(); } // 类的公有函数begin和end间接使用的是vector容器的方法begin和end

private:
	void checkIndex(int theIndex) const;
	std::vector<T>* element; // 是vector类型的指针,不是数组,析构使用delete而非delete []
};

// constructed
template<class T>
_charter5_vectorList<T> ::_charter5_vectorList(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		std::ostringstream s;
		s << "initial capcaity = " << initialCapacity << "  must be > 0";
		throw illegalParameterValue(s.str());
	}
	element = new std::vector<T>; // 动态容器的指针,是vector类型的指针
}

template<class T>
_charter5_vectorList<T> ::_charter5_vectorList(const _charter5_vectorList<T>& theList)
{
	element = new std::vector<T>(*theList.element); // 复制构造是把vectorList的实例的私有属性element(1个容器)的指针解引用传递
	// 本质上就是一个容器传入了容器,vector有这样的构造函数
	//vector<int> arrint1(10);
	//vector<int>arrint2(arrint1);
	//cout << arrint2.capacity() << endl;
	// 这里相当于把*theList.element整个给了element,解引用是因为theList.element是指针
}

template<class T>
void _charter5_vectorList<T>::checkIndex(int theIndex) const
{
	if (theIndex < 0 || theIndex >= size())
	{
		ostringstream s;
		s << "index = " << theIndex << " size = " << size();
		throw illegalIndex(s.str());
	}
}

template<class T>
T& _charter5_vectorList<T>::get(int theIndex) const
{
	checkIndex(theIndex);
	return (*element)[theIndex];
}

template<class T>
int _charter5_vectorList<T>::indexOf(const T& theElement) const
{
	// 查找这个容器元素theElement在容器的位置
	// element是一个vector容器的指针,也具备内置方法begin和end,但是要使用箭头->运算符
	int theIndex = (int)(find(element->begin(), element->end(),
		theElement)
		- element->begin());//数组中需要减去element,这里也是,find返回的是第1个元素

	// check if theElement was found
	if (theIndex == size())
		// not found
		return -1;
	else return theIndex;
}

template<class T>
void _charter5_vectorList<T>::erase(int theIndex)
{
	checkIndex(theIndex);
	element->erase(begin() + theIndex);// 调用vector自带的方法erase
}

template<class T>
void _charter5_vectorList<T>::insert(int theIndex, const T& theElement)
{
	if (theIndex < 0 || theIndex > size())
	{// invalid index
		ostringstream s;
		s << "index = " << theIndex << " size = " << size();
		throw illegalIndex(s.str());
	}
	element->insert(element->begin() + theIndex, theElement);//调用vector自带的方法insert 指定插入的位置和元素
}

template<class T>
void _charter5_vectorList<T>::output(ostream& out) const
{
	copy(element->begin(), element->end(), ostream_iterator<T>(cout, "  "));
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const _charter5_vectorList<T>& x)
{
	x.output(out); return out;
}





