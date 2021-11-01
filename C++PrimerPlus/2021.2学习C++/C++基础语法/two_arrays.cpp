#include <iostream>
#include <string> //2019不会报错 c++20
#include "hello_world.h"
#include <ctime> // 时间头文件
using namespace std;
int print_array(int arr[2][3]) {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {

			cout << arr[i][j] << endl;
		}
	}
	return 0;//需要有返回值0否则出错
}
int two_arrays(){
//int main() {
	//create_array();
	//二维数组的4种定义方式
	// 1.数组类型 数组名[行数][列数]
	int arr[2][3];  //定义的时候 :2行3列 但是小标最大到1和2
	arr[0][0] = 0;
	arr[0][1] = 1;
	arr[0][2] = 34;
	arr[1][0] = 4;
	arr[1][1] = 445;
	arr[1][2] = 87;
	//print_array(arr);
	//2.数据类型 数组名[行数][列数] = {数据1,数据2}
	int arr1[2][3] = {
		{1,2,3},{4,5,6}
	};
	//print_array(arr1);
	//3.数据类型 数组名[行数][列数] = {数据}
	int arr3[2][3] = {11,4,3,67,5,6};
	//print_array(arr3);
	//4.数据类型 数组名[][列数] = {数据1,数据2,...}
	int arr4[2][3] = { 121,24,33,647,35,16 };
	//print_array(arr4);

	//cout << sizeof(arr4) << endl; //数组大小
	//cout << sizeof(arr4[0]) << endl; //数组一行大小
	//cout << sizeof(arr4[0][0]) << endl; //数组元素大小
	//cout << sizeof(arr4)/ sizeof(arr4[0]) << endl; //二维数组行数
	//cout << sizeof(arr4[0]) / sizeof(arr4[0][0]) << endl; //二维数组列数

	//cout << (int)arr4 << endl; //二维数组首地址 也是第一行和第一个元素的首地址
	//cout << (int)arr4[0] << endl; //二维数组第一行首地址
	//cout << (int)arr4[1] << endl; //二维数组第二行首地址 发现差12  指针可以差12

	cout << (int)arr4[0][0] << endl; //二维数组第一个元素地址 不过这里不再是指针
	cout << (int)arr4[0][1] << endl;
	cout << (int)arr4[0][2] << endl;
	cout << (int)arr4[1][0] << endl;
	cout << (int)arr4[1][1] << endl;
	cout << (int)arr4[1][2] << endl; //二维数组最后一个元素地址
	//system("pause"); 
	return 0;
}