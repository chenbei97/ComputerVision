#include "all.h"
struct job
{
	char name[40];
	double salary;
	int floor;
};
void Swap(job& a, job& b)// 非模板函数
{
	cout << "非模板类函数被调用..." << endl;
	job c;
	c = a;
	a = b;
	b = c;
}
template <typename T>
void Swap(T& a, T& b)//普通模板函数,如果传入结构体,会交换结构体的全部成员
{
	cout << "普通模板类被调用..." << endl;
	T c;
	c = a;
	a = b;
	b = c;
}
template <> void Swap<job>(job& a, job& b)// 显式具体化版本,允许只交换部分成员
{
	cout << "显式化具体模板类被调用..." << endl;
	double s;
	s = a.salary;
	a.salary = b.salary;
	b.salary = s;

	int f;
	f = a.floor;
	a.floor = b.floor;
	b.floor = f;
}
template <typename T>
void Study__Func_Template_Swap(T& a, T& b)
{
	T c;
	c = a;
	a = b;
	b = c;
}
void Study_Func_Template()
{
	// 显式实例化
	//template void Swap<int>(int& a, int& b);当前不能显式实例化


	// 普通模板类，可以交换结构体
	int a1 = 1, a2 = 2;
	Study__Func_Template_Swap(a1, a2);
	cout << "a1=" << a1 << "   a2=" << a2;

	double b1 = 1.1, b2 = 2.2;
	Study__Func_Template_Swap(b1, b2);
	cout << "	b1=" << b1 << "   b2=" << b2;

	// 非模板函数、普通模板函数和显式化模板函数的优先级比较
	// 同时存在时,非模板函数先被调用
	job j1 = { "a",1.5,3 }, j2 = { "b",2.4,6 };
	cout << "before swap：" << " &j1=" << &j1 << "   &j2=" << &j2 << endl;
	Swap(j1, j2);
	cout << "j1.salary=" << j1.salary << "   j2.salary=" << j2.salary << endl;


}


