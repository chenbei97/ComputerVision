#include <iostream>
#include <string> //2019���ᱨ�� c++20
#include "hello_world.h"
#include <ctime> // ʱ��ͷ�ļ�
using namespace std;
int create_pointer(){
//int main() {
     //create_func();
    //����ָ��:��ӷ����ڴ�
    // һ��������¼��һ���������ڴ��ַ.��ָ��
    // �������� *ָ�������
    
    //1. ���õ�ַ
    int a = 10;
    int* p = &a; //ָ��p��¼a�ĵ�ַ
    //cout << &a << endl;
    //cout << p << endl; // p��&a��һ������
    
    //2.������ *p �ҵ�ָ��ָ����ڴ��е�����
    //cout << *p << endl;//*p��a��һ����
    //cout << &(*p) << endl;// &��*�������Ϊ���෴�Ĳ���,����Ϊp
    //cout << *(&a) << endl; //����Ϊa

    // ָ�����������ڴ��С  ���4λ16��������
    // 1λ16���� = 16���������� = 2��8λ������ = 2�ֽ�
    //ָ����32λϵͳ��ռ��4�ֽ�,64λ 8�ֽ�
    cout << sizeof(int*) << endl;  // 8
    cout << sizeof(char*) << endl;
    cout << sizeof(float*) << endl;
    cout << sizeof(double*) << endl;

    // ��ָ�� : ָ�����ָ���ڴ��б��Ϊ0�Ŀռ�,�����Է���, һ�����ڳ�ʼ��ָ�����,
   //0~255���ڴ���Ϊϵͳռ�ò����Է���
    //int* p = NULL; //�����ظ�����

    //Ұָ��:ָ��Ƿ����ڴ�ռ�
    //int* p = (int*)0x1000 ; //��16������ǿ��Ϊָ������������p
    //cout << *p << endl; // ����Ҹ���ַ�������ǷǷ���
   // system("pause");
    return 0;
}