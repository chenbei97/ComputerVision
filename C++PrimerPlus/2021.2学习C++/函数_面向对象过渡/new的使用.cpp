#include <iostream>
using namespace std;
//1.new的基本语法
int* func1()
{
	int* p = new int(100); //把100的地址或者指针返回
	return p;
}
void test1()
{
	int* p = func1();
	cout << *p << endl;
	// 然后想释放堆区数据可以使用delete
	delete p;
	//cout << *p << endl; // 不能再执行该语句
}
//2.堆区开辟数组
void func2()
{
	int* arr = new int[10]; //[]来创建数组 返回的是数组首地址 且这块堆区不需要数组名
	for (int i = 0; i < 10; i++)
	{
		arr[i] = i + 100;
	}
	for (int i = 0; i < 10; i++)
	{
		cout << arr[i] << endl;
	}
	// 释放数组
	delete[]  arr; //加综括号才能释放数组堆区
}
void The_Use_Of_New()
{
	//int main()
		//1.new的基本语法
	test1(); // 返回100
	//2.new创建数组
	func2();
	//system("pause ");
	//return 0;
}