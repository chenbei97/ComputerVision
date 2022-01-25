#pragma once
#ifndef chapter5_arrayListBidirectIterator_
#define chapter5_arrayListBidirectIterator_
#include "chapter5_linearList.h"
#include "chapter1_illegalParameterValue.h"
#include <iterator> // 使用bidirectional_iterator_tag和ptrdiff_t
#include<sstream> // 使用ostringstream

// 线性表带迭代器的具体类声明部分和实现写在同一文件中
// 就可以被其它文件调用
template<class T>
class _chapter5_arrayListWithIterator : public _chapter5_linearList<T>
{
public:
    _chapter5_arrayListWithIterator(int initialCapacity = 10);
    _chapter5_arrayListWithIterator(const _chapter5_arrayListWithIterator<T>&);
    ~_chapter5_arrayListWithIterator() { delete[] element; }

    bool empty() const { return listSize == 0; }
    int size() const { return listSize; }
    T& get(int theIndex) const;
    int indexOf(const T& theElement) const; 
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    void output(std::ostream& out) const;
    int capacity() const { return arrayLength; }

	// 迭代器类整体作为线性表类的公有成员,迭代器类的2个方法也是公有成员
	class _chapter5_iterator;// 类本身也是1个成员
	_chapter5_iterator begin() { return _chapter5_iterator(element); } // element是个指向线性表开头的指针,对应begin
	_chapter5_iterator end() { return _chapter5_iterator(element + listSize); }// element+listSize是最后1个元素的后1个位置
	class _chapter5_iterator
	{
	public:
		// 使用typedef实现双向迭代器,将下述关键字起别名
		// bidirectional_iterator_tag,T,ptrdiff_t, T*, T&都起相应的别名
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef  T value_type;
		typedef std::ptrdiff_t  difference_type;
		typedef T* pointer;
		typedef T& reference;

		// 默认构造函数,传入参数是一个指针
		_chapter5_iterator(T* thePosition = 0) { position = thePosition; }

		// 重载解引用*,->操作符
		T& operator*() const { return *position; }
		T* operator->() const { return &*position; }

		// 双向迭代器的++操作符重载
		_chapter5_iterator& operator++()   
		{
			++position; return *this; // 前加 就是先加,然后才用这个变量<=>++operator
			// 注意如何实现：position已经先+再返回this,此时表达式值已经变化
		}
		_chapter5_iterator operator++(int) // 后加 先用这个变量,然后在对这个变量做自增<=>operator++
		{
			// i++ 后加 相当于+1,需要传入int参数
			// 先保留+之前的结果,也就是position没+,表达式值没变
			_chapter5_iterator old = *this;
			++position;
			return old;
		}

		// 双向迭代器的--操作符重载
		_chapter5_iterator& operator--()   // 前减
		{
			--position; return *this;
		}
		_chapter5_iterator operator--(int) // 后减
		{
			_chapter5_iterator old = *this;
			--position;
			return old;
		}

		// 测试是否相等
		bool operator!=(const _chapter5_iterator right) const
		{
			// 左侧应当是this,右侧应当是传入的外界指针
			// 例如iterator != x.end() 是2个迭代器的!=运算
			return position != right.position; // 迭代器是否相等需要转换为迭代器指向的地址是否相等
		}
		bool operator==(const _chapter5_iterator right) const
		{
			return position == right.position;
		}
	protected:
		T* position;
	};  

protected:
    void checkIndex(int theIndex) const;
    void changeLength1D(T*& pa, int oldLength, int newLength); 
    int arrayLength; 
    int listSize; 
    T* element;
};
template<class T>
_chapter5_arrayListWithIterator<T>::_chapter5_arrayListWithIterator(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		std::ostringstream s; 
		s << "Initial Capacity = " << initialCapacity << "  Must be > 0";
		throw illegalParameterValue(s.str());
	}
	arrayLength = initialCapacity;
	element = new T[arrayLength]; 
	listSize = 0; 
}

template<class T>
_chapter5_arrayListWithIterator<T> ::_chapter5_arrayListWithIterator(const _chapter5_arrayListWithIterator<T>& theList)
{
	arrayLength = theList.arrayLength;
	listSize = theList.listSize;
	element = new T[arrayLength];
	std::copy(theList.element, theList.element + listSize, element); 
}

template<class T>
T& _chapter5_arrayListWithIterator<T>::get(int theIndex) const
{
	checkIndex(theIndex); 
	return element[theIndex];
}

template<class T>
int _chapter5_arrayListWithIterator<T>::indexOf(const T& theElement) const
{
	int theIndex = (int)(std::find(element, element + listSize, theElement) - element);
	if (theIndex == listSize) 
		return -1;
	else return theIndex;
}

template<class T>
void _chapter5_arrayListWithIterator<T>::erase(int theIndex)
{
	checkIndex(theIndex);
	std::copy(element + theIndex + 1, element + listSize, element + theIndex);
	element[--listSize].~T(); 
}

template<class T>
void _chapter5_arrayListWithIterator<T>::changeLength1D(T*& pa, int oldLength, int newLength)
{
	if (newLength < 0)
		throw illegalParameterValue("new length must be >=0");
	T* temp = new T[newLength];
	int number = std::min(oldLength, newLength);
	std::copy(pa, pa + number, temp);
	delete[] pa; 
	pa = temp; 
}

template<class T>
void _chapter5_arrayListWithIterator<T>::insert(int theIndex, const T& theElement)
{
	if (theIndex <0 || theIndex > listSize)
	{
		std::ostringstream s;
		s << "index = " << theIndex << "   size = " << listSize;
		throw illegalParameterValue(s.str());
	}
	if (listSize == arrayLength)
	{
		changeLength1D(element, arrayLength, 2 * arrayLength); 
		arrayLength *= 2;
	}
	std::copy_backward(element + theIndex, element + listSize, element + listSize + 1);
	element[theIndex] = theElement; 
	listSize++; 
}

template<class T>
void _chapter5_arrayListWithIterator<T>::output(std::ostream& out) const
{
	std::copy(element, element + listSize, std::ostream_iterator<T>(std::cout, "   "));
}

template<class T> 
std::ostream& operator << (std::ostream& out, const _chapter5_arrayListWithIterator<T>& x)
{
	x.output(out); 
	return out;
}

template<class T>
void _chapter5_arrayListWithIterator<T>::checkIndex(int theIndex) const
{
	if (theIndex < 0 || theIndex >= listSize)
	{
		std::ostringstream s;
		s << "index = " << theIndex << "   size - " << listSize;
		throw illegalParameterValue(s.str());
	}
}
#endif chapter5_arrayListBidirectIterator_