#pragma once
#ifndef charter6_point2D_
#define charter6_point2D_
template<class T>
struct  _charter6_point2D
{
	T x;
	T y;
	_charter6_point2D() { this->x = 0; this->y = 0; }; // Ĭ�Ϲ���
	_charter6_point2D(const T &x, const T &y) //�㹹��
	{// ����ʹ��T&x��T &y,����ʹ��Point(2,2)�ᱨ��
		this->x = x;
		this->y = y;
	}
	_charter6_point2D(const _charter6_point2D<T>& point) // ���ƹ���
	{
		this->x = point.x;
		this->y = point.y;
	}
};
#endif 

