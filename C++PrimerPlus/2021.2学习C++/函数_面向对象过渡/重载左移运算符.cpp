#include <iostream>
using namespace std;
#include "quote_pointer.h"
/*
������������� ����������Զ�����������
1.�������ó�Ա�������� ��Ϊ<< �ǵ�Ŀ����� cout << a 
p.operator<<(p) �ȼ���p1 cout << p2������Ҫ��  p.operator<<(cout) ----->�ȼ��� p << cout
2. ��������ȫ�ֺ�������
*/
class Person
{
	friend ostream& operator<< (ostream& cout, Person& p);
	friend void test_0003();
private:
	int _a;
	int _b;
};
ostream & operator<< (ostream &cout, Person &p)  
 //operator << (cout ,p) ��Ϊcout << p 
// cout ��Ϊ out Ҳ�ǿ��Ե� ��Ϊ�ǵ�ַ����
{
	cout << "\n_a = " << p._a << "_b = " << p._b;
	return cout; // ������ʽ�������
}
void test_0003()
{
	Person p;
	
	p._a = 10;
	p._b = 20;
	cout << p._a;
	cout << p << "\thello_world" <<endl; // û��void operator<< (ostream &cout, Person &p)  �����ǲ���ֱ�������
	
}
int leftmove()
//int main()
{
	//copy_Construct(); // �������캯������
	// Deep_Shallow_Copy(); // �����ǳ����
	// classMember(); // ����Ϊ���Ա
	//static_member_func(); // ��ľ�̬�����;�̬����
	//this_pointer(); // this ָ���ʹ��
	//friend_use(); // ��Ԫ��ʹ��
	// operatorOverload(); // ���������

	test_0003();

	//system("pause");
	return 0;
}