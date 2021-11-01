#include <iostream>
using namespace std;
#include "quote_pointer.h"
// �Ǿ�̬����ռ���ֽ� ����������������� ��ռ���ֽ�
// ���ھ�̬�����;�̬���� �������������û��ϵ�����Ǳ������Ǿ�̬�Ĺ���һ��
// �Ǿ�̬���� ��������� ��ͬ���󶼷�����һ�ݷǾ�̬�������ڴ�ռ� ���Բ�Ӱ��
// ���Ǿ�̬����Ҳ����������� �漰��������ֲ�ͬ���������һ�ݺ��������⣬����thisָ��
class Person1{};
void test010()
{
	Person1 p;
	// �ն���ռ���ڴ�1���ӽ� ��Ϊ�����ֿն���ռ�ڴ��λ��
	cout << "size of p = " << sizeof(p) << endl;
}
class Person2
{
	int _age; //�Ǿ�̬���� ������Ķ�����

	void func1() {} // �Ǿ�̬����  �������������

	static int _id; // ��̬����  �������������

	static void func2() {} // ��̬����  Ҳ�������������
};
void test011()
{
	Person2 p;
	// �ǿն���Ǿ�̬ռ���ڴ�4���ӽ�  ������ռ���ӽ�
	cout << "size of p = " << sizeof(p) << endl;
}
// this ָ��ָ�򱻵��õĳ�Ա���������Ķ��� ����Ҫ����ֱ��ʹ��
// ����˵Person p1,p2; p1.func() ;p2.func(); 
//*****ע*****----------> �βκͳ�Ա����ͬ��ʱ������thisָ������(������Ƴ�ͻ)
//*****ע*****----------> ��ķǾ�̬��Ա�����з��ض�����,����ʹ�� return *this
class Person3
{
public:
	//1��������ͻ ����ȡ��ͬ���ֽ��
	//Person3(int  age) { _age = age; }
	//int _age;
	// 2��Ҳ����ʹ��this ���
	//ָ��ָ��     �����õĳ�Ա����Person(int age)  �����Ķ���p1
	Person3(int  age) { this->age = age; }//�ȼ���p1->age = age ;
	int age;
	//3.���ض�������*this
	void PersonAddAge(Person3& p)
	{
		this->age += p.age;
	}
	Person3& _PersonAddAge(Person3& p)
		//���ص��õĶ����� ���������Լ������÷��ر���
	{
		this->age += p.age; return *this;
	}

};
void test012()
{
	Person3 p1(18);
	//cout << "p1������Ϊ ��" << p1._age << endl;
	cout << "p1������Ϊ ��" << p1.age << endl;
}
void test013()
{
	//3.���ض�������*this
	Person3 p2(10);

	Person3 p3(18);
	p2.PersonAddAge(p3); //p2���������������� thisҲ�����p2
	cout << "p2������Ϊ ��" << p2.age << endl;
	p3.PersonAddAge(p2);
	cout << "p3������Ϊ ��" << p3.age << endl;

	// ����PersonAddAge�����ǲ�������ʽ�ĵ����Լ�
	// _PersonAddAge��������
	p2._PersonAddAge(p2)._PersonAddAge(p3)._PersonAddAge(p2);
	// �ȼ��������������õĴ��� p2=28 p3=46
	//p2._PersonAddAge(p2);
	//// p2 =28+28 = 56; p3=46;
	//cout << "��һ����ʽ���ú�p2������Ϊ ��" << p2.age << endl;
	//p2._PersonAddAge(p3);
	//// p2 = 56+46= 102 ;  p3=46
	//cout << "�ڶ�����ʽ���ú�p2������Ϊ ��" << p2.age << endl;
	//// p2 =102 +102=204 ;p3=46
	//p2._PersonAddAge(p2);
	cout << "��������ʽ���ú�p2������Ϊ ��" << p2.age << endl;
}
// ��ָ����Է��ʳ�Ա���� ������Ҫע����û���õ�thisָ�� 
// ����õ���Ҫ�жϱ�֤����Ľ�׳��
class Person4
{
public:
	int _age;
	void showClassName() { cout << "this is a Person class" << endl; }
	void showPersonAge()
	{ 
		if (this == NULL) // ��߽�׳��
		{
			return;
		}
		//cout << "age = " << this->_age <<endl;
		cout << "age = " << _age << endl; //��ʹ����this ������Ĭ���Ǽӵ�
	}
};
void test014()
{
	Person4* p = NULL;
	p->showClassName(); // ��ָ����Է��ʳ�Ա����  this is a Person class
	p->showPersonAge(); // ���ǿ�ָ�뵽102�д���ʱ�޷����ʳ�Ա����
}
int this_pointer()
//int main() 
{
	//copy_Construct(); // �������캯������
   // Deep_Shallow_Copy(); // �����ǳ����
	// classMember(); // ����Ϊ���Ա
	//static_member_func(); // ��ľ�̬�����;�̬����

	test010();
	test011();

	test012();
	test013();

	test014();
	//system("pause");
	return 0;
}