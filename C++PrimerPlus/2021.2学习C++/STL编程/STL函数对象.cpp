#include "contanter.h"
/*
<1>函数对象概念
			重载函数调用操作符的类，其对象常称为函数对象
			函数对象使用重载的()时行为类似函数调用 即仿函数
			本质：函数对象(仿函数)是一个类，不是一个函数
<2>函数对象特点
			函数对象使用时可以像普通函数调用，可以有参数和返回值
			函数对象可以作为参数传递，超出普通函数的概念可以有自己的状态
*/
class Myadd
{
public:
	int operator ()(int v1, int v2)
	{
		return v1 + v2;
	}

};
class Myprint
{
public:
	Myprint()
	{
		this->count = 0;
	}
	void operator()(string test)
	{
		cout <<"test："<< test << endl;
		this->count++;
	}
	int count; // 记录函数调用几次
};
void doPrint(Myprint& mp, string test)
{
	mp(test);
}
void test_35()
{
	Myadd myadd;
	cout << myadd(10, 10) << endl;
	// 超出普通函数的概念可以有自己的状态
	Myprint myprint;
	myprint("helloworld");
	myprint("helloworld");
	cout << myprint.count << endl;
	spilit_line();
	// 函数对象myprint可以作为参数传递
	doPrint(myprint, "helloC++");
}
int stl_func_object()
//int main()
{
	 // stl_example2();
	test_35();
	return 0;
}