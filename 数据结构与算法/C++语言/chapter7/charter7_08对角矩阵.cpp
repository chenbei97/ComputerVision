#include "charter7_diagonalMatrix.h"
void _charter7_diagonalMatrix()
{
	diagonalMatrix<int> x(20);
	x.set(1, 1, 22);
	x.set(5, 5, 44);
	x.set(8, 5, 0);
	cout << "x(5,5) = "<<x.get(5, 5) << endl;
	cout << "x(1,1) = " << x.get(1, 1) << endl;
	cout << "x(10,1) = " << x.get(10, 1) << endl;
	cout << "x is " << endl;
	cout << x << endl;
	
	double a[10] = { 1,2,3,4,5,6,7,8,9,10 };
	diagonalMatrix<double> y(a,10);
	cout << "y is " << endl;
	cout << y << endl;
}