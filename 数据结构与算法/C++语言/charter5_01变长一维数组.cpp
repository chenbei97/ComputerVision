#pragma once
#include "charter1_illegalParameterValue.h"
// 此函数是线性表的具体类实例化中复制构造函数的实现的前身基础charter5_arrayList.cpp
template<class T>
void changeLength1D(T*& pa, int oldLength, int newLength)
{
	if (newLength < 0)
		throw illegalParameterValue("new length must be >=0");
	std::cout << "before change :  " << std::endl;
	for (int i = 0; i < oldLength; i++)
		std::cout << pa[i] << std::endl; // 可以执行
	T* temp = new T[newLength];
	// 如果新的长度变长最多复制原来的那么多元素,如果变短就复制当前这么多元素
	int number = std::min(oldLength, newLength);//要复制的元素个数
	printf("number = %d\n", number);
	std::copy(pa, pa + number, temp); // a是个T类型的指针的引用类型 可以+操作
	for (int i = number; i < newLength; i++)
		temp[i] = 0;
	delete[] pa; // 删除原来的容器元素
	//for (int i = 0 ;i<oldLength; i++) //->清空后不可在执行会报错
	//	std::cout << pa[i] << std::endl;
	pa = temp; // 指向新的容器
}
void _charter5_changeLength1D()
{
	const int n = 5;
	int* pa = new int[n];
	for (int i = 0; i < n; i++)
		pa[i] = i + 1;
	//for (int i = 0; i < n; i++)
	//	std::cout << pa[i] << std::endl;
	int oldlength = n;
	int newlength = 10;
	//printf("%d\n", std::min(5,10));
	changeLength1D(pa, oldlength, newlength);
	std::cout << "after change :  " << std::endl;
	for (int i = 0; i < newlength; i++)
		std::cout << pa[i] << std::endl;
}
