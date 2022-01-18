#include <iostream>
using namespace std;
template<class T>
void matrixMultiply_sameSize(T ** a ,T **b, T **c , const int n);
void _charter7_matrixMultiply_sameSize()
{
	const int n = 3;
	int a0[n], a1[n], a2[n];
	int* a[n] = { a0,a1,a2 };
	int b0[n], b1[n], b2[n];
	int* b[n] = { b0,b1,b2 };
	int idx = 1;
	for (int i = 0; i <n; i++)
		for (int j = 0; j < n; j++)
		{
			a[i][j] = idx++;
		}
	cout << "a is " << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << a[i][j] << "  ";
		cout << endl;
	}
	idx = pow(n,2);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			b[i][j] = idx--;
	cout << "b is " << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << b[i][j] << "  ";
		cout << endl;
	}
	int** c = new int* [n]; 
	for (int i = 0; i < n; i++)
		c[i] = new int[n];
	cout << "a*b is " << endl;
	matrixMultiply_sameSize(a, b, c, n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << c[i][j] << "  ";
		cout << endl;
	}
}
template<class T>
void matrixMultiply_sameSize(T** a, T** b, T** c, const int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			T sum = 0; //用于计算a的每一行与b的每一列的和
			for (int k = 0; k < n; k++) // a的列数和b的行数肯定是相等的,为n
				sum += a[i][k] * b[k][j]; // a[i][k]第i行的第k个数和b[k][j]第j列的第k个数
			c[i][j] = sum;
		}
}