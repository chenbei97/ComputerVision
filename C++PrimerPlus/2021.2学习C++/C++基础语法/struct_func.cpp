#include <iostream>
#include <string> //2019不会报错 c++20
#include "hello_world.h"
#include <ctime> // 时间头文件
using namespace std;
struct student {
	string name = "cb";
	int age = 24;
	int score = 100;
};
void print_student_value(struct student s) {
     //值传递 声明参数为一个结构体  (student   s)
	// 此结构体是student定义的罢了
	s.name = "CB";
	cout << "子函数中值传递姓名" << s.name << endl;
 }
void print_student_addr(const  struct  student * s) {
	//值传递 声明参数为一个结构体的地址  (student*    s)
   // 此结构体地址是student的罢了
	//student *s 只占据4子节， student s 需要开辟新的内存用于值传递, 地址传递可以节省内存
	// 地址传递节省内存但是不安全,可能写操作就会导致原本的数据发生改变
	// 所以使用const 可以防止某个函数写操作 也叫常量指针不能改变值,函数只读
	//s->name = "CB";
	cout << "子函数中地址传递姓名" << s->name << endl;
}
int struct_func(){
//int main() {
	//struct_struct(); 
	// 结构体作为函数参数
	//1.值传递 2.地址传递
	student stu; 
	// 1.值传递
	print_student_value(stu); //子函数更改形参
	cout << "main函数中值传递姓名" << stu.name << endl; //原变量没发生改变
	//2.地址传递
	student* p = &stu;
	//print_student_addr(&stu);//子函数更改形参
	print_student_addr(p);//传递指针也可以 p 0r &stu 都正确
	cout << "main函数中地址传递姓名" << stu.name << endl; //原变量发生了改变,但是使用const后不会改变
	//system("pause");


	return 0;
}