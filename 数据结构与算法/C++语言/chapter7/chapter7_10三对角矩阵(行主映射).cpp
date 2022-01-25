#include "chapter7_tridiagonalMatrixRowMapping.h"
void _chapter7_tridiagonalMatrixRowMapping()
{
	const int n = 5; // 对角线只有3n-2个元素
	int a[3*n-2] = {1,2,3,4,5,6,7,8,9,10,11,12,13}; // 行主映射要求按行顺序标注元素
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