#include "contanter.h"
/*
<1>�����������
			���غ������ò��������࣬����󳣳�Ϊ��������
			��������ʹ�����ص�()ʱ��Ϊ���ƺ������� ���º���
			���ʣ���������(�º���)��һ���࣬����һ������
<2>���������ص�
			��������ʹ��ʱ��������ͨ�������ã������в����ͷ���ֵ
			�������������Ϊ�������ݣ�������ͨ�����ĸ���������Լ���״̬
*/
class Myadd
{
public:
	int operator ()(int v1, int v2)
	{
		return v1 + v2;
	}

};
class Myprint
{
public:
	Myprint()
	{
		this->count = 0;
	}
	void operator()(string test)
	{
		cout <<"test��"<< test << endl;
		this->count++;
	}
	int count; // ��¼�������ü���
};
void doPrint(Myprint& mp, string test)
{
	mp(test);
}
void test_35()
{
	Myadd myadd;
	cout << myadd(10, 10) << endl;
	// ������ͨ�����ĸ���������Լ���״̬
	Myprint myprint;
	myprint("helloworld");
	myprint("helloworld");
	cout << myprint.count << endl;
	spilit_line();
	// ��������myprint������Ϊ��������
	doPrint(myprint, "helloC++");
}
int stl_func_object()
//int main()
{
	 // stl_example2();
	test_35();
	return 0;
}