#include "all.h"
void divide(double y, double x)
{
	try
	{
		if (x == 0.0)
			throw "ZeroDivisionError"; // ��������Զ����׳����쳣����
		else if (x < 0)
			throw  -1; // �����������int����
		else
		{
			double z = y / x;
			cout << "z=" << z << endl;
		}
	}
	catch (const char * s) // �ַ���������쳣������const chat * s����
	{
		cout <<   s << endl;
	}
	catch (int n)
	{
		cout << n << endl;
	}
}
void Study_Exception_Handle()
{
	double y = 5.4, x1 = 2.0, x2 = 0.0,x3 = -1.3;
	divide(y, x1);
	divide(y, x2);
	divide(y, x3);
}