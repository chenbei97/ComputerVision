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
	int** c = new int*[rows]; // ����Ҫ�ȷ���ռ�
	for (int i = 0; i < rows; i++)
		c[i] = new int[cols]; // ��ҲҪ����
	matrixAdd(a, b, c, rows, cols);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			cout << c[i][j] << "  ";
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < rows; i++)
		delete [] c[i];//ɾ��������пռ�
	delete [] c; // ɾ��c������пռ�
	c = NULL;//�����ΪҰָ��
}
template<class T>
void matrixAdd(T** a, T** b, T** c,const int rows, const int cols)
{
	// a+b = c ,a,b,c��ָ�������ָ��
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			c[i][j] = a[i][j] + b[i][j]; // ָ�������ǿ���[][]���ʵ�
	// charter7_01��ά�����ָ�븴ϰ.cpp
	// <2.2.2 ȫ��ָ��[][]����,ȫ��ָ��ֻ��3��Ԫ��> ����˵����**�ǿ��Է��ʾ���Ԫ�ص�
}