#include "charter7_tridiagonalMatrixRowMapping.h"
void _charter7_tridiagonalMatrixRowMapping()
{
	const int n = 5; // �Խ���ֻ��3n-2��Ԫ��
	int a[3*n-2] = {1,2,3,4,5,6,7,8,9,10,11,12,13}; // ����ӳ��Ҫ����˳���עԪ��
	tridiagonalMatrixRow<int> A(a, n);
	cout << "A is " << endl;
	cout << A << endl;
	A.set(5, 5, 100);
	cout << "A(5,5) = " << A.get(5, 5) << endl;
	try
	{
		A.set(5, 3, 20); // throw e
	}
	catch (illegalParameterValue e)
	{
		e.outputMessage();
	}
}