#pragma once
#ifndef chapter6_point2D_
#define chapter6_point2D_
template<class T>
struct  _chapter6_point2D
{
	T x;
	T y;
	_chapter6_point2D() { this->x = 0; this->y = 0; }; // 默认构造
	_chapter6_point2D(const T &x, const T &y) //点构造
	{// 不可使用T&x和T &y,否则使用Point(2,2)会报错
		this->x = x;
		this->y = y;
	}
	_chapter6_point2D(const _chapter6_point2D<T>& point) // 复制构造
	{
		this->x = point.x;
		this->y = point.y;
	}
};
#endif chapter6_point2D_

