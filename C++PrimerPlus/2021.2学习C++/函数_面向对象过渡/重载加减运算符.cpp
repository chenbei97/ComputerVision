#include <iostream>
using namespace std;
#include "quote_pointer.h"
// ��operator�����е�������ض��� �����µĹ��� �������Զ����������ͽ�������
// 1.���ó�Ա���� ��������Ž�������
class Person
{
public:
	int _a;
	int _b;
	Person operator+ (Person& p) // ��Ա����
	{
		Person temp;
		temp._a = this->_a + p._a;
		temp._b = this->_b + p._b;
		return temp;
	}
};

void test_0001()
{
	Person p1;
	p1._a = 10;
	p1._b = 20;
	Person p2;
	p2._a = 10;
	p2._b = 20;
	Person p3 = p1.operator+(p2);
	Person p4 = p1 +  p2; // ���ʾ�����һ�д���
	cout << "��Ա�������� p3��a = " << p3._a << endl;
	cout <<"��Ա�������� p4��b = "<< p4._b << endl;
}
// 2.ȫ�ֺ�������
Person operator + (Person& p1, Person& p2)
{
	Person temp;
	temp._a = p1._a + p2._a;
	temp._b = p1._b + p2._b;
	return temp;
}
void test_0002()
{
	Person p1;
	p1._a = 100;
	p1._b = 200;
	Person p2;
	p2._a = 100;
	p2._b = 200;
	Person p3 = operator+ (p1, p2); // ���ʵ���
	//Person p4 = p1 + p2; // �ض����� ��֪��������һ�еĻ���28�д����
	cout << "\nȫ�ֺ������� p3��a = " << p3._a << endl;
	//cout << "ȫ�ֺ������� p4��b = " << p4._b << endl;
}
int operatorOverload()
//int main()
{
	//copy_Construct(); // �������캯������
	// Deep_Shallow_Copy(); // �����ǳ����
	// classMember(); // ����Ϊ���Ա
	//static_member_func(); // ��ľ�̬�����;�̬����
	//this_pointer(); // this ָ���ʹ��
	//friend_use(); // ��Ԫ��ʹ��


	test_0001();
	test_0002();

	system("pause");
	return 0;	
}