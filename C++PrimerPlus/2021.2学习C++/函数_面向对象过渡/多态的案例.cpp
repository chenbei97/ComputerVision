#include <iostream>
using namespace std;
#include "quote_pointer.h"
//class_Inheritance();
/*������ͨд���Ͷ�̥����ʵ��������������������ļ�������*/
// 1. ��ͨд��
class Calculator
{
public:
	int _num1;
	int _num2;
	int getResult(string oper)
	{
		if (oper == "+")
		{
			cout << "���������Ϊ------------>" << _num1 + _num2<< endl;
			return _num1 + _num2;
			
		}
		else if (oper == "-")
		{
			cout << "���������Ϊ------------>" << _num1 - _num2 << endl;
			return _num1 - _num2;
		}
		else if (oper == "*")
		{
			cout << "���������Ϊ------------>" << _num1 * _num2 << endl;
			return _num1 * _num2;
		}
		// �����Ҫ��չ���� ������ᵼ�·����޸�getResult����
		// �ᳫ����ԭ�� : ����չ���п��� ���޸Ľ��йر�
	}
};
void conventional_Writing()
{
	Calculator calculator;
	calculator._num1 = 3;
	calculator._num2 = 5;
	calculator.getResult("*");
}
// 2. ��̬д��
// �ṹ����(���������Ƿֿ���)  
// �ɶ���ǿ
// ����չ�Ϳ�ά���Ը�
// 2.1 ʵ�ּ������ĳ����� ʲô���ܶ�û��
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
// 2,2 �ӷ���
class addCalculator : public baseCalculator
{
public:
	int getResult() // �൱����д�˸���
	{
		cout << "���������Ϊ------------>" << _num1 + _num2 << endl;
		return _num1 + _num2;
	}
};
void polymorphism_Writing()
{
	baseCalculator * add = new addCalculator	; //�Ѹ���ָ��ָ��������� �������麯���滻
	add->_num1 = 100;
	add->_num2 = 200;
	add->getResult(); // ִ�е�������ĺ���
	delete add;
}
int conventional_polymorphism()
//int main()
{
	// 1. ����д��
	conventional_Writing();
	// 2. ��̬д��
	polymorphism_Writing();

	
	return 0; 
}