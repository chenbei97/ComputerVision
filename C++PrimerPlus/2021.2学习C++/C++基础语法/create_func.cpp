#include <iostream>
#include <string> //2019���ᱨ�� c++20
#include "hello_world.h"
#include <ctime> // ʱ��ͷ�ļ�
using namespace std;
int add(int num1, int num2) {
	// �β� ���ٵ�ַ��ʵ�εĵ�ַ��ͬ,����Ӱ��ԭ����ʵ��
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
	//1.����ֵ����2.������3.��������4.���������5.���ʽ
		/*
	����ֵ���� ������ (�����б�)
	{
	   ���������;
	   return ���ʽ ;
	}
	*/
	// �����ĺ�����ʽ
	//1.�޲��޷�2.�޲��з�3.�в��޷�4.�в��з�
	//system("pause");
	return ;
}