#include <iostream>
using namespace std;
#include "quote_pointer.h"
// 非静态变量占用字节 其它都不属于类对象 不占用字节
// 对于静态变量和静态函数 不属于类对象是没关系的它们本来就是静态的共用一份
// 非静态变量 属于类对象 不同对象都分配了一份非静态变量的内存空间 各自不影响
// 但非静态函数也不属于类对象 涉及到如何区分不同对象调用这一份函数的问题，引入this指针
class Person1{};
void test010()
{
	Person1 p;
	// 空对象占用内存1个子节 是为了区分空对象占内存的位置
	cout << "size of p = " << sizeof(p) << endl;
}
class Person2
{
	int _age; //非静态变量 属于类的对象上

	void func1() {} // 非静态函数  不属于类对象上

	static int _id; // 静态变量  不属于类对象上

	static void func2() {} // 静态函数  也不属于类对象上
};
void test011()
{
	Person2 p;
	// 非空对象非静态占用内存4个子节  其它不占用子节
	cout << "size of p = " << sizeof(p) << endl;
}
// this 指针指向被调用的成员函数所属的对象 不需要定义直接使用
// 简单来说Person p1,p2; p1.func() ;p2.func(); 
//*****注*****----------> 形参和成员变量同名时可以用this指针区分(解决名称冲突)
//*****注*****----------> 类的非静态成员函数中返回对象本身,可以使用 return *this
class Person3
{
public:
	//1、命名冲突 可以取不同名字解决
	//Person3(int  age) { _age = age; }
	//int _age;
	// 2、也可以使用this 解决
	//指针指向     被调用的成员函数Person(int age)  所属的对象p1
	Person3(int  age) { this->age = age; }//等价于p1->age = age ;
	int age;
	//3.返回对象本身用*this
	void PersonAddAge(Person3& p)
	{
		this->age += p.age;
	}
	Person3& _PersonAddAge(Person3& p)
		//返回调用的对象本身 这个对象可以继续调用返回本身
	{
		this->age += p.age; return *this;
	}

};
void test012()
{
	Person3 p1(18);
	//cout << "p1的年龄为 ：" << p1._age << endl;
	cout << "p1的年龄为 ：" << p1.age << endl;
}
void test013()
{
	//3.返回对象本身用*this
	Person3 p2(10);

	Person3 p3(18);
	p2.PersonAddAge(p3); //p2对象调用了这个函数 this也变成了p2
	cout << "p2的年龄为 ：" << p2.age << endl;
	p3.PersonAddAge(p2);
	cout << "p3的年龄为 ：" << p3.age << endl;

	// 对于PersonAddAge函数是不可以链式的调用自己
	// _PersonAddAge函数可以
	p2._PersonAddAge(p2)._PersonAddAge(p3)._PersonAddAge(p2);
	// 等价于下述连续调用的代码 p2=28 p3=46
	//p2._PersonAddAge(p2);
	//// p2 =28+28 = 56; p3=46;
	//cout << "第一层链式调用后p2的年龄为 ：" << p2.age << endl;
	//p2._PersonAddAge(p3);
	//// p2 = 56+46= 102 ;  p3=46
	//cout << "第二层链式调用后p2的年龄为 ：" << p2.age << endl;
	//// p2 =102 +102=204 ;p3=46
	//p2._PersonAddAge(p2);
	cout << "第三层链式调用后p2的年龄为 ：" << p2.age << endl;
}
// 空指针可以访问成员函数 但是需要注意有没有用的this指针 
// 如果用到需要判断保证代码的健壮性
class Person4
{
public:
	int _age;
	void showClassName() { cout << "this is a Person class" << endl; }
	void showPersonAge()
	{ 
		if (this == NULL) // 提高健壮性
		{
			return;
		}
		//cout << "age = " << this->_age <<endl;
		cout << "age = " << _age << endl; //即使不加this 编译器默认是加的
	}
};
void test014()
{
	Person4* p = NULL;
	p->showClassName(); // 空指针可以访问成员函数  this is a Person class
	p->showPersonAge(); // 但是空指针到102行代码时无法访问成员属性
}
int this_pointer()
//int main() 
{
	//copy_Construct(); // 拷贝构造函数运行
   // Deep_Shallow_Copy(); // 深拷贝与浅拷贝
	// classMember(); // 类作为类成员
	//static_member_func(); // 类的静态变量和静态函数

	test010();
	test011();

	test012();
	test013();

	test014();
	//system("pause");
	return 0;
}