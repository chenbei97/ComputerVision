#include <iostream>
//#include <functional>
#include <string>
using namespace std;
// 定义有返回类型和参数的函数
int _chapter11_add(int, int);
int _chapter11_subtract(int, int);
// 定义无返回值无参数的函数
void _chapter11_printHello();
void _chapter11_printBye();
// 定义有参数无返回值的函数
void _chapter11_printName(string);
void _chapter11_printAge(int);
// 定义有返回值无参数的函数
double* _chapter11_return_double_p();
const char& _chapter11_return_char_r();
// 4个函数类型作为参数的5个函数
int _chapter11_add_with_subtract(int (*)(int,int),int,int);
void _chapter11_hello_bye(void(*)());
template<class T>
void _chapter11_name_age(void(*func)(T ), T x);
double* _chapter11_return_p(double*(*func)());
const char& _chapter11_return_r(const char&(*func)());
void _chapter11_function_as_parameter()
{
	// 测试有返回类型和参数的函数
	int c1 = _chapter11_add_with_subtract(_chapter11_add, 5, 6);
	int c2 = _chapter11_add_with_subtract(_chapter11_subtract, 5, 6);
	cout << "5+6 = " << c1 << "  5-6 = " << c2 << endl;

	// 测试无返回值无参数的函数
	_chapter11_hello_bye(_chapter11_printHello);
	_chapter11_hello_bye(_chapter11_printBye);

	// 测试有参数无返回值的函数
	_chapter11_name_age(_chapter11_printName, string("chenbei")); // 不用构造会显示const char*不匹配
	_chapter11_name_age(_chapter11_printAge, 25);

	// 测试有返回值无参数的函数
	double * p =_chapter11_return_p(_chapter11_return_double_p);
	cout << "now the double address is " << p << endl;
	const char c = _chapter11_return_r(_chapter11_return_char_r);
	cout << "now the char reference is " << c << endl;
}
int _chapter11_add(int x , int y)
{
	return x + y;
}
int _chapter11_subtract(int x , int y)
{
	return x - y;
}
void _chapter11_printHello()
{
	cout << "hello" << endl;
}
void _chapter11_printBye()
{
	cout << "bye" << endl;
}
void _chapter11_printName(string name)
{
	cout << "my name is " << name << endl;
}
void _chapter11_printAge(int age)
{
	cout << "my age is " << age << endl;
}
double* _chapter11_return_double_p()
{
	double* p = new double();
	cout << "new double* address is " << p << endl;
	return p;
}
const char& _chapter11_return_char_r()
{
	const char* c = new const char [5] {'a','b','c','d','e'};
	cout << "new char& address is " << &c[0] << endl; // 地址就是abcde
	return c[4];
}
int _chapter11_add_with_subtract(int (*func)(int, int),int x ,int y)
{
	return (*func)(x, y);
}
void _chapter11_hello_bye(void(*func)())
{
	(*func)();
}
template<class T>
void _chapter11_name_age(void(*func)(T), T x)
{
	(*func)(x);
}
double* _chapter11_return_p(double*(*func)())
{
	return (*func)();
}
const char& _chapter11_return_r(const char& (*func)())
{
	return (*func)();
}