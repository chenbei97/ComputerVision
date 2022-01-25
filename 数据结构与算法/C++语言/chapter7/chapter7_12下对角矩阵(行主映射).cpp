#include "chapter7_lowerTriangularMatrixRow.h"
void _chapter7_lowerTriangularMatrixRow()
{
	const int n = 5;
	int a[n * (n + 1) / 2] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
	lowerTriangularMatrixRow<int> A(a, n);
	cout << "A is " << endl;
	cout << A << endl;
	A.set(4, 4, 100);
	cout << "A(4,4) = " << A.get(4, 4) << endl;
	try
	{
		//cout << "A(6,6) = " << A.get(6, 6) << endl;
		A.set(3, 5, 20); // throw e
	}
	catch (illegalParameterValue e)
	{
		e.outputMessage();
	}
	catch (matrixIndexOutOfBounds e)
	{
		e.outputMessage();
	}
}