#include <iostream>
using namespace std;
#include "quote_pointer.h"
/*
* 成员属性不能修改 : ①外部限定为常对象②内部限定常函数
1.成员函数加cosnt后称之为常函数(内部限定)
2.常函数内不能修改成员属性 指向和值都不能修改
3.成员属性加mutable时常函数中依然可以修改
4.声明对象前 加const 对象为常对象(外部限定)
5.常对象只能调用常函数
*/
class Person
{
public:
	int  _age;
	mutable int _id; //特殊声明
	// 普通函数
	void showPerson1() 
	{
		//this指针是指针常量 指向不能修改
		// this = NULL;
		_age = 100;  // 但可以赋值
	}
	// 常函数
	void showPerson2() const 
	{
		// 不仅指向不能修改 , 值也不能修改
		// 变为常量指针常量 即纯常量指针
		//_age = 100;  
		_id = 100; // mutable变量仍然能够修改
	}
};
void test110()
{
	Person p;
	p.showPerson1(); 
	p.showPerson2();
}
void test111()
{
	const Person p; //常对象 
	// p._age = 100; // 常对象不允许修改普通变量
	p._id = 100; // 常对象可以修改mutable变量
	p.showPerson2();  // 但是可访问常函数 不能访问showPerson1()
}
int const_classfunc()
//int main() 
{
	//copy_Construct(); // 拷贝构造函数运行
	// Deep_Shallow_Copy(); // 深拷贝与浅拷贝
	// classMember(); // 类作为类成员
	//static_member_func(); // 类的静态变量和静态函数
	//this_pointer();

	system("pause");
	return 0;
}