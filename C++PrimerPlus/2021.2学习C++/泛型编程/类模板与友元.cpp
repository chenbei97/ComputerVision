#include "_template.h"
/*
1. ȫ����ͨ��������ʵ�� �� ֱ������������Ԫ����
2. ȫ����ͨ��������ʵ�֣���ǰ�ñ�����֪��ȫ�ֺ����Ĵ���
*/

// ������� ����ʵ��
// ����д�����Ϸ������ñ�����֪���������������ڵ���ͨ����
template<class T1 ,class T2>
class Person ;
template<class T1, class T2>
void  printPerson(Person<T1, T2>p)
{
	cout << "����ʵ��������" << p._name << endl;
	cout << "����ʵ�����䣺" << p._age << endl;
}
template <class T1, class T2>
class Person
{
public:
	Person(T1 name, T2 age);
	//{
	//	this->_age = age;
	//	this->_name = name;
	//}
	// ȫ��������� ����ʵ��
	friend void showPerson(Person<T1 ,T2> p)// ���ݵ��Ǹ���ģ��
	{
			cout << "����ʵ��������" << p._name << endl;
			cout << "����ʵ�����䣺" << p._age << endl;
	}
	 // ȫ��������� ����ʵ��
	friend void printPerson<>(Person<T1, T2> p);
private:
	T1 _name;
	T2 _age;
};
// ���캯�� ����ʵ��
template<class T1 ,class T2>
Person<T1, T2>  ::Person(T1 name, T2 age)
{
	this->_age = age;
	this->_name = name;
}

void test_0013()
{
	Person<string, int> p("LNR", 180);
	showPerson(p); // ȫ���������������ʵ��
	  // ȫ���������������ʵ��
	printPerson(p);
}
int friend_template()
//int main() 
{
	//class_template_spilit();
	test_0013();
	return 0;
}