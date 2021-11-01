#include <iostream>
#include <string> //2019不会报错 c++20
#include "hello_world.h"
#include <ctime> // 时间头文件
using namespace std;
void const_pointer(){
//int main() {
	//create_pointer();
	//1.const 修饰指针--->常量指针;
	//2.const修饰常量--->指针常量；
    //3.const 修饰指针又修饰常量；

	// 1.常量指针:指针的指向可以修改,但指针指向的值不能修改
	int a = 10, b = 20;
	const int* p = &a; //常量指针
	//*p = 20; //*p就是解引用即原来的值10,是不能改变和赋值20的
	p = &b; //但是p是个地址,指向是可以改的,指向b的地址
	
	//2.指针常量:
	int* const p1 = &a;
	* p1 = 20; //值可以修改
	// p1 = &b; //指向不能修改

	//3.const即修饰指针又修饰常量
	const int* const p2 = &a;
	//*p2 = 20; 不能修改值
	//p2 = &b;//也不能修改指向
	//system("pause");
	//return 0;
}
