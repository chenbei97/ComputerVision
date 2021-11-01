#include <iostream>
#include <string> //2019不会报错 c++20
#include "hello_world.h"
#include <ctime> // 时间头文件
using namespace std;
int poiner_array(){
//int main(){
    // 利用指针访问二维数组
	// 数组本身就是地址
	int arr[10] = {1,2,3,4,5,6,7,8,9,10};
	int* p = arr;//不需要&arr，arr就是数组首地址
	int* p1 = &arr[0];//或者指向某个具体元素地址是可以的
	cout << *p << endl; // arr首地址解引用就是首元素1
	cout << *p1 << endl; // 首元素指针解引用也是首元素
	cout << p << endl; //地址也完全相同
	cout << p1 << endl; 

	//p++; // p= p+1 指针加1不是值加1,而是指针的地址加1,这个1加的是数组一个元素的内存大小(偏移4个字节)
	//cout << *p << endl;

    cout << "指针遍历数组"  << endl ;
	for (int i = 0; i < 10; i++)
	{
		cout << *p << endl;
		p++;
	}

	//system("pause");
	return 0;
}