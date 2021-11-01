#include <iostream>
using namespace std;
#include "quote_pointer.h"
// 用operator对已有的运算符重定义 赋予新的功能 对两个自定义数据类型进行运算
// 1.利用成员函数 对运算符号进行重载
class Person
{
public:
	int _a;
	int _b;
	Person operator+ (Person& p) // 成员函数
	{
		Person temp;
		temp._a = this->_a + p._a;
		temp._b = this->_b + p._b;
		return temp;
	}
};

void test_0001()
{
	Person p1;
	p1._a = 10;
	p1._b = 20;
	Person p2;
	p2._a = 10;
	p2._b = 20;
	Person p3 = p1.operator+(p2);
	Person p4 = p1 +  p2; // 本质就是上一行代码
	cout << "成员函数重载 p3的a = " << p3._a << endl;
	cout <<"成员函数重载 p4的b = "<< p4._b << endl;
}
// 2.全局函数重载
Person operator + (Person& p1, Person& p2)
{
	Person temp;
	temp._a = p1._a + p2._a;
	temp._b = p1._b + p2._b;
	return temp;
}
void test_0002()
{
	Person p1;
	p1._a = 100;
	p1._b = 200;
	Person p2;
	p2._a = 100;
	p2._b = 200;
	Person p3 = operator+ (p1, p2); // 本质调用
	//Person p4 = p1 + p2; // 重定义了 不知道是用上一行的还是28行代码的
	cout << "\n全局函数重载 p3的a = " << p3._a << endl;
	//cout << "全局函数重载 p4的b = " << p4._b << endl;
}
int operatorOverload()
//int main()
{
	//copy_Construct(); // 拷贝构造函数运行
	// Deep_Shallow_Copy(); // 深拷贝与浅拷贝
	// classMember(); // 类作为类成员
	//static_member_func(); // 类的静态变量和静态函数
	//this_pointer(); // this 指针的使用
	//friend_use(); // 友元的使用


	test_0001();
	test_0002();

	system("pause");
	return 0;	
}