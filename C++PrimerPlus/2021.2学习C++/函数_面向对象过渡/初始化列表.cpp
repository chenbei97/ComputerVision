#include <iostream>
using namespace std;
#include "quote_pointer.h"
// ��ʽ List() : a(5) , b(10),c(20)
class List 
{
public :
	int _a;
	int _b;
	int _c;
	List() : _a(5), _b(10), _c(20) {}//��ʼ���б�����
	List(int a, int b, int c) : _a(a), _b(b), _c(c) {} // �����Բ�д�� ������
		void print()
	{
		cout << "a = " << _a << "\nb = " << _b<<"\nc = "<<_c <<endl;
	}

};
int initialList()
//int main()
{
	//copy_Construct(); // �������캯������
	//Deep_Shallow_Copy(); // �����ǳ����
	
	List L1; // �вι���1 : �����˳�ʼ���б����� 
	L1.print();

	List L2(1, 2, 3);//�вι���2  : ����б����
	L2.print();
	//system("pause");
	return 0;


}