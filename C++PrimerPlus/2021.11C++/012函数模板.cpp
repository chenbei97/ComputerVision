#include "all.h"
struct job
{
	char name[40];
	double salary;
	int floor;
};
void Swap(job& a, job& b)// ��ģ�庯��
{
	cout << "��ģ���ຯ��������..." << endl;
	job c;
	c = a;
	a = b;
	b = c;
}
template <typename T>
void Swap(T& a, T& b)//��ͨģ�庯��,�������ṹ��,�ύ���ṹ���ȫ����Ա
{
	cout << "��ͨģ���౻����..." << endl;
	T c;
	c = a;
	a = b;
	b = c;
}
template <> void Swap<job>(job& a, job& b)// ��ʽ���廯�汾,����ֻ�������ֳ�Ա
{
	cout << "��ʽ������ģ���౻����..." << endl;
	double s;
	s = a.salary;
	a.salary = b.salary;
	b.salary = s;

	int f;
	f = a.floor;
	a.floor = b.floor;
	b.floor = f;
}
template <typename T>
void Study__Func_Template_Swap(T& a, T& b)
{
	T c;
	c = a;
	a = b;
	b = c;
}
void Study_Func_Template()
{
	// ��ʽʵ����
	//template void Swap<int>(int& a, int& b);��ǰ������ʽʵ����


	// ��ͨģ���࣬���Խ����ṹ��
	int a1 = 1, a2 = 2;
	Study__Func_Template_Swap(a1, a2);
	cout << "a1=" << a1 << "   a2=" << a2;

	double b1 = 1.1, b2 = 2.2;
	Study__Func_Template_Swap(b1, b2);
	cout << "	b1=" << b1 << "   b2=" << b2;

	// ��ģ�庯������ͨģ�庯������ʽ��ģ�庯�������ȼ��Ƚ�
	// ͬʱ����ʱ,��ģ�庯���ȱ�����
	job j1 = { "a",1.5,3 }, j2 = { "b",2.4,6 };
	cout << "before swap��" << " &j1=" << &j1 << "   &j2=" << &j2 << endl;
	Swap(j1, j2);
	cout << "j1.salary=" << j1.salary << "   j2.salary=" << j2.salary << endl;

	system("pause");
}


