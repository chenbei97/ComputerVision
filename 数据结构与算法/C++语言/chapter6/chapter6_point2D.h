#pragma once
#ifndef chapter6_point2D_
#define chapter6_point2D_
template<class T>
struct  _chapter6_point2D
{
	T x;
	T y;
	_chapter6_point2D() { this->x = 0; this->y = 0; }; // Ĭ�Ϲ���
	_chapter6_point2D(const T &x, const T &y) //�㹹��
	{// ����ʹ��T&x��T &y,����ʹ��Point(2,2)�ᱨ��
		this->x = x;
		this->y = y;
	}
	_chapter6_point2D(const _chapter6_point2D<T>& point) // ���ƹ���
	{
		this->x = point.x;
		this->y = point.y;
	}
};
#endif chapter6_point2D_

