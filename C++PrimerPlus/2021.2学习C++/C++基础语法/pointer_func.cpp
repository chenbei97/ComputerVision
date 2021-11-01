#include <iostream>
#include <string> //2019不会报错 c++20
#include "hello_world.h"
#include <ctime> // 时间头文件
using namespace std;
void swap1(int a, int b) {
	int temp = b;
	b = a;
	a = temp;
	cout << "swap1下的形参a ="<< a << endl;
	cout << "swap1下的形参a =" << b << endl;
}
void swap2(int *   a, int *  b) { //int *只是说明这是个整型指针变量,实际上形参为地址
	//*在声明时表示强调指针类型,*在程序执行时表示解引用,两者不同含义
	int temp = * a; //地址解引用
	*a = *b; // 直接把两个地址的值交换
	*b = temp;
}
void bubble_sort(int * arr , int len) {
     // (int *) arr 是地址
	for (int i = 0; i < len - 1; i++) {
		for (int j = 0; j < len - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}
void print_Array(int * arr,int len) {
	for (int i = 0; i < len; i++) {
		cout << arr[i] << endl;
	}
}
int  pointer_func() {
//int main() {
   //指针和函数
	//poiner_array(); 
	//值传递函数内部的形参不影响外部
	int a = 10, b= 20;
	swap1(a, b);
	cout << "值传递main下的实参a =" << a << endl;
	cout << "值传递main下的实参a =" << b << endl;
	//地址传递 : 可以改变实参
	swap2(&a, &b); //指针接收地址
	cout << "地址传递main下的实参a =" << a << endl;
	cout << "地址传递main下的实参a =" << b << endl;
	
	// 冒牌排序
	cout << "冒牌排序" << endl;
	int arr[] = {1,3,34,65,2,64,23,67};
	bubble_sort(arr, sizeof(arr) / sizeof(arr[0]));
	print_Array(arr, sizeof(arr) / sizeof(arr[0]));
	//system("pause");
	return 0;
}