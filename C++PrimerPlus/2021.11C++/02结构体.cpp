#include "all.h"
struct Student
{
	int age = 0;
	char name[20] = {};
};
Student Study_Sum_Student_Age(Student s1, Student s2);
void Study_Show_Student(const Student* s);
void Study_struct()
{
	int arr[] = { 0,1,2 };
	struct my_struct
	{
		char name[4] = {};
		double price  = 0.;
		int age = 0;
		string wife;
	};
	my_struct s1; // ����ʡ��struct�����ṹ��
	struct my_struct s2; 
	s2.age = 18;
	s2.name[0] = 's';
	s2.name[1] = '2';
	s1.name[0] = '1';
	s1.name[1] = 's';
	s1.price = 1.5;
	s2.wife = "cccbbb";
	//s1.name = "cccbbb"; //�Ƿ�
    // �����ʩ ��ʼ��ʱ�͸�ֵ
	my_struct s3 = {"123",0.2,1,"456"};
	// Ҳ����ʹ��strcpy_sֱ�Ӹ�ֵ
	strcpy_s(s3.name, "789");
	cout << s3.name << endl;
	cout << s1.name << endl;
	cout <<s2.name << endl;

	my_struct* p = &s2;// ����ָ��ýṹʵ����ָ��ҲҪʹ�øýṹ
	cout << "p->wife=" << p->wife << endl;//p->wife=cccbbb
	cout << "&s2=" << &s2 << endl;

	struct Person
	{
		int age = 18;
		char name[10] = "cb";
	}wife;
	Person* w = &wife; // ����wָ��ṹ��ʵ��wife����ĵ�ַ��ҲҪ��Personȥ����ָ��
	cout << "&wife=" << &wife << endl;
	// cout << "*(w)" << *(w)<< endl; �Ƿ�,�ṹ�岻�ܽ�����
	cout << "*(w->name)" << *(w->name+1) << endl;// c  �ṹ���Ա���Խ����ã�"cb"�ĵ�ַΪc�ĵ�ַ,+1������Ϊb
	cout << "w->wife=" << w->name << endl;

	// Ҳ����ʹ�ö�̬new����ָ��,ָ�붼��Ҫ��ͷ�������ָ���Ա,ʹ�þ�������Ҳ����,��Ҫ�Ƚ�����
	Person* w1 = new Person; 
	// ���ʳ�Ա��2�ַ�ʽ
	cout << "w1->name=" << w1->name << " (*w1).name=" << (*w1).name << endl;

	// ���Զ���ṹ������
	Person wifes[3];
	cout << "(wifes+1)->name=" << (wifes + 1)->name << endl;// (wifes+1)->name=cb
	
	// �����Դ���ָ������,ÿ��ָ�붼ָ��ṹ��
	wifes[1].age = 100;
	Person* pwifes[3] = { &wifes[0], &wifes[1] ,&wifes[2] };
	cout << "pwifes[1]->age=" << pwifes[1]->age << endl;//pwifes[1]->age=100

	// �����Դ���ָ���ָ�������ָ��,��Ҫʹ��**
	Person** ppwifes = pwifes;//pwifes�Ǹ����飬Ҳ����ָ��������׸�ָ��ĵ�ַ
	cout <<"(*(ppwifes + 1))->age="<< (*(ppwifes + 1))->age << endl;
	// (ppwifes + 1)�Ǹ�ָ��ָ�������2��Ԫ��ָ��,�����ú���ָ��,�ұ����Ӹ�����*(ppwifes + 1)->age�Ǵ����
	// ���ֱ�Ӷ����������׳���,����ʹ��auto
	auto ppwifes_ = pwifes;


	// ������ṹ��
	Student _s1 = { 20,"ggg" };
	Student _s2 = { 40,"ddd" };
	Student s = Study_Sum_Student_Age(_s1, _s2);
	cout << "s.age=" << s.age << endl;
	Student* ps = &s;
	Student const* ps1 = &s;
	Study_Show_Student(ps);
	Study_Show_Student(ps1);
	system("pause");
}
Student Study_Sum_Student_Age(Student s1, Student s2)
{
	Student s ;
	s.age = s1.age + s2.age;
	strcpy_s(s.name,"chenbei" );
	return s;
}
void Study_Show_Student(const Student* s)
{
	cout << "student.age=" << s->age << endl;
	cout << "student name=" << s->name << endl;
}