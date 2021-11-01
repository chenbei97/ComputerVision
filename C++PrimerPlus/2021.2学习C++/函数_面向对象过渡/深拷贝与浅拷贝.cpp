#include <iostream>
using namespace std;
#include "quote_pointer.h"
/*
1.浅拷贝 ： 简单的赋值拷贝操作
2.深拷贝 ： 在堆区重新申请空间 进行拷贝操作
*/
class Per
{
public:
	
	Per()
	{
		cout << "<-----------默认无参构造函数----------->" << endl;
	}
	Per( int age)
	{
		_age = age;
		cout << "<-----------自定义有参构造函数(无内存申请new)----------->" << endl;
	}
	Per(int age ,int height)
	{
		_age = age;
		_height = new int(height); //给输入参数申请一个堆区内存地址
		cout << "<-----------自定义有参构造函数(有内存申请new)----------->" << endl;
	}
	~Per()
	{
		if (_height != NULL)
		{
			delete _height;
			_height = NULL;
		}
		cout << "<-----------默认析构函数----------->释放完毕" << endl;
	}
	void print1()
	{
		cout << "<-----------年龄----------->" <<_age << endl;
	}
	void print2()
	{
		cout << "<-----------年龄----------->" << _age << endl;
		cout << "<-----------身高----------->" << *_height << endl;
	}
	Per(const Per & p  ,int width) // 为了区别于深拷贝的函数 引入参数 width但是什么也不做
	{
		// 浅拷贝 Per (p1,height) (构造);Per(p1,width)(浅拷贝)(*_height释放一次) ;p2.print2(); (*_height释放两次) 运行结束后 p1的堆区被释放两次会崩溃
		cout << "<-----------默认拷贝构造函数(浅拷贝)----------->" << endl;
		_age = p._age;
		_height = p._height; // 普通拷贝(浅拷贝)没有开辟新的内存去接收
	}
	Per(const Per& p) // 传入的参数是类地址 深拷贝赋值
	{
		// Per (p1) ; Per(p1,height)(构造) ; Per(p1)(深拷贝) (用新内存接收了 *_height然后释放一次);p2.print2();(*_height释放两次)
		cout << "<-----------自定义拷贝构造函数(深拷贝)----------->" << endl;
		_age = p._age;
		//_height = p._height(); 默认的拷贝构造函数会运行这两段代码 即浅拷贝 会导致内存泄露
		_height = new int(*p._height); // 深拷贝的操作 使用了新内存去接收堆区地址
	}
private :
	int _age = 0;
	int* _height = 0; // 指向身高的地址
};
void test01()
{
	cout << "<-----------p1----------->" << endl;
	Per p1(18); //第一个有参构造 
	p1.print1();
}
void test02()
{
	cout << "\n<-----------p2----------->" << endl;
	// 注:  这里析构函数会释放两次
	Per p1(18); //第一个有参构造 
	// 注 : 使用的是默认拷贝构造 类中没有自定义新的拷贝函数
	Per p2(p1,20); // 浅拷贝 : 普通局部变量两次释放不会出现问题
	p2.print1();
}
void test03()
{
	cout << "\n<-----------p3----------->" << endl;
	Per p3(18, 160); // 第二个有参构造 : 有了堆区内存申请
	p3.print2();
}
void test04()
{
	cout << "\n<-----------p4----------->" << endl;
	 //注:  这里析构函数会释放两次
	Per p3(18, 160); // 第二个有参构造 : 有了堆区内存申请
	 /*注 : 使用的是默认拷贝构造 类中没有自定义新的拷贝函数*/
	Per p4(p3,20); // 浅拷贝 : 第一次p3已经释放了_height堆区内存 ,p4二次释放出现问题
	p4.print2();
}
void  test05()
{
	cout << "\n<-----------p5----------->" << endl;
	   // 注:  这里析构函数会释放两次
	Per p4(18, 160);
	// 注 : 使用的是自定义拷贝构造 类中有自定义新的拷贝函数
	Per p5(p4); //  深拷贝 : 自定义拷贝函数中new了新的内存 释放两次没有问题
	p5.print2();
}
int Deep_Shallow_Copy()
//int main() 
{
	 // copy_Construct(); // 拷贝构造函数运行
	
	test01();

	test02();

	test03();

	//test04(); // 解决浅拷贝重读释放内存的方案是自定义新的拷贝构造函数

	test05(); // 深拷贝

	//system("pause");
	return 0;
}

