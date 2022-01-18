#include <iostream>
using namespace std;
template<class T>
void matrixAdd(T** a, T** b, T** c, const int rows, const int cols);
void _charter7_matrixAdd()
{
	const int cols = 5;
	const int rows = 3;
	int a0[cols], a1[cols], a2[cols];
	int *a[rows] = { a0,a1,a2 };
	int b0[cols], b1[cols], b2[cols];
	int* b[rows] = { b0,b1,b2 };
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			a[i][j] = 1+(i + 1) * (j + 1) ;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			b[i][j] = 1 - (i + 1) * (j + 1) ;
	// a+ b = E*2
	int** c = new int*[rows]; // 必须要先分配空间
	for (int i = 0; i < rows; i++)
		c[i] = new int[cols]; // 列也要分配
	matrixAdd(a, b, c, rows, cols);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			cout << c[i][j] << "  ";
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < rows; i++)
		delete [] c[i];//删除分配的列空间
	delete [] c; // 删除c分配的行空间
	c = NULL;//避免成为野指针
}
template<class T>
void matrixAdd(T** a, T** b, T** c,const int rows, const int cols)
{
	// a+b = c ,a,b,c是指针数组的指针
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			c[i][j] = a[i][j] + b[i][j]; // 指针数组是可以[][]访问的
	// charter7_01二维数组和指针复习.cpp
	// <2.2.2 全局指针[][]访问,全局指针只有3个元素> 这里说明了**是可以访问矩阵元素的
}