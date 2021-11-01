#include <iostream>
using namespace std;
#include "quote_pointer.h"
// 在python中想要直接访问类的私有属性需要装饰器@property
/*
    # 用于直接获取私有属性 先有get动作
	@property
	def age(self):   # 函数名和变量名必须相同
		return self.__age
	# 用于直接改变私有属性 再有set动作 set依赖于get
	@age.setter
	def age(self , age):
		self.__age = age
*/
// c++期望某些函数或者类访问 类的私有属性可以使用友元 friend
/*
1.全局函数作友元
2.类作友元
3.成员函数作友元
*/
class Building1
{
	friend void goodGay(Building1* building); //该函数可以访问私有属性
public :
	Building1() // 无参构造
	{
		_Livingroom = "客厅";
		_Bedroom = "卧室";
	}
public:
	string _Livingroom; // 客厅
private:
	string _Bedroom; // 卧室

};
// 1. 全局函数作友元
void goodGay(Building1* building) // 地址传递
{ 
	// 全局函数不能访问私有属性 但是加了friend 可以访问
	cout << "好基友全局函数正在访问私有属性卧室 : " <<building->_Bedroom<< endl;
}

// 2. 类作友元
class Building2
{
	friend class Goodgay1;// 某类可以访问该类的私有属性 那么类中任何成员都可以访问该类
public:
	Building2(); //无参构造 但是不同于Building2是在类内进行构造 这里也可以类外构造
public:
	string _Livingroom; // 客厅
private:
	string _Bedroom; // 卧室
};
// <2.1>Building2 类外写构造函数 （无参构造）
Building2::Building2()
{
	_Livingroom = "客厅"; 
	_Bedroom = "卧室";

}
class Goodgay1
{
public:
	Goodgay1(); // 无参构造 : 用new构造了新的内存地址让building2指向建筑类
	void visit();
	Building2* building2; // 即Goodgay类包含了建筑类 只不过这里是地址
};
// <2.2>Goodgay 类外写构造函数 (无参构造)
Goodgay1::Goodgay1()
{
	// 创建建筑物对象 将类属性 building2 指向一个新开辟的内存地址 所以building2用指针创建
	building2 = new Building2;  // 这里的building2 和类里的属性building2是相同的
}
// <2.3> Goodgay 类外写成员函数
void Goodgay1::visit()
{
	//cout << "好基友类正在访问私有属性卧室 : " <<building2->_Livingroom << endl;
	// 也可以访问私有属性 
	cout << "好基友类正在访问私有属性卧室 : " << building2->_Bedroom << endl;
}


// 3.成员函数作友元 : 只希望类中某个函数才能访问
class Building3; // 虽然Goodgay2先于Building3定义 , 但是前者用到了后者 所以还必须先声明有一个类Building3
class Goodgay2 // Goodgay2必须在Building3之前定义 否则97行不认识这个函数
{
public:
	Goodgay2();// 无参构造 : 用new构造了新的内存地址让building3指向建筑类
	Building3* building3;
	void visit1(); // 让类中visit1函数不可以访问建筑类私有属性
	void visit2(); // 让类中visit2函数可以访问建筑类私有属性
};
class Building3
{
	//friend class Goodgay2;
	//friend void Goodgay2:: visit1();
	friend void Goodgay2::visit2();   
public:
	Building3(); //无参构造
public:
	string _Livingroom; // 客厅
private:
	string _Bedroom; // 卧室
};

// 类外构造函数
Goodgay2::Goodgay2()
{
	building3 = new Building3;
}
// 类外成员函数
void Goodgay2::visit1()
{
	cout << "好基友类的成员函数visit1正在访问公共属性 : " << building3->_Livingroom << endl;
}
void Goodgay2::visit2()
{
	cout << "好基友类的成员函数visit2正在访问私有属性 : " << building3->_Bedroom << endl;
}
// 类外构造函数
Building3::Building3()
{
	_Bedroom = "卧室";
	_Livingroom = "客厅";
}
int friend_use()
//int main()
{
	//copy_Construct(); // 拷贝构造函数运行
	// Deep_Shallow_Copy(); // 深拷贝与浅拷贝
	// classMember(); // 类作为类成员
	//static_member_func(); // 类的静态变量和静态函数
	//this_pointer(); // this 指针的使用
	
	//Building1 building1;
	//goodGay(&building1);
 //  
	//Goodgay1 goodgay1;
	//goodgay1.visit();
	
	Goodgay2 goodgay2;
	goodgay2.visit1();
	goodgay2.visit2();
	system("pause");
	return 0;
}