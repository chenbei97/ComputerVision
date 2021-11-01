#include <iostream>
using namespace std;
#include "quote_pointer.h"
//conventional_polymorphism(); ��ͳ�����Ͷ�̬��������
//coffeedrinkMaing(); ���麯���ͳ�����
/*
1. ��̬ʹ��ʱ��������������ڶ���, ��ô����ָ�����ͷ�ʱ�޷����õ��������������
2. �����ʽ : ����������������Ϊ���������ߴ�������
3. ����������������
	3.1 ���� : 
		3.1.1 ���Խ������ָ���ͷ�������������
		3.1.2 ��Ҫ�о���ĺ���ʵ��
	3.2 ���� : �����������ڳ������޷�ʵ��������
    3.3 �﷨ : 
		3.3.1 ������ : virtual ~����(){} ����ʵ��
		3.3.2 �������� :  virtual ~����() = 0 ; Ȼ������ʵ�־��庯��
*/
class Animal
{
public:
	Animal()
	{
		cout << "----------------Animal���캯������һ��--------------" << endl;
	}
	// �������������Խ������ָ���ͷ�������󲻸ɾ�������
	/*virtual ~Animal()
	{
		cout << "----------------Animal������������һ��--------------" << endl;
	}*/
	// ��������
	virtual ~Animal() = 0;
	virtual void speak() = 0;
};
// ������������Ҫ�о���ĺ���ʵ�� (�������� ����ʵ��)
Animal :: ~Animal()
{
	cout << "--------------Animal����������������һ��--------------" << endl;
}
class Cat1 : public Animal
{
public:
	string * _name;
	Cat1(string name)
	{
		cout << "----------------cat���캯������һ��--------------" << endl;
		_name = new string(name);
	}
	~Cat1()
	{
		if (_name != NULL)
			cout << "----------------cat������������һ��--------------" << endl;
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