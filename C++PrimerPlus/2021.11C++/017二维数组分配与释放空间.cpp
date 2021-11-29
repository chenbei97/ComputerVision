#include "all.h"
template<class T>
bool make_arr2D(T ** & x , int n_rows , int n_cols);
template<class T>
void delete2Darr(T**& x, int n_rows);
void Study_allocate_release_arr2D()
{
	float ** x;
	int n_rows = 3;
	int n_cols = 5;
	// һ���������������ʹ���쳣����
	try { bool isallocated = make_arr2D(x, n_rows, n_cols); }
	catch(bad_alloc){cerr << "falied to create 2D array!" << endl; exit(1); };
	for (int row = 0; row < n_rows; row++)
	{
		float* t = x[row]; // t��ָ��һά��ͨ���鱾���ָ��
		for (int col = 0; col < n_cols; col++)
		{
			t[col] =(float) (row + 1) * (col + 1);
		}
	}
	for (int row = 0; row < n_rows; row++)
		for (int col = 0; col < n_cols; col++)
			cout << "x["<<row<<"]["<<col<<"] = "<<x[row][col] << endl;
	delete2Darr(x, n_rows);

}
template<class T>
bool make_arr2D(T**& x, int n_rows, int n_cols)
{
	// x ��һ��ָ��һάָ�����鱾���ָ�������
	int a1 = 1, a2 = 2, a3 = 3;
	int a4[] = {1, 2, 3, 4};
	int* a[] = {&a1,&a2,&a3,a4}; // a��1άָ������
	int** pa = a;// x ���Ǻ�paһ������
	cout << pa[1] << "   " << a[1] << endl; // ���ʵľ���a�ĵ�1��Ԫ��,ֻ����Ԫ����1����ַ
	try {
	x = new T * [n_rows]; //  T * [n_rows] ���Կ��� T *[10], x��ָ��һάָ�����鱾���ָ��
	// ������鱾����T���͵�,���Դ��T���͵ĵ�ַ
	for (int row = 0; row < n_rows; row++)
		x[row] = new T [n_cols]; // ָ�����ʹ��[]����,x[i]��������һ�����ĵ�ַ����һ��һά��ͨ���鱾��
	    // ��ʵ����һά��ͨ���������Ķ�ӦԪ�ص�ַ,�����ַ����ָ��һά���鱾��Ҳ�������ض�ֵ
	return true; // ����ɹ�
	}
	catch (bad_alloc){return false; }// ����ʧ��
}
template<class T>
void delete2Darr(T**& x, int n_rows)
{
	cout << "address of x = " << x<<endl;
	for (int row = 0; row < n_rows; row++)
	{
		delete[] x[row];
	}
	delete[] x;
	cout << "delete sucessful.." << endl;
	x = NULL;
	cout << "address of x = " << x << endl;
}