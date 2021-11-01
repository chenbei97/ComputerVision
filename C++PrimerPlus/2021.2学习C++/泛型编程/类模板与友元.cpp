#include "_template.h"
/*
1. 全局普通函数类内实现 ： 直接类内声明友元即可
2. 全局普通函数类外实现：提前让编译器知道全局函数的存在
*/

// 输出函数 类外实现
// 必须写在最上方、且让编译器知道存在这个类和类内的普通函数
template<class T1 ,class T2>
class Person ;
template<class T1, class T2>
void  printPerson(Person<T1, T2>p)
{
	cout << "类外实现姓名：" << p._name << endl;
	cout << "类外实现年龄：" << p._age << endl;
}
template <class T1, class T2>
class Person
{
public:
	Person(T1 name, T2 age);
	//{
	//	this->_age = age;
	//	this->_name = name;
	//}
	// 全局输出函数 类内实现
	friend void showPerson(Person<T1 ,T2> p)// 传递的是个类模板
	{
			cout << "类内实现姓名：" << p._name << endl;
			cout << "类内实现年龄：" << p._age << endl;
	}
	 // 全局输出函数 类外实现
	friend void printPerson<>(Person<T1, T2> p);
private:
	T1 _name;
	T2 _age;
};
// 构造函数 类外实现
template<class T1 ,class T2>
Person<T1, T2>  ::Person(T1 name, T2 age)
{
	this->_age = age;
	this->_name = name;
}

void test_0013()
{
	Person<string, int> p("LNR", 180);
	showPerson(p); // 全局输出函数：类内实现
	  // 全局输出函数：类外实现
	printPerson(p);
}
int friend_template()
//int main() 
{
	//class_template_spilit();
	test_0013();
	return 0;
}