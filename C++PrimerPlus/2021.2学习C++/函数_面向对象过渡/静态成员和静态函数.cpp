#include <iostream>
using namespace std;
#include "quote_pointer.h"
/* 静态成员 : 加上关键字 static 不是不能改变的意思,而是每个对象不能单独改变
1.静态属性
1.1所有对象共享一份数据(全局)
1.2 编译阶段分配内存
1.3类内声明,类外初始化
1.4访问方式  : 都可以改变静态变量
1.4.1 对象访问 :  p._age = 100; 
1.4.2  类作用域访问 	Person::func(60)
2.静态函数
2.1所有对象共享一个函数
2.2 静态函数只能访问静态变量 : 静态变量在全局区
2.3 类初始化不同对象时非静态变量都是可以不同的,静态变量则完全相同
2.4 类似的非静态函数不同对象只能用来改变非静态变量,而静态函数所有对象都实现同一个功能
*/
/*
简单来说，类中的静态变量是不能初始化的，只能类外声明，且类初始化的不同对象p1和p2都共用一份数据，p1可以改变，p2也可以改变
同时静态函数只能访问静态变量，所以p1的静态函数调用时改变静态变量，p2去访问时也会接受改变
*/
class Person
{
public:
	static void func(int age)
	{
		_age = age;
		//_id = 200; 不能访问非静态变量
		cout << "------>static void func 调用<------" << endl;
	}
	//1.3类内声明, 类外初始化
	static int _age ; //静态属性 不能在类内初始化静态变量值 
	int _id;
};
int Person::_age = 0; //宏常量初始化定义
void test001() 
{
	Person p;
	cout << "p赋值前年龄为 : " << p._age << endl;
	p._age = 100; // 类外初始化 对象去访问
	cout << "p赋值后年龄为 : " << p._age << endl;
	p.func(100);
	cout << "p的func函数调用后年龄为 : " << p._age << endl;

	Person::func(60); // 类作用域直接访问
	cout << "p的作用域func函数访问后年龄为 : " << p._age << endl;
	/*
	p赋值前年龄为 : 0
	p赋值后年龄为 : 100
	------>static void func 调用<------
	p的func函数调用后年龄为 : 100
	------>static void func 调用<------
	p的作用域func函数访问后年龄为 : 60
	*/
}
void test002()
{
	 //1.通过对象访问
	Person p1;
	cout << "p1的func调用前年龄为 : " << p1._age <<endl;
	p1.func(20);
	cout << "p1的func调用后年龄为 : " << p1._age << endl;
	Person p2; 
	// 可以看出静态函数把新对象p2也改变了
	cout << "p2的func调用前年龄为 : " << p2._age << endl;
	p2.func(100);
	cout << "p2的func调用后年龄为 : " << p2._age << endl;
	// 可以看出静态函数把原对象p1也改变了
	cout << "p1的func再次调用前年龄为 : " << p1._age << endl;
	/* OutPut :
	p1的func调用前年龄为 : 60
	------>static void func 调用<------
	p1的func调用后年龄为 : 20
	p2的func调用前年龄为 : 20
	------>static void func 调用<------
	p2的func调用后年龄为 : 100
	p1的func再次调用前年龄为 : 100
	*/
	//2. 通过类名访问
	//Person::func(20);
}
int static_member_func()
//int main()
{
	//copy_Construct(); // 拷贝构造函数运行
   // Deep_Shallow_Copy(); // 深拷贝与浅拷贝
	// classMember();

	test001();
	cout << "\n"<<endl;
	test002();

    //system("pause");
	return 0;
}
