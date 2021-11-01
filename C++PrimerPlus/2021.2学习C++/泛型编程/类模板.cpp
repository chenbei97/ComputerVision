#include <iostream>
using namespace std;
#include "_template.h"
/*
1. ��ģ�����ã� ����ͨ���࣬���г�Ա���������Ͷ���ָ������һ���������ʹ���
2. �﷨�� template<typename T> ��
3. ��ģ��ͺ���ģ�������
	3.1 ��ģ��û���Զ��Ƶ�����
	3.2 ��ģ������б������Ĭ�ϲ���
4. ��ģ���Ա��������ʱ��
	��ͨ���Ա����һ��ʼ�Ϳ��Դ��� ��ģ���Ա�����ڵ���ʱ�Ŵ���
5. ��ģ����Ϊ�������� �� ��ģ��ʵ�����Ķ��� �������εķ�ʽ
	5.1 ָ����������� - ֱ����ʾ�������������(��� �������Ա�����template����ģ�����)
	void printPer2(Per<int,string>& p){};
	5.2 ����ģ�廯 - ������Ĳ�����Ϊģ����д���
	template <class T1 , class T2>
	void printPer2(Per<T1,T2>& p){};
	5.3 ������ģ�廯 - ������������� ģ�廯���д���
	template <class T>
	void printPer3(T &p){};
6. ��ģ����̳�
	6.1 ����̳еĸ�����һ����ģ��ʱ ��������ʱҪָ������T������
	class son1 : public base<int> // base����ָ��Ϊint����
	6.2 ��ָ�� �������޷�����������ڴ�
	6.3 �������ָ������T�����ͣ�����Ҳ��Ҫ��Ϊ��ģ��
	template <class T1, class T2>
	class son2 : public base<T1> // base����ָ��ΪT1�������ڶ������Ը�������� T2��������ģ���Լ�����
7. ��ģ���Ա��������ʵ�֣�
	 7.1 ��ģ��Ĺ��캯��������ʵ��
	 Car<T1,T2>::Car(T1 name, T2 age){};
	 7.2 ��ģ�����ͨ��Ա����������ʵ��
	 void Car<T1,T2>::showPerson(){};
*/
template<class NameType , class AgeType = int>//Ĭ�ϲ���
class Person
{
public:
	Person(NameType name, AgeType age )
	{
		this->_age = age;
		this->_name = name;
	}
	NameType _name;
	AgeType _age; // _age��AgeType���� �����������Ҳδָ��
	void showPerson()
	{
		cout << "������" <<_name<< endl;
		cout << "���䣺" << _age << endl;
	}
};
void test_0006()
{
	// Person p1("chenbei", 18); // û���Զ������Ƶ�
	Person<string, int> p1("chenbei",18);//������ʽָ������
	Person<string>p2("cb",20); // ���Բ���ʽָ��intĬ�ϲ���
	p1.showPerson();
	p2.showPerson();
}
class Person1
{
public:
	void showPerson1()
	{
		cout << "Person1����" << endl;
	}
};
class Person2
{
public:
	void showPerson2()
	{
		cout << "Person2����" << endl;
	}
};
template<class T>
class myClass
{
public:
	T obj;
	// ��ģ���еĳ�Ա����
	void fun1()
	{
		obj.showPerson1();
	}
	void fun2()
	{
		obj.showPerson2();
	}
};
void test_0007()
{
	myClass<Person1>  m1;
	m1.fun1();//myClass����ʱȷ��ΪPerson1���ͷ�����ִ��
	//m1.fun2(); //Person2���Ͳ���ִ��

}
// ��ģ����Ϊ���������Ĵ��ݷ�ʽ
template <class T1 ,class T2>
class Per
{
public:
	T1 _age;
	T2 _name;
	Per(T2 name, T1 age)
	{
		this->_age = age;
		this->_name = name;
	}
	void showPerson()
	{
		cout << "������" << _name << endl;
		cout << "���䣺" << _age << endl;
	}

};
//	5.1 ָ����������� - ֱ����ʾ�������������
void printPer1(Per<int, string> &p)
{
	p.showPerson(); //�������ָ�����͵���ģ��ĵ�ַ �����͵�����Ե��ø÷���
}
//5.2 ����ģ�廯 - ������Ĳ�����Ϊģ����д���
template <class T1 , class T2>
void printPer2(Per<T1,T2>& p)
{
	p.showPerson();//�ഫ���ʱ��ָ�����������
	cout << "T1����������Ϊ��" <<typeid(T1).name()<< endl;// int
	cout << "T2����������Ϊ��" << typeid(T2).name() << endl; // string
}
//5.3 ������ģ�廯 - ������������� ģ�廯���д���
template <class T>
void printPer3(T & p)
{
	p.showPerson();
	cout << "T����������Ϊ��" << typeid(T).name() << endl;//class Per
}
void test_0008()
{
	//	5.1 ָ����������� - ֱ����ʾ�������������
	Per<int, string> p("chenebei",18);
	printPer1(p);
	//5.2 ����ģ�廯 - ������Ĳ�����Ϊģ����д���
	printPer2(p);
	//5.3 ������ģ�廯 - ������������� ģ�廯���д���
	printPer3(p);
}
// 6.��ģ����̳�
template <class T>
class base
{
public:
	T _m;
};
// 6.1 ָ�����ͼ̳�
class son1 : public base<int> // base����ָ�����������int
{
public:
	son1(int m)
	{
		this->_m = m;
	}

};
// 6.2 ���ָ�������T���ͣ�����Ҳ�����Ϊģ��
template <class T1, class T2>
class son2 : public base<T1> // base����ָ��ΪT1����
{
public:
	T2 _obj;
	son2(T1 a, T2 b)
	{
		this->_obj = b;
		this->_m = a;
	}
	void print()
	{
		cout << "T1����������Ϊ��" << typeid(T1).name() << endl;// int
		cout << "T2����������Ϊ��" << typeid(T2).name() << endl; // string
		cout << "������" << this->_obj << endl;
		cout << "���䣺" << this->_m<< endl;
	}
};
void test_0009() 
{
	// 6.1 ָ�����ͼ̳�
	son1 s1(10);
	cout<<s1._m << endl;
	// 6.2 ���ָ�������T���ͣ�����Ҳ�����Ϊģ��
	son2<int, string> s2(20, "chen");
	s2.print();
	
}
// 7. ��ģ���Ա��������ʵ��
template<class T1 , class T2>
class Car
{
public:
	T1 _name;
	T2 _age;
	Car(T1 name, T2 age);
	//{
	//	this->_age = age;
	//	this->_name = name;
	//}
	void showPerson();
	//{
	//	cout << "������" << this->_name << endl;
	//	cout << "���䣺" << this->_age << endl;
	//}
};
// 7.���캯������ʵ��
// 7.1��ģ��Ĺ��캯��������ʵ��
template<class T1 ,class T2>
//Car ::Car(T1 name, T2 age); 
Car<T1,T2>::Car(T1 name, T2 age)
{
	this->_age = age;
	this->_name = name;
}
// 7.2 ��ģ�����ͨ��Ա����������ʵ��
template<class T1, class T2>
void Car<T1, T2>::showPerson()
{
	cout << "������" << this->_name << endl;
	cout << "���䣺" << this->_age << endl;
}
void test_0010()
{
	Car<string,int> car("chenbei",100);
	car.showPerson();

}
int class_template()
//int main() 
{
	//func_template();
	//test_0006();
	//test_0007();
	//test_0008();
	//test_0009();
	test_0010();
	return 0;
}