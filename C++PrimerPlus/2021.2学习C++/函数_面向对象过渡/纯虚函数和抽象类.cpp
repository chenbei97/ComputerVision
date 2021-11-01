#include <iostream>
using namespace std;
#include "quote_pointer.h"
//conventional_polymorphism();
// 1.���麯���ͳ����� : ������麯��ʵ�ֿ��ܺ����������д�ɴ��麯��
// �﷨ :  virtual ����ֵ���� ������ (�����б�) = 0 ;
// 2.�������д��麯�� ������Ϊ������
// 2.1 �޷�ʵ��������
// 2.2 ���������д�������еĴ��麯�� ����Ҳ���ڳ�����
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
		cout << "-----����func��������---------->" << endl;
	}
};
void Pure_Virtual_Function()
{
	// 1.ʵ������
	Son son;
	son.func();
	// 2.��̬����
	Base* base = new Son;
	base->func();
	delete base;
}
/*
���� : ������Ʒ : ��ˮ - ���� - ���뱭�� - ���븨��
���ö�̬���� �ṩ����������Ʒ���� �ṩ�����������ȺͲ�Ҷ
1.��ˮ2.���ݿ���3.���뱭��4.���Ǻ�ţ�� 
1.��ˮ2.���ݲ�Ҷ3.���뱭��4.�����
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
	virtual  void Boil(){cout << "������ˮ" << endl;}
	virtual  void Brew() { cout << "���ȳ���" << endl; }
	virtual  void Pour() { cout << "���ȵ���" << endl; }
	virtual  void Add() { cout << "���ȼ���" << endl; }
	virtual string boilingmethod(string name) { return name; }
};
class Makingtea : public baseMakingdrink
{
public:
	virtual  void Boil() { cout << "��Ҷ��ˮ" << endl; }
	virtual  void Brew() { cout << "��Ҷ����" << endl; }
	virtual  void Pour() { cout << "��Ҷ����" << endl; }
	virtual  void Add() { cout << "��Ҷ����" << endl; }
};
void doWorking( baseMakingdrink * abs) 
{
	// ������Ʒ�ĺ���ֻ�ڻ�����
	// ������Ҫһ�������ָ��ָ��ʵ���Ŀ��ȺͲ�
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
������������ ��ĳ����������ˮ���Լ�����չ 
���ò�ͬ�ķ�����ˮ �����õ硢��ú������Ȼ����ˮ
ͬʱ����������������һ������չʾ��ˮ��ʽboilingMethod()�����ṩ����
������ˮ�๹�캯����boilingMethod��ʼ������Method ����Boil����
Boil�������� �����븸���ǲ�ͬ��
*/
class coffeBoiling : public Makingcoffee
{
public: 
	string Method;
	coffeBoiling(string method)
	{
		Method = boilingmethod(method);
	}
	virtual void Boil() //string method ��������
	{
		cout << "������" <<Method <<"��ˮ" << endl;
	}
};
void doBoiling(Makingcoffee * coffee)
{
	coffee->Boil();
}
void testBoiling()
{
	doBoiling(new coffeBoiling("��Ȼ��"));
}
int coffeedrinkMaing()
//int main() 
{
	Pure_Virtual_Function();
	testMaking();
	testBoiling();
	return 0;
}