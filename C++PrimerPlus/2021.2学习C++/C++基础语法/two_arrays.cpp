#include <iostream>
#include <string> //2019���ᱨ�� c++20
#include "hello_world.h"
#include <ctime> // ʱ��ͷ�ļ�
using namespace std;
int print_array(int arr[2][3]) {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {

			cout << arr[i][j] << endl;
		}
	}
	return 0;//��Ҫ�з���ֵ0�������
}
int two_arrays(){
//int main() {
	//create_array();
	//��ά�����4�ֶ��巽ʽ
	// 1.�������� ������[����][����]
	int arr[2][3];  //�����ʱ�� :2��3�� ����С�����1��2
	arr[0][0] = 0;
	arr[0][1] = 1;
	arr[0][2] = 34;
	arr[1][0] = 4;
	arr[1][1] = 445;
	arr[1][2] = 87;
	//print_array(arr);
	//2.�������� ������[����][����] = {����1,����2}
	int arr1[2][3] = {
		{1,2,3},{4,5,6}
	};
	//print_array(arr1);
	//3.�������� ������[����][����] = {����}
	int arr3[2][3] = {11,4,3,67,5,6};
	//print_array(arr3);
	//4.�������� ������[][����] = {����1,����2,...}
	int arr4[2][3] = { 121,24,33,647,35,16 };
	//print_array(arr4);

	//cout << sizeof(arr4) << endl; //�����С
	//cout << sizeof(arr4[0]) << endl; //����һ�д�С
	//cout << sizeof(arr4[0][0]) << endl; //����Ԫ�ش�С
	//cout << sizeof(arr4)/ sizeof(arr4[0]) << endl; //��ά��������
	//cout << sizeof(arr4[0]) / sizeof(arr4[0][0]) << endl; //��ά��������

	//cout << (int)arr4 << endl; //��ά�����׵�ַ Ҳ�ǵ�һ�к͵�һ��Ԫ�ص��׵�ַ
	//cout << (int)arr4[0] << endl; //��ά�����һ���׵�ַ
	//cout << (int)arr4[1] << endl; //��ά����ڶ����׵�ַ ���ֲ�12  ָ����Բ�12

	cout << (int)arr4[0][0] << endl; //��ά�����һ��Ԫ�ص�ַ �������ﲻ����ָ��
	cout << (int)arr4[0][1] << endl;
	cout << (int)arr4[0][2] << endl;
	cout << (int)arr4[1][0] << endl;
	cout << (int)arr4[1][1] << endl;
	cout << (int)arr4[1][2] << endl; //��ά�������һ��Ԫ�ص�ַ
	//system("pause"); 
	return 0;
}