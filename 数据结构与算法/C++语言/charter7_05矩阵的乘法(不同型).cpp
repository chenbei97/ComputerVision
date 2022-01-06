#include <iostream>
using namespace std;
template<class T>
void matrixMultiply_differentSize(T** a, T** b, T** c, const int m, const int n, const int p);
void _charter7_matrixMultiply_differentSize()
{
	const int m = 5, n = 4, p = 3;
	int a1[n], a2[n], a3[n] ,a4[n],a5[n];
	int* a[m] = { a1,a2,a3,a4,a5 }; // 5×4
	int b1[p], b2[p], b3[p],b4[p];
	int* b[n] = { b1,b2,b3,b4 } ; // 4×3
	int idx = 1;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
			a[i][j] = idx++;
		}
	cout << "a is " << endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			cout << a[i][j] << "  ";
		cout << endl;
	}
	idx = n * p;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < p; j++)
		{
			b[i][j] = idx--;
		}
	cout << "b is " << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < p; j++)
			cout << b[i][j] << "  ";
		cout << endl;
	}
	int** c = new int* [m];
	for (int i = 0; i < m; i++)
		c[i] = new int[p];
	cout << "a*b is " << endl;// 5×3
	matrixMultiply_differentSize(a, b, c, m, n, p);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < p; j++)
			cout << c[i][j] << "  ";
		cout << endl;
	}
}
template<class T>
void matrixMultiply_differentSize(T** a, T** b, T** c, const int m, const int n, const int p)
{
	// m×n * n×p = m×p
	// 和同型的原理是一样的,只不过2次循环是从m和p循环的 因为结果是m×p
	for (int i = 0; i < m; i++)
		for (int j = 0; j < p; j++)
		{
			T sum = 0; //用于计算a的每一行与b的每一列的和
			for (int k = 0; k < n; k++) // a的列数和b的行数肯定是相等的,为n
				sum += a[i][k] * b[k][j]; // a[i][k]第i行的第k个数和b[k][j]第j列的第k个数
			c[i][j] = sum;// 共有m行和p列
		}
}