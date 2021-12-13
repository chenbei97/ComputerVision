#include <iostream>
#include <assert.h>
template<class T>
void accumulate_analytic(T src[], T dst[], int n);
template<class T>
void matrix_transpose_analytic(T** a, int n, bool show = true);
void _charter2_analytic_method_steps()
{
	const int n = 4; // 必须是方阵
	int a1[n] = { 1,2,3,0 };
	int a2[n] = { 4,5,6,10 };
	int a3[n] = { 7,8,9,11 };
	int a4[n] = { 12,13,14,15 };
	// 元素是每个数组首元素的首地址,a1=&a1[0]所以这么赋值也可以

	int* a[n] = { a1,a2,a3,a4 };  // 一维指针数组
	int** pa = a;
	int step = 0;
	matrix_transpose_analytic(a, n); // a可以
	printf("\n");
	matrix_transpose_analytic(pa, n); // pa也可以
	int b[5] = { 1,2,3,4,5 };
	int c[5] = {};
	printf("\n");
	accumulate_analytic(b, c, 5);
}
template<class T>
void matrix_transpose_analytic(T** a, int n, bool show)
{
	// **指针是指向一维指针数组本身的指针可以访问数组元素
	int step = 0;
	for (int i = 0; i < n; i++) // 需要n+1次比较,决定第2个for循环比较次数,i=0,执行3次,因为终止循环算1次
	{
		step += 1;
		for (int j = i + 1; j < n; j++) // 需要Σ(n-i)次比较,n=3时=3+2+1+0=6次比较
		{
			// 内部for循环真正只执行了n-i-1次
			step += 2; // 执行依赖于i的n次交换,这里是计算交换次数和比较次数
			T temp = a[i][j]; // a[0][1],a[0][2],...,a[0][n-1]<=>a[1,0],a[2,0],...,a[n-1,0]每次交换就减少了1行1列
			a[i][j] = a[j][i];// a[1][2],a[1][3],...,a[1][n-1]<=>a[2,1],a[3,1],...,a[n-1,1]
			a[j][i] = temp; // a[i][j]的i控制每行不变,列变化,a[j][i]的j控制每行变化,列不变
		}
		step += 1; // 终止第2个for循环还需1次
	}
	step += 1; // 终止第1个for循环还需1次
	assert(step == n * n + n + 1); // 时间复杂度为n^2+n+1
	if (show)
	{
		for (int row = 0; row < n; row++)
		{
			int* rowp = a[row]; // 行指针
			for (int col = 0; col < n; col++)
				printf("a[%d][%d] = %d   ", row, col, rowp[col]);
		}
		printf("\nstep = %d", step);
	}

}
template<class T>
void accumulate_analytic(T src[], T dst[], int n)
{
	int step = 0;
	T res = 0; step++; // 1次
	for (int j = 0; j < n; j++) //执行n+1次
	{
		step++; // 比较j与n的大小为n次
		dst[j] = res += src[j]; step += 2;// 2次赋值操作
		printf("dst[%d] = %d   ", j, dst[j]);
	}
	step++; // 终止for循环需要1次,总计1+n+2n+1=3n+2次
	assert(step == 3 * n + 2);
	printf("\nstep = %d", step);
	// 5->17,4->14

}