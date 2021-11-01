#include <iostream>
using namespace std;
//#include "quote_pointer.h"
class A1 
{
public:
	string _brand;
	A1 (string brand) // 有参构造
	{
		_brand = brand;
		cout << "<---------------A1运行到此一游--------------->" << endl;
		
	}
	~A1() { cout << "<---------------A1析构函数到此一游--------------->" << endl; }
	void print()
	{
		cout << "A1的品牌是 : " << _brand << endl;
	}
};
class A2
{
public:
	string _name; 
	A1 _A1; // !!!******作为类成员时不赋值初始化******!!!
	A2(string name, string brand) : _name(name), _A1(brand) {
		cout << "<---------------A2运行到此一游--------------->" << endl;}//有参构造

	~A2(){cout << "<---------------A2析构函数到此一游--------------->" << endl;}
	void print() { cout << "A2的名字是 : " << _name <<
		"\t手机品牌是 : "<<_A1._brand <<endl; }
};
void member_Class()
//int main() 
{
	//copy_Construct(); // 拷贝构造函数运行
    // Deep_Shallow_Copy(); // 深拷贝与浅拷贝
	
	//A1 _a1; 有参构造会覆盖无参构造必须赋值
	//A1 _a1("oppo");// 作为实例对象要初始化---->23行代码
	//_a1.print();

	//A2 _a2; 有参构造会覆盖无参构造必须赋值
	A2 _a2("chenbei","vivo"); 
	_a2.print(); // A2先析构 然后A1析构 实例化先有A1后有A2  析构则符合先进后出原则
	
	/*
	输出 :  
	<---------------A1运行到此一游--------------->
	<---------------A2运行到此一游--------------->
	A2的名字是 : chenbei    手机品牌是 : vivo
	请按任意键继续. . .
	<---------------A2析构函数到此一游--------------->
	<---------------A1析构函数到此一游--------------->
	*/
	//system("pause");
	//return 0;
}