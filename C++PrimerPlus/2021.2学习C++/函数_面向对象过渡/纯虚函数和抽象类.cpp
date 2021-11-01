#include <iostream>
using namespace std;
#include "quote_pointer.h"
//conventional_polymorphism();
// 1.纯虚函数和抽象类 : 父类的虚函数实现可能毫无意义可以写成纯虚函数
// 语法 :  virtual 返回值类型 函数名 (参数列表) = 0 ;
// 2.当类中有纯虚函数 这个类成为抽象类
// 2.1 无法实例化对象
// 2.2 子类必须重写抽象类中的纯虚函数 否则也属于抽象类
class Base
{
public:
	virtual void func() = 0;
};
class Son : public  Base
{
public:
	virtual void func() 
	{
		cout << "-----子类func函数调用---------->" << endl;
	}
};
void Pure_Virtual_Function()
{
	// 1.实例调用
	Son son;
	son.func();
	// 2.多态调用
	Base* base = new Son;
	base->func();
	delete base;
}
/*
案例 : 制作饮品 : 煮水 - 冲泡 - 倒入杯中 - 加入辅料
利用多态技术 提供抽象制作饮品基类 提供子类制作咖啡和茶叶
1.煮水2.冲泡咖啡3.倒入杯中4.加糖和牛奶 
1.煮水2.冲泡茶叶3.倒入杯中4.加枸杞
*/
class baseMakingdrink
{
public:
	virtual void Boil() = 0;
	virtual void Brew() = 0;
	virtual void Pour() = 0;
	virtual void Add() = 0;
	void  Makingdrink()
	{
		Boil(); Brew();Pour();Add();
	}
};
class Makingcoffee : public baseMakingdrink
{
public:
	virtual  void Boil(){cout << "咖啡煮水" << endl;}
	virtual  void Brew() { cout << "咖啡冲泡" << endl; }
	virtual  void Pour() { cout << "咖啡倒杯" << endl; }
	virtual  void Add() { cout << "咖啡加糖" << endl; }
	virtual string boilingmethod(string name) { return name; }
};
class Makingtea : public baseMakingdrink
{
public:
	virtual  void Boil() { cout << "茶叶煮水" << endl; }
	virtual  void Brew() { cout << "茶叶冲泡" << endl; }
	virtual  void Pour() { cout << "茶叶倒杯" << endl; }
	virtual  void Add() { cout << "茶叶加糖" << endl; }
};
void doWorking( baseMakingdrink * abs) 
{
	// 制作饮品的函数只在基类有
	// 所以需要一个基类的指针指向实例的咖啡和茶
	abs->Makingdrink();
	//delete abs;
}
void testMaking()
{
	Makingcoffee coffe;
	doWorking(&coffe);
	doWorking(new Makingtea);
}
/*
对于制作咖啡 的某个函数如煮水可以继续拓展 
如用不同的方法煮水 比如用电、用煤、用天然气煮水
同时在制作咖啡中留出一个函数展示煮水方式boilingMethod()用来提供名字
咖啡煮水类构造函数用boilingMethod初始化属性Method 送入Boil函数
Boil不可重载 否则与父类是不同的
*/
class coffeBoiling : public Makingcoffee
{
public: 
	string Method;
	coffeBoiling(string method)
	{
		Method = boilingmethod(method);
	}
	virtual void Boil() //string method 不可重载
	{
		cout << "咖啡用" <<Method <<"煮水" << endl;
	}
};
void doBoiling(Makingcoffee * coffee)
{
	coffee->Boil();
}
void testBoiling()
{
	doBoiling(new coffeBoiling("天然气"));
}
int coffeedrinkMaing()
//int main() 
{
	Pure_Virtual_Function();
	testMaking();
	testBoiling();
	return 0;
}