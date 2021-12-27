#pragma once
#include "charter5_linearList.h"
#include "charter1_illegalParameterValue.h"
#include <iterator> // ʹ��bidirectional_iterator_tag��ptrdiff_t
#include<sstream> // ʹ��ostringstream

// ���Ա���������ľ������������ֺ�ʵ��д��ͬһ�ļ���
// �Ϳ��Ա������ļ�����
template<class T>
class _charter5_arrayListWithIterator : public _charter5_linearList<T>
{
public:
    _charter5_arrayListWithIterator(int initialCapacity = 10);
    _charter5_arrayListWithIterator(const _charter5_arrayListWithIterator<T>&);
    ~_charter5_arrayListWithIterator() { delete[] element; }

    bool empty() const { return listSize == 0; }
    int size() const { return listSize; }
    T& get(int theIndex) const;
    int indexOf(const T& theElement) const; 
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    void output(std::ostream& out) const;
    int capacity() const { return arrayLength; }

	// ��������������Ϊ���Ա���Ĺ��г�Ա,���������2������Ҳ�ǹ��г�Ա
	class _charter5_iterator;// �౾��Ҳ��1����Ա
	_charter5_iterator begin() { return _charter5_iterator(element); } // element�Ǹ�ָ�����Ա�ͷ��ָ��,��Ӧbegin
	_charter5_iterator end() { return _charter5_iterator(element + listSize); }// element+listSize�����1��Ԫ�صĺ�1��λ��
	class _charter5_iterator
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
		_charter5_iterator(T* thePosition = 0) { position = thePosition; }

		// ���ؽ�����*,->������
		T& operator*() const { return *position; }
		T* operator->() const { return &*position; }

		// ˫���������++����������
		_charter5_iterator& operator++()   
		{
			++position; return *this; // ǰ�� �����ȼ�,Ȼ������������<=>++operator
			// ע�����ʵ�֣�position�Ѿ���+�ٷ���this,��ʱ���ʽֵ�Ѿ��仯
		}
		_charter5_iterator operator++(int) // ��� �����������,Ȼ���ڶ��������������<=>operator++
		{
			// i++ ��� �൱��+1,��Ҫ����int����
			// �ȱ���+֮ǰ�Ľ��,Ҳ����positionû+,���ʽֵû��
			_charter5_iterator old = *this;
			++position;
			return old;
		}

		// ˫���������--����������
		_charter5_iterator& operator--()   // ǰ��
		{
			--position; return *this;
		}
		_charter5_iterator operator--(int) // ���
		{
			_charter5_iterator old = *this;
			--position;
			return old;
		}

		// �����Ƿ����
		bool operator!=(const _charter5_iterator right) const
		{
			// ���Ӧ����this,�Ҳ�Ӧ���Ǵ�������ָ��
			// ����iterator != x.end() ��2����������!=����
			return position != right.position; // �������Ƿ������Ҫת��Ϊ������ָ��ĵ�ַ�Ƿ����
		}
		bool operator==(const _charter5_iterator right) const
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
_charter5_arrayListWithIterator<T>::_charter5_arrayListWithIterator(int initialCapacity)
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
_charter5_arrayListWithIterator<T> ::_charter5_arrayListWithIterator(const _charter5_arrayListWithIterator<T>& theList)
{
	arrayLength = theList.arrayLength;
	listSize = theList.listSize;
	element = new T[arrayLength];
	std::copy(theList.element, theList.element + listSize, element); 
}

template<class T>
T& _charter5_arrayListWithIterator<T>::get(int theIndex) const
{
	checkIndex(theIndex); 
	return element[theIndex];
}

template<class T>
int _charter5_arrayListWithIterator<T>::indexOf(const T& theElement) const
{
	int theIndex = (int)(std::find(element, element + listSize, theElement) - element);
	if (theIndex == listSize) 
		return -1;
	else return theIndex;
}

template<class T>
void _charter5_arrayListWithIterator<T>::erase(int theIndex)
{
	checkIndex(theIndex);
	std::copy(element + theIndex + 1, element + listSize, element + theIndex);
	element[--listSize].~T(); 
}

template<class T>
void _charter5_arrayListWithIterator<T>::changeLength1D(T*& pa, int oldLength, int newLength)
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
void _charter5_arrayListWithIterator<T>::insert(int theIndex, const T& theElement)
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
void _charter5_arrayListWithIterator<T>::output(std::ostream& out) const
{
	std::copy(element, element + listSize, std::ostream_iterator<T>(std::cout, "   "));
}

template<class T> 
std::ostream& operator << (std::ostream& out, const _charter5_arrayListWithIterator<T>& x)
{
	x.output(out); 
	return out;
}

template<class T>
void _charter5_arrayListWithIterator<T>::checkIndex(int theIndex) const
{
	if (theIndex < 0 || theIndex >= listSize)
	{
		std::ostringstream s;
		s << "index = " << theIndex << "   size - " << listSize;
		throw illegalParameterValue(s.str());
	}
}