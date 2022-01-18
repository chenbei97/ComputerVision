#pragma once
#ifndef charter8_arrayList_
#define charter8_arrayList_
#include "charter5_linearList.h"
#include "charter1_illegalParameterValue.h"
#include <sstream>
// �������ִ�<_charter5_arrayList.h>���ƹ���,ʵ�ֲ��ִ�<charter5_arrayList�ķ��ļ�ʵ��.cpp>���ƹ���
template<class T>
class _charter8_arrayList : public _charter5_linearList<T>
{
public:
    _charter8_arrayList(int initialCapacity = 10); 
    _charter8_arrayList(const _charter8_arrayList<T>&); 
    ~_charter8_arrayList() { delete[] element; }
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
_charter8_arrayList<T>::_charter8_arrayList(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		std::ostringstream s; 
		s << "Initial Capacity = " << initialCapacity << "  Must be > 0";
		throw illegalParameterValue(s.str());
	}
	arrayLength = initialCapacity;
	element = new T[arrayLength]; // ��̬�������� �������������Ӧdelete [] element
	listSize = 0; //��ʱ0��Ա
}

template<class T>
_charter8_arrayList<T> ::_charter8_arrayList(const _charter8_arrayList<T>& theList)
{
	arrayLength = theList.arrayLength;
	listSize = theList.listSize;
	element = new T[arrayLength];
	std::copy(theList.element, theList.element + listSize, element); 
}

template<class T>
T& _charter8_arrayList<T>::get(int theIndex) const
{
	checkIndex(theIndex); 
	return element[theIndex];
}

template<class T>
int _charter8_arrayList<T>::indexOf(const T& theElement) const
{
	int theIndex = (int)(std::find(element, element + listSize, theElement) - element);
	if (theIndex == listSize) 
		return -1;
	else return theIndex;
}

template<class T>
void _charter8_arrayList<T>::erase(int theIndex)
{
	checkIndex(theIndex);
	std::copy(element + theIndex + 1, element + listSize, element + theIndex);
	element[--listSize].~T(); 
}

template<class T>
void _charter8_arrayList<T>::changeLength1D(T*& pa, int oldLength, int newLength)
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
void _charter8_arrayList<T>::insert(int theIndex, const T& theElement)
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
void _charter8_arrayList<T>::output(std::ostream& out) const
{
	std::copy(element, element + listSize, std::ostream_iterator<T>(std::cout, "   "));
}

template<class T> 
std::ostream& operator << (std::ostream& out, const _charter8_arrayList<T>& x)
{
	x.output(out); 
	return out;
}

template<class T>
void _charter8_arrayList<T>::checkIndex(int theIndex) const
{
	if (theIndex < 0 || theIndex >= listSize)
	{
		std::ostringstream s;
		s << "index = " << theIndex << "   size - " << listSize;
		throw illegalParameterValue(s.str());
	}
}
#endif // !charter8_arrayList_
