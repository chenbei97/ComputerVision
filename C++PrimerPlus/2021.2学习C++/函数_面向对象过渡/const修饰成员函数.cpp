#include <iostream>
using namespace std;
#include "quote_pointer.h"
/*
* ��Ա���Բ����޸� : ���ⲿ�޶�Ϊ��������ڲ��޶�������
1.��Ա������cosnt���֮Ϊ������(�ڲ��޶�)
2.�������ڲ����޸ĳ�Ա���� ָ���ֵ�������޸�
3.��Ա���Լ�mutableʱ����������Ȼ�����޸�
4.��������ǰ ��const ����Ϊ������(�ⲿ�޶�)
5.������ֻ�ܵ��ó�����
*/
class Person
{
public:
	int  _age;
	mutable int _id; //��������
	// ��ͨ����
	void showPerson1() 
	{
		//thisָ����ָ�볣�� ָ�����޸�
		// this = NULL;
		_age = 100;  // �����Ը�ֵ
	}
	// ������
	void showPerson2() const 
	{
		// ����ָ�����޸� , ֵҲ�����޸�
		// ��Ϊ����ָ�볣�� ��������ָ��
		//_age = 100;  
		_id = 100; // mutable������Ȼ�ܹ��޸�
	}
};
void test110()
{
	Person p;
	p.showPerson1(); 
	p.showPerson2();
}
void test111()
{
	const Person p; //������ 
	// p._age = 100; // �����������޸���ͨ����
	p._id = 100; // ����������޸�mutable����
	p.showPerson2();  // ���ǿɷ��ʳ����� ���ܷ���showPerson1()
}
int const_classfunc()
//int main() 
{
	//copy_Construct(); // �������캯������
	// Deep_Shallow_Copy(); // �����ǳ����
	// classMember(); // ����Ϊ���Ա
	//static_member_func(); // ��ľ�̬�����;�̬����
	//this_pointer();

	system("pause");
	return 0;
}