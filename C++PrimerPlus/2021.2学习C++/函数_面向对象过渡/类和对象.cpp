#include <iostream>
#include "quote_pointer.h"
using namespace std;
const double pi = 3.1415926;
class Circle
{
	// 访问权限
	// 公共权限
public : 
	//属性 : 半径
	int r = 1; //半径 
	// 方法 : 求周长
	double calculateZC()
	{
		return 2 * pi * r;
	}

};
class student
{
public :
	string _name; //类属性
	int _id; //学号
	
	void showStudent() 
	{
		cout << "学生姓名 : " << _name << endl;
		cout << "学生id  :   " << _id << endl;
	}
	void setName(string name)
	{
		_name = name; // 方法改变类属性
	}
};
int class_object()
//int main() 
{
	//quote_pointer(); //总的引用合指针对比
	//查看引用常用
	//quote_contst();
	 
	
	// 封装、继承、多态
	// 设计圆类求周长
	Circle  yuan; // 实例化
	yuan.r = 10;
	double ZC = yuan.calculateZC();
	cout << "圆的周长为 : " << ZC <<endl;

	student s1;
	s1._name = "张三";
	s1._id = 1;
	s1.showStudent();
	s1.setName("李四");
	s1.showStudent();
	system("pause"); 
	return 0;
}