#include <iostream>
#include <assert.h>
template<class T >
void sequentialSearch_analytic(T a[], int n, const T& x);
template<class T >
void insert_analytic(T a[], int &n, const T& x);
void _charter2_analytic_best_worst_mean_steps()
{
	const int n = 5;
	int a[n] = { 0,1,2,3,4 };
	int x = 0;
	sequentialSearch_analytic(a, n, x);// 最好情况比较4次
	x = a[n - 1]; 
	printf("\n");
	sequentialSearch_analytic(a, n, x); //最好情况比较n+3次
	x = 6;
	printf("\n");
	sequentialSearch_analytic(a, n, x); //没找到也是n+3次
	// 可以知道,假定一定能查找成功100%时如果数组每个元素不同且认为x与任何元素相等的概率一样
	// 那么就可以认为平均查找的成功概率为(n+7)/2
	// 但是可能存在不成功查找的情况此时执行步数为n+3,假定能够成功查找概率0.8
	// 则真实的概率为0.8(n+7)/2+0.2(n+3)=0.6n+3.4
	int n1 = 5;
	int b[6] = { 0,1,2,3,4};
	printf("\n");
	insert_analytic(b, n1, x); // 最好的情况直接右插共计4次
	int n2 = 5; // 用新的n2,n1增1了
	int c[6] = { 0,1,2,3,4 }; // 用新的数组,因为b的容量+1了
	x = -1;
	printf("\n");
	insert_analytic(c, n2, x);// 最坏的情况左插共计2*5+4次
}
template<class T >
void sequentialSearch_analytic(T a[], int n, const T& x)
{
	int step = 0;
	int i; step++;
	for (i = 0; i < n && a[i] != x; i++)
		step++; // for循环比较1次
	step++; // 终止for循环1次
	step++;// if无论查找成功都会判断1次
	if (i == n)   printf("x is not exist");// if判断1次,语句执不执行不影响这1次
	else { step++; printf("x_idx = %d", i); }// 查找成功执行1次失败0次
	
	printf("\nstep = %d", step);
	if (a[0] == x)
		assert(step == 4); // 最好的情况定义1次,for比较1次,if判断1次,找到了这个值返回1次,共计4次
	else if (a[n - 1] == x)
		assert(step == n + 3); // 最坏的情况比较了n次还没找到
}
template<class T >
void insert_analytic(T a[], int& n, const T& x)
{
	int step = 0;
	int i; step++; // 1次
	for (i = n - 1; i >= 0 && x < a[i]; i--)
	{
		step++; // 进入for循环比较i+1次 i=0,1,2,...n-1
		a[i + 1] = a[i]; // 赋值i+1次 i=0,1,2,...n-1
		step++;// 赋值i+1次
		// 一次for循环执行2(i+1)次
	}
	step++;// 终止for循环1次
	a[i + 1] = x; step++;
	n++; step ++ ;
	for (int i = 0; i < n ; i++) // 还是<n,因为n++了
		printf("a[%d] = %d  ", i, a[i]);
	printf("\nstep = %d", step);
	if (a[0] == x)
		assert(step == 2*(n-1)+4); // 最坏的情况for循环比较执行(n+1)次赋值n次,外部4次共计左插2n+4次,这里n++了所以需要减一下
	else if (a[n - 1] == x)
		assert(step == 4); // 最好的情况右插不进入for循环但是需要终止1次故1+1+1+1执行4次
	
	// 插入a[n]需要4次
	// 正常下1个数插入某个位置应当为for循环内部比较(i+1)次赋值i+1次共2i+2次,外部执行4次
	// 插入a[0]时取i=n-1,(2n-2+2)=2n次,外部执行4次;插入a[n-1]取i=0,需要2次,外部执行4次;
	// 从a[0]到a[n-1]有n个可能所以外部累计4n次,内部是2n+2(n-1)+...+2=n(n+1)次
	// 再算上右插没有for循环的次数4,总的次数为n^2+5n+4=(n+4)(n+1)，平均次数=n+4
}