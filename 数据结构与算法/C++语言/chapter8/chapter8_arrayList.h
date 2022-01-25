#pragma once
#ifndef chapter8_arrayList_
#define chapter8_arrayList_
#include "chapter5_linearList.h"
#include "chapter1_illegalParameterValue.h"
#include <sstream>
// 声明部分从<_charter5_arrayList.h>复制过来,实现部分从<charter5_arrayList的分文件实现.cpp>复制过来
template<class T>
class _chapter8_arrayList : public _chapter5_linearList<T>
{
public:
    _chapter8_arrayList(int initialCapacity = 10); 
    _chapter8_arrayList(const _chapter8_arrayList<T>&); 
    ~_chapter8_arrayList() { delete[] element; }
    bool empty() const { return listSize == 0; }
    int size() const { return listSize; }
    T& get(int theIndex) const;
    int indexOf(const T& theElement) const; 
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    void output(std::ostream& out) const;
    int capacity() const { return arrayLength; }
protected:
    void checkIndex(int theIndex) const; 
    void changeLength1D(T*& pa, int oldLength, int newLength); 
    int arrayLength;
    int listSize; 
    T* element;
};

template<class T>
_chapter8_arrayList<T>::_chapter8_arrayList(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		std::ostringstream s; 
		s << "Initial Capacity = " << initialCapacity << "  Must be > 0";
		throw illegalParameterValue(s.str());
	}
	arrayLength = initialCapacity;
	element = new T[arrayLength]; // 动态开辟数组 析构函数必须对应delete [] element
	listSize = 0; //暂时0成员
}

template<class T>
_chapter8_arrayList<T> ::_chapter8_arrayList(const _chapter8_arrayList<T>& theList)
{
	arrayLength = theList.arrayLength;
	listSize = theList.listSize;
	element = new T[arrayLength];
	std::copy(theList.element, theList.element + listSize, element); 
}

template<class T>
T& _chapter8_arrayList<T>::get(int theIndex) const
{
	checkIndex(theIndex); 
	return element[theIndex];
}

template<class T>
int _chapter8_arrayList<T>::indexOf(const T& theElement) const
{
	int theIndex = (int)(std::find(element, element + listSize, theElement) - element);
	if (theIndex == listSize) 
		return -1;
	else return theIndex;
}

template<class T>
void _chapter8_arrayList<T>::erase(int theIndex)
{
	checkIndex(theIndex);
	std::copy(element + theIndex + 1, element + listSize, element + theIndex);
	element[--listSize].~T(); 
}

template<class T>
void _chapter8_arrayList<T>::changeLength1D(T*& pa, int oldLength, int newLength)
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
void _chapter8_arrayList<T>::insert(int theIndex, const T& theElement)
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
void _chapter8_arrayList<T>::output(std::ostream& out) const
{
	std::copy(element, element + listSize, std::ostream_iterator<T>(std::cout, "   "));
}

template<class T> 
std::ostream& operator << (std::ostream& out, const _chapter8_arrayList<T>& x)
{
	x.output(out); 
	return out;
}

template<class T>
void _chapter8_arrayList<T>::checkIndex(int theIndex) const
{
	if (theIndex < 0 || theIndex >= listSize)
	{
		std::ostringstream s;
		s << "index = " << theIndex << "   size - " << listSize;
		throw illegalParameterValue(s.str());
	}
}
#endif // !chapter8_arrayList_
