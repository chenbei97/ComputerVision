#include <iostream>
#include <string> //2019���ᱨ�� c++20
#include <ctime> // ʱ��ͷ�ļ�
//#include "hello_world.h"
using namespace std;
//int create_array()
int main()
{
	//hello_world();
	// int arr[5] = {1,2,3,4,5} ;
	// ctrl + k + d �Զ������ʽ
	int arr[5]; //��������
	cout << sizeof(arr) / 4 << endl;
	for (int i = 0; i <= sizeof(arr) / 4 - 1; i++) //��Ҫ��1
		// for i in range(5) �������е�5 ǰ�պ󿪿ռ�
	{
		arr[i] = i; //i =4�Ժ���ȻС��5,i���ӵ�5,��ʱ���л���ִ���
		cout << arr[i] << endl;
		//cout <<&arr[i] << endl; //��ַ
		//cout << int (&arr[i]) << endl; //��ַ��Ӧ��������
	}
	int  list[] = {324,46,234,567,2322,546};
	int end = sizeof(list) / 4 - 1;
	int temp = 0;
	for (int start = 0; start <= sizeof(list) / 4 / 2 -1; start++ )
	{
		temp = list[end-start]; // ʵ����������
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

