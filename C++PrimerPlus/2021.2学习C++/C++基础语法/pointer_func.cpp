#include <iostream>
#include <string> //2019���ᱨ�� c++20
#include "hello_world.h"
#include <ctime> // ʱ��ͷ�ļ�
using namespace std;
void swap1(int a, int b) {
	int temp = b;
	b = a;
	a = temp;
	cout << "swap1�µ��β�a ="<< a << endl;
	cout << "swap1�µ��β�a =" << b << endl;
}
void swap2(int *   a, int *  b) { //int *ֻ��˵�����Ǹ�����ָ�����,ʵ�����β�Ϊ��ַ
	//*������ʱ��ʾǿ��ָ������,*�ڳ���ִ��ʱ��ʾ������,���߲�ͬ����
	int temp = * a; //��ַ������
	*a = *b; // ֱ�Ӱ�������ַ��ֵ����
	*b = temp;
}
void bubble_sort(int * arr , int len) {
     // (int *) arr �ǵ�ַ
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
   //ָ��ͺ���
	//poiner_array(); 
	//ֵ���ݺ����ڲ����ββ�Ӱ���ⲿ
	int a = 10, b= 20;
	swap1(a, b);
	cout << "ֵ����main�µ�ʵ��a =" << a << endl;
	cout << "ֵ����main�µ�ʵ��a =" << b << endl;
	//��ַ���� : ���Ըı�ʵ��
	swap2(&a, &b); //ָ����յ�ַ
	cout << "��ַ����main�µ�ʵ��a =" << a << endl;
	cout << "��ַ����main�µ�ʵ��a =" << b << endl;
	
	// ð������
	cout << "ð������" << endl;
	int arr[] = {1,3,34,65,2,64,23,67};
	bubble_sort(arr, sizeof(arr) / sizeof(arr[0]));
	print_Array(arr, sizeof(arr) / sizeof(arr[0]));
	//system("pause");
	return 0;
}