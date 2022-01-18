#include <iostream>
using namespace std;
template<class T>
void matrixTranspose(T** a, const int m, const int n);
void _charter7_matrixTranspose()
{
	const int m = 5, n = 4;
	int a1[n], a2[n], a3[n], a4[n], a5[n];
	int* a[m] = { a1,a2,a3,a4,a5 };
	for (int i = 0; i < m; i++)
		a[i] = new int[n];
	cout << " before transpose : " << endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			a[i][j] = (i + 1) * (j + 1) + 1;
			cout << a[i][j] << "  ";
		}
		cout << endl;
	}
	cout << " after transpose : " << endl;
	matrixTranspose(a, m, n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			cout << a[i][j] << "  ";
		cout << endl;
	}
}
template<class T>
void matrixTranspose(T** a, const int m, const int n)
{
	T** b = new T * [n];
	if (m != n)
	{
		for (int i = 0; i < n; i++)
			b[i] = new T[m]; // 分配转置的空间 b[i]是局部的后面会自动释放
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			b[j][i] = a[i][j];
		}
		delete[] a[i];
	}
	// delete[] a; 不要删除
	for (int i = 0; i < n; i++)
	{
		a[i] = new T[m];
		for (int j = 0; j < m; j++)
			a[i][j] = b[i][j];
	}	
}