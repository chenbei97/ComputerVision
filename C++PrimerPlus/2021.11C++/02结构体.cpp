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
	my_struct s1; // 可以省略struct创建结构体
	struct my_struct s2; 
	s2.age = 18;
	s2.name[0] = 's';
	s2.name[1] = '2';
	s1.name[0] = '1';
	s1.name[1] = 's';
	s1.price = 1.5;
	s2.wife = "cccbbb";
	//s1.name = "cccbbb"; //非法
    // 解决措施 初始化时就赋值
	my_struct s3 = {"123",0.2,1,"456"};
	// 也可以使用strcpy_s直接赋值
	strcpy_s(s3.name, "789");
	cout << s3.name << endl;
	cout << s1.name << endl;
	cout <<s2.name << endl;

	my_struct* p = &s2;// 创建指向该结构实例的指针也要使用该结构
	cout << "p->wife=" << p->wife << endl;//p->wife=cccbbb
	cout << "&s2=" << &s2 << endl;

	struct Person
	{
		int age = 18;
		char name[10] = "cb";
	}wife;
	Person* w = &wife; // 这里w指向结构体实例wife本身的地址，也要用Person去定义指针
	cout << "&wife=" << &wife << endl;
	// cout << "*(w)" << *(w)<< endl; 非法,结构体不能解引用
	cout << "*(w->name)" << *(w->name+1) << endl;// c  结构体成员可以解引用，"cb"的地址为c的地址,+1解引用为b
	cout << "w->wife=" << w->name << endl;

	// 也可以使用动态new创建指针,指针都需要箭头运算符→指向成员,使用句点运算符也可以,需要先解引用
	Person* w1 = new Person; 
	// 访问成员的2种方式
	cout << "w1->name=" << w1->name << " (*w1).name=" << (*w1).name << endl;

	// 可以定义结构体数组
	Person wifes[3];
	cout << "(wifes+1)->name=" << (wifes + 1)->name << endl;// (wifes+1)->name=cb
	
	// 还可以创建指针数组,每个指针都指向结构体
	wifes[1].age = 100;
	Person* pwifes[3] = { &wifes[0], &wifes[1] ,&wifes[2] };
	cout << "pwifes[1]->age=" << pwifes[1]->age << endl;//pwifes[1]->age=100

	// 还可以创建指向该指针数组的指针,需要使用**
	Person** ppwifes = pwifes;//pwifes是个数组，也就是指针数组的首个指针的地址
	cout <<"(*(ppwifes + 1))->age="<< (*(ppwifes + 1))->age << endl;
	// (ppwifes + 1)是个指向指针数组第2个元素指针,解引用后还是指针,且必须多加个括号*(ppwifes + 1)->age是错误的
	// 如果直接定义类型容易出错,可以使用auto
	auto ppwifes_ = pwifes;


	// 函数与结构体
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