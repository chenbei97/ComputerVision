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
// relational_Operator(); // ��ϵ���������
//int functor(); �º���

// ����������������� Ҳ����'()'
class MyPrint
{
public:
	// ���غ������������'()'
	void operator()(string test)
	{
		cout << test << endl;
	}
};
void test_0009() 
{
	MyPrint myprint;
	myprint("hello"); // ʵ�����������һ������
}
class MyAdd
{
public:
	int operator()(int a, int b)
	{
		return a + b;
	}
};
void test_0010()
{
	MyAdd myadd;
	cout <<myadd(1, 2)<<endl;
	// ������������
	cout << MyAdd()(100, 100) << endl; //������python���෽��
}
int functor()
//int main() 

{
	// �������������()Ҳ�������� ���غ�ķ�ʽ�������ĵ��� ��˳�Ϊ�º���
	test_0009();
	test_0010();
	return 0; 
}