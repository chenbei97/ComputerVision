#pragma once
#ifndef chapter5_arrayListBidirectIterator_
#define chapter5_arrayListBidirectIterator_
#include "chapter5_linearList.h"
#include "chapter1_illegalParameterValue.h"
#include <iterator> // ʹ��bidirectional_iterator_tag��ptrdiff_t
#include<sstream> // ʹ��ostringstream

// ���Ա���������ľ������������ֺ�ʵ��д��ͬһ�ļ���
// �Ϳ��Ա������ļ�����
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

	// ��������������Ϊ���Ա���Ĺ��г�Ա,���������2������Ҳ�ǹ��г�Ա
	class _chapter5_iterator;// �౾��Ҳ��1����Ա
	_chapter5_iterator begin() { return _chapter5_iterator(element); } // element�Ǹ�ָ�����Ա�ͷ��ָ��,��Ӧbegin
	_chapter5_iterator end() { return _chapter5_iterator(element + listSize); }// element+listSize�����1��Ԫ�صĺ�1��λ��
	class _chapter5_iterator
	{
	public:
		// ʹ��typedefʵ��˫�������,�������ؼ��������
		// bidirectional_iterator_tag,T,ptrdiff_t, T*, T&������Ӧ�ı���
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef  T value_type;
		typedef std::ptrdiff_t  difference_type;
		typedef T* pointer;
		typedef T& reference;

		// Ĭ�Ϲ��캯��,���������һ��ָ��
		_chapter5_iterator(T* thePosition = 0) { position = thePosition; }

		// ���ؽ�����*,->������
		T& operator*() const { return *position; }
		T* operator->() const { return &*position; }

		// ˫���������++����������
		_chapter5_iterator& operator++()   
		{
			++position; return *this; // ǰ�� �����ȼ�,Ȼ������������<=>++operator
			// ע�����ʵ�֣�position�Ѿ���+�ٷ���this,��ʱ���ʽֵ�Ѿ��仯
		}
		_chapter5_iterator operator++(int) // ��� �����������,Ȼ���ڶ��������������<=>operator++
		{
			// i++ ��� �൱��+1,��Ҫ����int����
			// �ȱ���+֮ǰ�Ľ��,Ҳ����positionû+,���ʽֵû��
			_chapter5_iterator old = *this;
			++position;
			return old;
		}

		// ˫���������--����������
		_chapter5_iterator& operator--()   // ǰ��
		{
			--position; return *this;
		}
		_chapter5_iterator operator--(int) // ���
		{
			_chapter5_iterator old = *this;
			--position;
			return old;
		}

		// �����Ƿ����
		bool operator!=(const _chapter5_iterator right) const
		{
			// ���Ӧ����this,�Ҳ�Ӧ���Ǵ�������ָ��
			// ����iterator != x.end() ��2����������!=����
			return position != right.position; // �������Ƿ������Ҫת��Ϊ������ָ��ĵ�ַ�Ƿ����
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