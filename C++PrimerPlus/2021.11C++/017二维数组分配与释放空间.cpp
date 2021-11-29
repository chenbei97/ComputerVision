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
	// 一般最好在主程序中使用异常处理
	try { bool isallocated = make_arr2D(x, n_rows, n_cols); }
	catch(bad_alloc){cerr << "falied to create 2D array!" << endl; exit(1); };
	for (int row = 0; row < n_rows; row++)
	{
		float* t = x[row]; // t是指向一维普通数组本身的指针
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
	// x 是一个指向一维指针数组本身的指针的引用
	int a1 = 1, a2 = 2, a3 = 3;
	int a4[] = {1, 2, 3, 4};
	int* a[] = {&a1,&a2,&a3,a4}; // a是1维指针数组
	int** pa = a;// x 就是和pa一个类型
	cout << pa[1] << "   " << a[1] << endl; // 访问的就是a的第1个元素,只不过元素是1个地址
	try {
	x = new T * [n_rows]; //  T * [n_rows] 可以看成 T *[10], x是指向一维指针数组本身的指针
	// 这个数组本身是T类型的,可以存放T类型的地址
	for (int row = 0; row < n_rows; row++)
		x[row] = new T [n_cols]; // 指针可以使用[]索引,x[i]的类型是一个数的地址或者一个一维普通数组本身
	    // 其实就是一维普通数组索引的对应元素地址,这个地址可以指向一维数组本身也可以是特定值
	return true; // 分配成功
	}
	catch (bad_alloc){return false; }// 分配失败
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