#include "_template.h"
// #include "person.h"
#include "person.cpp" // ��һ�ֽ������
// ��ģ���Ա��������ʱ���ڵ��ý׶� �����ļ���дʱ���Ӳ���
// ������� �� 1��ֱ�Ӱ���cppԴ�ļ� 2����������ʵ��д��ͬһ���ļ����ĺ�׺��Ϊhpp
// hpp ��Լ�������� ��ǿ�� hpp= h+cpp

//template <class T1, class T2>
//class Person
//{
//public:
//	T1 _name;
//	T2 _age;
//	Person(T1 name, T2 age);
//	void showPerson();
//};
//template<class T1 ,class T2>
//Person<T1, T2>  ::Person(T1 name, T2 age)
//{
//	this->_age = age;
//	this->_name = name;
//}
//template<class T1, class T2>
//void Person<T1, T2> ::showPerson()
//{
//	cout << "������" << _name << endl;
//	cout << "���䣺" << _age << endl;
//}
void test_0011()
{
	Person<string, int> p("chenbei",100);
	p.showPerson();
}
int class_template_spilit()
//int main() 
{
	//func_template();
	//class_template();
	test_0011();
	return 0;
}