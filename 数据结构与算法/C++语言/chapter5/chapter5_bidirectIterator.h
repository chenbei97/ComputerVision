#pragma once
#ifndef chapter5_bidirectIterator_
#define chapter5_bidirectIterator_
#include <iterator>
#include <iostream>
template<class T>
class _chapter5_bidirectIterator
{
public:
	// 使用typedef实现双向迭代器,将下述关键字起别名
	// bidirectional_iterator_tag,T,ptrdiff_t, T*, T&都起相应的别名
	// 其中bidirectional_iterator_tag和ptrdiff_t必须include <iterator>且std命名空间下
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef  T value_type;
	typedef std::ptrdiff_t  difference_type;
	typedef T* pointer;
	typedef T& reference;

	// 默认构造函数,传入参数是一个指针,指针默认指向开头
	_chapter5_bidirectIterator(T* thePosition = 0) { position = thePosition; }

	// 重载解引用*,->操作符
	T& operator*() const { return *position; }
	// 	一个类/结构的实例s去访问成员，使用s.func()
	// 如果是指向s的一个指针p访问成员，需要解引用再使用句点运算符
	// 这个操作可以用箭头运算符等价。即p->func() <=>(*p).func()
	T* operator->() const { return &*position; }
	void print_position() const
	{
		// 此函数是为了测试箭头运算符特意加的,功能是输出私有成员position4
		std::cout << "the current pointer position value is " << *position << std::endl;
	}

	// 双向迭代器的++操作符重载
	_chapter5_bidirectIterator& operator++()
	{
		++position; return *this; // 前加 就是先加，然后才用这个变量
		// 注意如何实现：
	}
	_chapter5_bidirectIterator operator++(int) // 后加 先用这个变量，然后在对这个变量做自增
	{
		_chapter5_bidirectIterator old = *this;
		++position;
		return old;
	}

	// 双向迭代器的--操作符重载
	_chapter5_bidirectIterator& operator--()   // 前减
	{
		--position; return *this;
	}
	_chapter5_bidirectIterator operator--(int) // 后减
	{
		_chapter5_bidirectIterator old = *this;
		--position;
		return old;
	}

	// 测试是否相等
	bool operator!=(const _chapter5_bidirectIterator right) const
	{
		return position != right.position;
	}
	bool operator==(const _chapter5_bidirectIterator right) const
	{
		return position == right.position;
	}
protected:
	T* position;
};
#endif chapter5_bidirectIterator_