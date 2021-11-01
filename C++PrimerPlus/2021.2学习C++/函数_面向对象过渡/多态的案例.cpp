#include <iostream>
using namespace std;
#include "quote_pointer.h"
//class_Inheritance();
/*利用普通写法和堕胎技术实现两个操作数进行运算的计算器类*/
// 1. 普通写法
class Calculator
{
public:
	int _num1;
	int _num2;
	int getResult(string oper)
	{
		if (oper == "+")
		{
			cout << "两个数相加为------------>" << _num1 + _num2<< endl;
			return _num1 + _num2;
			
		}
		else if (oper == "-")
		{
			cout << "两个数相减为------------>" << _num1 - _num2 << endl;
			return _num1 - _num2;
		}
		else if (oper == "*")
		{
			cout << "两个数相乘为------------>" << _num1 * _num2 << endl;
			return _num1 * _num2;
		}
		// 如果需要扩展功能 在这里会导致反复修改getResult函数
		// 提倡开闭原则 : 对扩展进行开发 对修改进行关闭
	}
};
void conventional_Writing()
{
	Calculator calculator;
	calculator._num1 = 3;
	calculator._num2 = 5;
	calculator.getResult("*");
}
// 2. 多态写法
// 结构清晰(各种运算是分开的)  
// 可读性强
// 易拓展和可维护性高
// 2.1 实现计算器的抽象类 什么功能都没有
class baseCalculator
{
public:
	int _num1;
	int _num2;
	virtual int getResult()
	{
		return 0;
	}
};
// 2,2 加法类
class addCalculator : public baseCalculator
{
public:
	int getResult() // 相当于重写了父类
	{
		cout << "两个数相加为------------>" << _num1 + _num2 << endl;
		return _num1 + _num2;
	}
};
void polymorphism_Writing()
{
	baseCalculator * add = new addCalculator	; //把父类指针指向子类对象 发生了虚函数替换
	add->_num1 = 100;
	add->_num2 = 200;
	add->getResult(); // 执行的是子类的函数
	delete add;
}
int conventional_polymorphism()
//int main()
{
	// 1. 常规写法
	conventional_Writing();
	// 2. 多态写法
	polymorphism_Writing();

	
	return 0; 
}