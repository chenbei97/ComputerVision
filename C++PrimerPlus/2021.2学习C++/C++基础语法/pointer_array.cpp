#include <iostream>
#include <string> //2019���ᱨ�� c++20
#include "hello_world.h"
#include <ctime> // ʱ��ͷ�ļ�
using namespace std;
int poiner_array(){
//int main(){
    // ����ָ����ʶ�ά����
	// ���鱾����ǵ�ַ
	int arr[10] = {1,2,3,4,5,6,7,8,9,10};
	int* p = arr;//����Ҫ&arr��arr���������׵�ַ
	int* p1 = &arr[0];//����ָ��ĳ������Ԫ�ص�ַ�ǿ��Ե�
	cout << *p << endl; // arr�׵�ַ�����þ�����Ԫ��1
	cout << *p1 << endl; // ��Ԫ��ָ�������Ҳ����Ԫ��
	cout << p << endl; //��ַҲ��ȫ��ͬ
	cout << p1 << endl; 

	//p++; // p= p+1 ָ���1����ֵ��1,����ָ��ĵ�ַ��1,���1�ӵ�������һ��Ԫ�ص��ڴ��С(ƫ��4���ֽ�)
	//cout << *p << endl;

    cout << "ָ���������"  << endl ;
	for (int i = 0; i < 10; i++)
	{
		cout << *p << endl;
		p++;
	}

	//system("pause");
	return 0;
}