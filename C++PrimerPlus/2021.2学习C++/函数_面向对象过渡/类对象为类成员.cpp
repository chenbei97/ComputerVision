#include <iostream>
using namespace std;
//#include "quote_pointer.h"
class A1 
{
public:
	string _brand;
	A1 (string brand) // �вι���
	{
		_brand = brand;
		cout << "<---------------A1���е���һ��--------------->" << endl;
		
	}
	~A1() { cout << "<---------------A1������������һ��--------------->" << endl; }
	void print()
	{
		cout << "A1��Ʒ���� : " << _brand << endl;
	}
};
class A2
{
public:
	string _name; 
	A1 _A1; // !!!******��Ϊ���Աʱ����ֵ��ʼ��******!!!
	A2(string name, string brand) : _name(name), _A1(brand) {
		cout << "<---------------A2���е���һ��--------------->" << endl;}//�вι���

	~A2(){cout << "<---------------A2������������һ��--------------->" << endl;}
	void print() { cout << "A2�������� : " << _name <<
		"\t�ֻ�Ʒ���� : "<<_A1._brand <<endl; }
};
void member_Class()
//int main() 
{
	//copy_Construct(); // �������캯������
    // Deep_Shallow_Copy(); // �����ǳ����
	
	//A1 _a1; �вι���Ḳ���޲ι�����븳ֵ
	//A1 _a1("oppo");// ��Ϊʵ������Ҫ��ʼ��---->23�д���
	//_a1.print();

	//A2 _a2; �вι���Ḳ���޲ι�����븳ֵ
	A2 _a2("chenbei","vivo"); 
	_a2.print(); // A2������ Ȼ��A1���� ʵ��������A1����A2  ����������Ƚ����ԭ��
	
	/*
	��� :  
	<---------------A1���е���һ��--------------->
	<---------------A2���е���һ��--------------->
	A2�������� : chenbei    �ֻ�Ʒ���� : vivo
	�밴���������. . .
	<---------------A2������������һ��--------------->
	<---------------A1������������һ��--------------->
	*/
	//system("pause");
	//return 0;
}