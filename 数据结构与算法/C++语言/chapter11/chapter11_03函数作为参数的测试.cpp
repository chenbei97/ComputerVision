#include <iostream>
//#include <functional>
#include <string>
using namespace std;
// �����з������ͺͲ����ĺ���
int _chapter11_add(int, int);
int _chapter11_subtract(int, int);
// �����޷���ֵ�޲����ĺ���
void _chapter11_printHello();
void _chapter11_printBye();
// �����в����޷���ֵ�ĺ���
void _chapter11_printName(string);
void _chapter11_printAge(int);
// �����з���ֵ�޲����ĺ���
double* _chapter11_return_double_p();
const char& _chapter11_return_char_r();
// 4������������Ϊ������5������
int _chapter11_add_with_subtract(int (*)(int,int),int,int);
void _chapter11_hello_bye(void(*)());
template<class T>
void _chapter11_name_age(void(*func)(T ), T x);
double* _chapter11_return_p(double*(*func)());
const char& _chapter11_return_r(const char&(*func)());
void _chapter11_function_as_parameter()
{
	// �����з������ͺͲ����ĺ���
	int c1 = _chapter11_add_with_subtract(_chapter11_add, 5, 6);
	int c2 = _chapter11_add_with_subtract(_chapter11_subtract, 5, 6);
	cout << "5+6 = " << c1 << "  5-6 = " << c2 << endl;

	// �����޷���ֵ�޲����ĺ���
	_chapter11_hello_bye(_chapter11_printHello);
	_chapter11_hello_bye(_chapter11_printBye);

	// �����в����޷���ֵ�ĺ���
	_chapter11_name_age(_chapter11_printName, string("chenbei")); // ���ù������ʾconst char*��ƥ��
	_chapter11_name_age(_chapter11_printAge, 25);

	// �����з���ֵ�޲����ĺ���
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
	cout << "new char& address is " << &c[0] << endl; // ��ַ����abcde
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