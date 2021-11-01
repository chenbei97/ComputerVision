#include <iostream>
using namespace std;
#include "quote_pointer.h"
/*
左移运算符重载 ：可以输出自定义数据类型
1.不能利用成员函数重载 因为<< 是单目运算符 cout << a 
p.operator<<(p) 等价于p1 cout << p2不是想要的  p.operator<<(cout) ----->等价于 p << cout
2. 可以利用全局函数重载
*/
class Person
{
	friend ostream& operator<< (ostream& cout, Person& p);
	friend void test_0003();
private:
	int _a;
	int _b;
};
ostream & operator<< (ostream &cout, Person &p)  
 //operator << (cout ,p) 简化为cout << p 
// cout 改为 out 也是可以的 因为是地址引用
{
	cout << "\n_a = " << p._a << "_b = " << p._b;
	return cout; // 可以链式加载输出
}
void test_0003()
{
	Person p;
	
	p._a = 10;
	p._b = 20;
	cout << p._a;
	cout << p << "\thello_world" <<endl; // 没有void operator<< (ostream &cout, Person &p)  函数是不能直接运算的
	
}
int leftmove()
//int main()
{
	//copy_Construct(); // 拷贝构造函数运行
	// Deep_Shallow_Copy(); // 深拷贝与浅拷贝
	// classMember(); // 类作为类成员
	//static_member_func(); // 类的静态变量和静态函数
	//this_pointer(); // this 指针的使用
	//friend_use(); // 友元的使用
	// operatorOverload(); // 运算符重载

	test_0003();

	//system("pause");
	return 0;
}