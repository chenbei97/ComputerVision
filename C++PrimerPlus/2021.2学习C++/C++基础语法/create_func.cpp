#include <iostream>
#include <string> //2019不会报错 c++20
#include "hello_world.h"
#include <ctime> // 时间头文件
using namespace std;
int add(int num1, int num2) {
	// 形参 另开辟地址和实参的地址不同,不会影响原来的实参
	int sum = num1 + num2;
	return sum;
}
int max(int a, int b) {
	return a > b ? a : b;
}
void create_func(){
//int main() {
	//two_arrays();
	cout << add(1, 2) << endl;
	//1.返回值类型2.函数名3.参数表列4.函数体语句5.表达式
		/*
	返回值类型 函数名 (参数列表)
	{
	   函数体语句;
	   return 表达式 ;
	}
	*/
	// 常见的函数样式
	//1.无参无返2.无参有返3.有参无返4.有参有返
	//system("pause");
	return ;
}