#include <iostream>
using namespace std;
#include "quote_pointer.h"
//conventional_polymorphism(); 传统方法和多态方法案例
//coffeedrinkMaing(); 纯虚函数和抽象类
/*
1. 多态使用时子类如果有属性在堆区, 那么父类指针在释放时无法调用到子类的析构代码
2. 解决方式 : 将父类析构函数变为虚析构或者纯虚析构
3. 纯虚析构和虚析构
	3.1 共性 : 
		3.1.1 可以解决父类指针释放子类对象的问题
		3.1.2 都要有具体的函数实现
	3.2 区别 : 纯虚析构属于抽象类无法实例化对象
    3.3 语法 : 
		3.3.1 虚析构 : virtual ~类名(){} 类内实现
		3.3.2 纯虚析构 :  virtual ~类名() = 0 ; 然后类外实现具体函数
*/
class Animal
{
public:
	Animal()
	{
		cout << "----------------Animal构造函数到此一游--------------" << endl;
	}
	// 利用虚析构可以解决父类指针释放子类对象不干净的问题
	/*virtual ~Animal()
	{
		cout << "----------------Animal析构函数到此一游--------------" << endl;
	}*/
	// 纯虚析构
	virtual ~Animal() = 0;
	virtual void speak() = 0;
};
// 纯虚析构必须要有具体的函数实现 (类内声明 类外实现)
Animal :: ~Animal()
{
	cout << "--------------Animal纯虚析构函数到此一游--------------" << endl;
}
class Cat1 : public Animal
{
public:
	string * _name;
	Cat1(string name)
	{
		cout << "----------------cat构造函数到此一游--------------" << endl;
		_name = new string(name);
	}
	~Cat1()
	{
		if (_name != NULL)
			cout << "----------------cat析构函数到此一游--------------" << endl;
		   delete _name;
		  _name = NULL;
	}
	virtual void speak()
	{
		cout << "--------------"<<*_name <<"cat-----------------" << endl;
	}
};
void test_1101()
{
	Animal* animal = new Cat1("Tom");
	animal->speak();
	delete animal;
}
int pure_xigou()
//int main()
{
	test_1101();


	return 0;
}