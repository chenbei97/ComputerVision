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
class Person
{
public:
	string _name;
	int _age;
	Person() {};
	Person(string name, int age)
	{
		_age = age;
		_name = name;
	}
	~Person() { cout << "-------析构函数到此一游--------" << endl; }
	bool operator==(Person& p)
	{
		if (this->_age == p._age && this->_name == p._name)
		{
			return true;
		}
		return false;
	}
};
void test_0008()
{
	Person p1("Tom", 19);

	Person p2("Tom", 18);

	if (p1 == p2) // 需要重载恒等号"=="
	{cout << "p1和p2相等"<<endl;}
	else { cout << "p1和p2不相等" << endl; }
}
int relational_Operator()
//int main()
{
	// 对两个自定义的数据进行关系运算
	test_0008();
    /*
	p1和p2不相等
	-------析构函数到此一游--------
	-------析构函数到此一游--------
	*/
	return 0;
}