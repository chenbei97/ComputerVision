#include <iostream>
using namespace std;
#include "quote_pointer.h"
// ������������� ++ �Զ����Լ�����������
class myInteger
{
	// friend void test_0004();
	friend ostream& operator << (ostream& cout, myInteger myint);
public:
	myInteger()
	{
		_num = 10;
	}
	// 1.����ǰ��++�����
	myInteger&  operator++() // myInteger operator++()
	{
		// �������� ��Ϊ��һֱ��һ�����ݽ��е���
		// ������˵a=0 ; |  ++(++a) =2 ;a =2 ;
		// �������������  ++(++myint) = 2 ; ���� myint =1 ;
		// ���������õ�һ���++myint �ͱ��һ���µı���������ԭ���� 
		// ��ʱ�������µ�++����ı�ԭ����myint ��ȻΪ1
		_num++;
		return  *this;  // ��������ĵ�ַ
	}
	// ���غ���++�����
	myInteger operator++(int) //int��������ռλ����ǰ�úͺ���
	{
	      // �ȼ�¼��ʱ���
		myInteger temp = *this;
		_num++;
		return temp; // temp�Ǿֲ����� ֻ�ܷ���ֵ
	}
private : 
	int _num; 
};
// ����<<�����
ostream & operator << (ostream& cout, myInteger  myint) 
{
	cout << myint._num; // �����ķ���ֵ���
	return cout;
}
void test_0004()
{
	myInteger  myint; // �������������� ��Ϊ����ֵ�����˽������
	cout << ++(++myint)<< endl; // ǰ�������������ʽ���� ��Ϊ���Է��ص�ַ
	cout << myint << endl;
}
void test_0005()
{
	myInteger  myint;
	cout << ++(myint++) << endl; // ���õ�����������ʽ���� ���ص�ֵ
	cout << myint << endl;
}
int increment_Operator()
// int main()
{
	//copy_Construct(); // �������캯������
	// Deep_Shallow_Copy(); // �����ǳ����
	// classMember(); // ����Ϊ���Ա
	//static_member_func(); // ��ľ�̬�����;�̬����
	//this_pointer(); // this ָ���ʹ��
	//friend_use(); // ��Ԫ��ʹ��
	// operatorOverload(); // ���������
	//leftmove(); // �������������

	test_0004();
	test_0005();

	return 0;
}