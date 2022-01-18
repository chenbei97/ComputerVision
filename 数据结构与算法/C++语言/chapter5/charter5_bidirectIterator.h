#pragma once
#include <iterator>
#include <iostream>
/*

*/
template<class T>
class _charter5_bidirectIterator
{
public:
	// ʹ��typedefʵ��˫�������,�������ؼ��������
	// bidirectional_iterator_tag,T,ptrdiff_t, T*, T&������Ӧ�ı���
	// ����bidirectional_iterator_tag��ptrdiff_t����include <iterator>��std�����ռ���
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef  T value_type;
	typedef std::ptrdiff_t  difference_type;
	typedef T* pointer;
	typedef T& reference;

	// Ĭ�Ϲ��캯��,���������һ��ָ��,ָ��Ĭ��ָ��ͷ
	_charter5_bidirectIterator(T* thePosition = 0) { position = thePosition; }

	// ���ؽ�����*,->������
	T& operator*() const { return *position; }
	// 	һ����/�ṹ��ʵ��sȥ���ʳ�Ա��ʹ��s.func()
	// �����ָ��s��һ��ָ��p���ʳ�Ա����Ҫ��������ʹ�þ�������
	// ������������ü�ͷ������ȼۡ���p->func() <=>(*p).func()
	T* operator->() const { return &*position; }
	void print_position() const
	{
		// �˺�����Ϊ�˲��Լ�ͷ���������ӵ�,���������˽�г�Աposition4
		std::cout << "the current pointer position value is " << *position << std::endl;
	}

	// ˫���������++����������
	_charter5_bidirectIterator& operator++()
	{
		++position; return *this; // ǰ�� �����ȼӣ�Ȼ������������
		// ע�����ʵ�֣�
	}
	_charter5_bidirectIterator operator++(int) // ��� �������������Ȼ���ڶ��������������
	{
		_charter5_bidirectIterator old = *this;
		++position;
		return old;
	}

	// ˫���������--����������
	_charter5_bidirectIterator& operator--()   // ǰ��
	{
		--position; return *this;
	}
	_charter5_bidirectIterator operator--(int) // ���
	{
		_charter5_bidirectIterator old = *this;
		--position;
		return old;
	}

	// �����Ƿ����
	bool operator!=(const _charter5_bidirectIterator right) const
	{
		return position != right.position;
	}
	bool operator==(const _charter5_bidirectIterator right) const
	{
		return position == right.position;
	}
protected:
	T* position;
};