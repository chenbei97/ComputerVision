#include "all.h"
void method_1(int n);
void method_2(int n);
void select(int n, void (*p)(int));
void Study_Func_Pointer()
{
	int n;
	cout << "please input n = " ;
	cin >> n;
	if (n == 1)
	{
		select(n, method_1);// 时刻1使用算法1
	}
	else
	{
		select(n, method_2);// 时刻2使用算法2
	}
	system("pause");
}

void select(int n, void (*p)(int))
{
	// double (*p)(int) 和 原型double method_1(int n)是相似的
	// 所以(*p)对照就是函数,那么p就是函数指针
	(*p)(n); // 执行函数
	p(n); // 也可以，C++中认为函数指针p和(*p)等价
}
void method_1(int n)
{
	cout << "method_1 = " << n << endl;
}
void method_2(int n)
{
	cout << "method_2 = " << n << endl;
}