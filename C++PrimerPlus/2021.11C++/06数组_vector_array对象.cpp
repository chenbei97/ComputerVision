#include "all.h"
void Study_Fill_Array(array<double, 4>* p);
void Study_Show_Array(array<double, 4>  p);
void Study_compare_arr_vector_array()
{
	double arr1[4] = { 1.2,2.4,4.8,9.6 };
	double arr1_[4];
	vector<double> arr2(4);
	vector<double> arr2_(4);
	array<double, 4> arr3 = { 1.1,1.2,1.3,1.4 };// 可以初始化也可以不初始化
	array<double, 4> arr3_;
	// vector的必须单独初始化
	arr2[0] = 1.0 / 3; arr2[1] = 1.0 / 5; arr2[2] = 1.0 / 7; arr2[3] = 1.0 / 9;

	// 相同点都可以使用索引进行访问
	cout << "arr1[0]=" << arr1[0] << "  arr2[0]=" << arr2[0] << "  arr3[0]=" << arr3[0] << endl;

	// 区别普通数组不能直接赋值，array/vector对象可以
	// arr1_ = arr1; 非法
	arr2_ = arr2;
	arr3_ = arr3;

	// 普通数组不会检查越界错误.vector/array可以使用at函数禁止越界
	arr1[-2] = 20.1; // 实际上就是*(arr1-2),这块内存不属于arr1
	cout << "&arr1[-2]=" << &arr1[-2] << "  !=  &arr1=" << &arr1 << endl;
	//arr2.at(-2) = 20.1; at检测到非法索引之后中断
	arr2.at(2) = 20.1; arr3.at(2) = 20.3;// 合法
	cout << "arr2[2]=" << arr2[2] << "arr3[2]=" << arr3[2] << endl;

	int x1 = 5, x2 = 5, y;
	y = x1++;
	cout << "先计算表达式x1++=" << y << "，然后自增x1=" << x1 << endl;
	//先计算表达式x1++ = 5，然后自增x1 = 6
	y = ++x2;
	cout << "先自增然后计算表达式x2++=" << y << "，此时x2=" << x2 << endl;
	//先自增然后计算表达式x2++ = 6，此时x2 = 6

	// 函数与array对象
	array<double, 4> arr;
	Study_Fill_Array(&arr); // 传入地址
	Study_Show_Array(arr);// 传入对象
	system("pause");
}
void Study_Fill_Array(array<double, 4>* p)
{
	for (int i = 0; i < 4; i++)
	{
		(*p)[i] = i; // p是指针,解引用后才是数组
	}
}
void Study_Show_Array(array<double, 4>  p)
{
	for (int i = 0; i < 4; i++)
	{
		cout << p[i] << endl;
	}
}