#include <iostream>
using namespace std;
//1.new�Ļ����﷨
int* func1()
{
	int* p = new int(100); //��100�ĵ�ַ����ָ�뷵��
	return p;
}
void test1()
{
	int* p = func1();
	cout << *p << endl;
	// Ȼ�����ͷŶ������ݿ���ʹ��delete
	delete p;
	//cout << *p << endl; // ������ִ�и����
}
//2.������������
void func2()
{
	int* arr = new int[10]; //[]���������� ���ص��������׵�ַ ������������Ҫ������
	for (int i = 0; i < 10; i++)
	{
		arr[i] = i + 100;
	}
	for (int i = 0; i < 10; i++)
	{
		cout << arr[i] << endl;
	}
	// �ͷ�����
	delete[]  arr; //�������Ų����ͷ��������
}
void The_Use_Of_New()
{
	//int main()
		//1.new�Ļ����﷨
	test1(); // ����100
	//2.new��������
	func2();
	//system("pause ");
	//return 0;
}