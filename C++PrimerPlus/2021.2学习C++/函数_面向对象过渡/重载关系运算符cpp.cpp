#include <iostream>
using namespace std;
#include "quote_pointer.h"
//copy_Construct(); // �������캯������
//Deep_Shallow_Copy(); // �����ǳ����
// classMember(); // ����Ϊ���Ա
//static_member_func(); // ��ľ�̬�����;�̬����
//this_pointer(); // this ָ���ʹ��
//friend_use(); // ��Ԫ��ʹ��
// operatorOverload(); // �Ӽ����������
//leftmove(); // �������������
//increment_Operator();  //  �������������
//assignment_Operator(); // ��ֵ���������
class Person
{
public:
	string _name;
	int _age;
	Person() {};
	Person(string name, int age)
	{
		_age = age;
		_name = name;
	}
	~Person() { cout << "-------������������һ��--------" << endl; }
	bool operator==(Person& p)
	{
		if (this->_age == p._age && this->_name == p._name)
		{
			return true;
		}
		return false;
	}
};
void test_0008()
{
	Person p1("Tom", 19);

	Person p2("Tom", 18);

	if (p1 == p2) // ��Ҫ���غ�Ⱥ�"=="
	{cout << "p1��p2���"<<endl;}
	else { cout << "p1��p2�����" << endl; }
}
int relational_Operator()
//int main()
{
	// �������Զ�������ݽ��й�ϵ����
	test_0008();
    /*
	p1��p2�����
	-------������������һ��--------
	-------������������һ��--------
	*/
	return 0;
}