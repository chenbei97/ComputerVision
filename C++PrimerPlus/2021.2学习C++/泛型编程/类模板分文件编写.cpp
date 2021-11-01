#include "_template.h"
// #include "person.h"
#include "person.cpp" // 第一种解决方案
// 类模板成员函数创建时机在调用阶段 导致文件编写时链接不到
// 解决方法 ： 1、直接包含cpp源文件 2、将声明和实现写到同一个文件更改后缀名为hpp
// hpp 是约定的名称 不强制 hpp= h+cpp

//template <class T1, class T2>
//class Person
//{
//public:
//	T1 _name;
//	T2 _age;
//	Person(T1 name, T2 age);
//	void showPerson();
//};
//template<class T1 ,class T2>
//Person<T1, T2>  ::Person(T1 name, T2 age)
//{
//	this->_age = age;
//	this->_name = name;
//}
//template<class T1, class T2>
//void Person<T1, T2> ::showPerson()
//{
//	cout << "姓名：" << _name << endl;
//	cout << "年龄：" << _age << endl;
//}
void test_0011()
{
	Person<string, int> p("chenbei",100);
	p.showPerson();
}
int class_template_spilit()
//int main() 
{
	//func_template();
	//class_template();
	test_0011();
	return 0;
}