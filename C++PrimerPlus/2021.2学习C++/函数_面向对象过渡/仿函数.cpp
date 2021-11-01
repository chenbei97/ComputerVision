#include <iostream>
using namespace std;
#include "quote_pointer.h"
//copy_Construct(); // 拷贝构造函数运行
//Deep_Shallow_Copy(); // 深拷贝与浅拷贝
// classMember(); // 类作为类成员
//static_member_func(); // 类的静态变量和静态函数
//this_pointer(); // this 指针的使用
//friend_use(); // 友元的使用
// operatorOverload(); // 加减运算符重载
//leftmove(); // 左移运算符重载
//increment_Operator();  //  递增运算符重载
//assignment_Operator(); // 赋值运算符重载
// relational_Operator(); // 关系运算符重载
//int functor(); 仿函数

// 函数调用运算符重载 也就是'()'
class MyPrint
{
public:
	// 重载函数调用运算符'()'
	void operator()(string test)
	{
		cout << test << endl;
	}
};
void test_0009() 
{
	MyPrint myprint;
	myprint("hello"); // 实例化对象很像一个函数
}
class MyAdd
{
public:
	int operator()(int a, int b)
	{
		return a + b;
	}
};
void test_0010()
{
	MyAdd myadd;
	cout <<myadd(1, 2)<<endl;
	// 匿名函数对象
	cout << MyAdd()(100, 100) << endl; //类似于python的类方法
}
int functor()
//int main() 

{
	// 函数调用运算符()也可以重载 重载后的方式很像函数的调用 因此称为仿函数
	test_0009();
	test_0010();
	return 0; 
}