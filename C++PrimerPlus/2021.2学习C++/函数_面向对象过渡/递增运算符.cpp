#include <iostream>
using namespace std;
#include "quote_pointer.h"
// 递增运算符重载 ++ 自定义自己的数据类型
class myInteger
{
	// friend void test_0004();
	friend ostream& operator << (ostream& cout, myInteger myint);
public:
	myInteger()
	{
		_num = 10;
	}
	// 1.重载前置++运算符
	myInteger&  operator++() // myInteger operator++()
	{
		// 返回引用 是为了一直对一个数据进行递增
		// 正常来说a=0 ; |  ++(++a) =2 ;a =2 ;
		// 如果不返回引用  ++(++myint) = 2 ; 但是 myint =1 ;
		// 不返回引用第一层的++myint 就变成一个新的变量而不是原来的 
		// 这时候对这个新的++不会改变原来的myint 仍然为1
		_num++;
		return  *this;  // 返回自身的地址
	}
	// 重载后置++运算符
	myInteger operator++(int) //int可以用来占位区分前置和后置
	{
	      // 先记录当时结果
		myInteger temp = *this;
		_num++;
		return temp; // temp是局部变量 只能返回值
	}
private : 
	int _num; 
};
// 重载<<运算符
ostream & operator << (ostream& cout, myInteger  myint) 
{
	cout << myint._num; // 真正的返回值输出
	return cout;
}
void test_0004()
{
	myInteger  myint; // 不是真正的整型 因为返回值是类的私有属性
	cout << ++(++myint)<< endl; // 前置运算符可以链式运算 因为可以返回地址
	cout << myint << endl;
}
void test_0005()
{
	myInteger  myint;
	cout << ++(myint++) << endl; // 后置递增不能作链式运算 返回的值
	cout << myint << endl;
}
int increment_Operator()
// int main()
{
	//copy_Construct(); // 拷贝构造函数运行
	// Deep_Shallow_Copy(); // 深拷贝与浅拷贝
	// classMember(); // 类作为类成员
	//static_member_func(); // 类的静态变量和静态函数
	//this_pointer(); // this 指针的使用
	//friend_use(); // 友元的使用
	// operatorOverload(); // 运算符重载
	//leftmove(); // 左移运算符重载

	test_0004();
	test_0005();

	return 0;
}