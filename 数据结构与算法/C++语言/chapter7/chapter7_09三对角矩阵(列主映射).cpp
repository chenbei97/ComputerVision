#include "chapter7_tridiagonalMatrixColMapping.h"
void _chapter7_tridiagonalMatrixColMapping()
{
	const int n = 5;
	int a[3 * n - 2] = { 1,2,3,4,5,6,7,8,9,10,11,12,13 };
	tridiagonalMatrixCol<int> A(a, n);
	cout << "A is " << endl;
	cout << A << endl;
	A.set(5, 5, 100);
	cout << "A(5,5) = " << A.get(5, 5) << endl;
	A.set(3, 4, 50);
	cout << "now A is " << endl;
	cout << A << endl;
	try
	{
		A.set(5, 3, 20); // throw e
	}
	catch (illegalParameterValue e)
	{
		e.outputMessage();
	}
}