#include <iostream>
#include <string> //2019不会报错 c++20
#include "hello_world.h"
#include <ctime> // 时间头文件
using namespace std;
struct student {
	string name="cb";
	int age = 19;
	int score = 100;
};
struct teacher {
	int id = 5;
	string name = "sb";
	int age = 40;
	struct student  std = {
	"chen",100,100}; //某个辅导的学生
};
int struct_struct(){
//int main() {
	//Struct(); 
	// 结构体嵌套结构体
	student  s1 = {"123",12,45};
	teacher  t1 = { 000,"wang",200,s1};
	cout << t1.std.age << endl; //返回的是实参s1的年龄
	teacher t2;
	cout << t2.std.age << endl;//初始化的年龄100
	
	
	//system("pause");
	return 0;
}