#include <iostream>
#include "quote_pointer.h"
using namespace std;
const double pi = 3.1415926;
class Circle
{
	// ����Ȩ��
	// ����Ȩ��
public : 
	//���� : �뾶
	int r = 1; //�뾶 
	// ���� : ���ܳ�
	double calculateZC()
	{
		return 2 * pi * r;
	}

};
class student
{
public :
	string _name; //������
	int _id; //ѧ��
	
	void showStudent() 
	{
		cout << "ѧ������ : " << _name << endl;
		cout << "ѧ��id  :   " << _id << endl;
	}
	void setName(string name)
	{
		_name = name; // �����ı�������
	}
};
int class_object()
//int main() 
{
	//quote_pointer(); //�ܵ����ú�ָ��Ա�
	//�鿴���ó���
	//quote_contst();
	 
	
	// ��װ���̳С���̬
	// ���Բ�����ܳ�
	Circle  yuan; // ʵ����
	yuan.r = 10;
	double ZC = yuan.calculateZC();
	cout << "Բ���ܳ�Ϊ : " << ZC <<endl;

	student s1;
	s1._name = "����";
	s1._id = 1;
	s1.showStudent();
	s1.setName("����");
	s1.showStudent();
	system("pause"); 
	return 0;
}