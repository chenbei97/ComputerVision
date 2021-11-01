#include <iostream>
#include <string> //2019不会报错 c++20
#include <ctime> // 时间头文件
//#include "hello_world.h"
using namespace std;
//int create_array()
int main()
{
	//hello_world();
	// int arr[5] = {1,2,3,4,5} ;
	// ctrl + k + d 自动整理格式
	int arr[5]; //定义数组
	cout << sizeof(arr) / 4 << endl;
	for (int i = 0; i <= sizeof(arr) / 4 - 1; i++) //需要减1
		// for i in range(5) 不能运行到5 前闭后开空间
	{
		arr[i] = i; //i =4以后仍然小于5,i增加到5,此时运行会出现错误
		cout << arr[i] << endl;
		//cout <<&arr[i] << endl; //地址
		//cout << int (&arr[i]) << endl; //地址对应的整型数
	}
	int  list[] = {324,46,234,567,2322,546};
	int end = sizeof(list) / 4 - 1;
	int temp = 0;
	for (int start = 0; start <= sizeof(list) / 4 / 2 -1; start++ )
	{
		temp = list[end-start]; // 实现逆序数组
		list[end-start] = list[start];
		list[start] = temp;
		//cout << list[start] << endl;
	}
	for (int i = 0; i <= end; i++) {
		cout << list[i] << endl;
	}
	//system("pause");
	return 0;
}

