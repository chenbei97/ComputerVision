#include "all.h"
void method_1(int n);
void method_2(int n);
void select(int n, void (*p)(int));
void Study_Func_Pointer()
{
	int n;
	cin >> n;
	if (n == 1)
	{
		select(n, method_1);// ʱ��1ʹ���㷨1
	}
	else
	{
		select(n, method_2);// ʱ��2ʹ���㷨2
	}

}

void select(int n, void (*p)(int))
{
	// double (*p)(int) �� ԭ��double method_1(int n)�����Ƶ�
	// ����(*p)���վ��Ǻ���,��ôp���Ǻ���ָ��
	(*p)(n); // ִ�к���
	p(n); // Ҳ���ԣ�C++����Ϊ����ָ��p��(*p)�ȼ�
}
void method_1(int n)
{
	cout << "method_1 = " << n << endl;
}
void method_2(int n)
{
	cout << "method_2 = " << n << endl;
}