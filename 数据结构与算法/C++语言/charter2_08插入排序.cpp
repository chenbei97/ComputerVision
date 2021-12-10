#include <iostream>
template<class T>
void insert_ordered_array1(T a[], int n, const T& x);
template<class T>
void rearrange_byinsert(T a[], int n, bool show = true);
void _charter2_insert_sort()
{
	// 在有序数组插入元素的基础上进行
	const int n = 6;
	int a[n] = { 3,0,4,5,2,1 };
	rearrange_byinsert(a, n);
}
template<class T>
void rearrange_byinsert(T a[], int n, bool show)
{
	// 有序数组插入元素，将a[i](i=1,2,..n-1)作为x进行插入
	for (int i = 1; i < n; i++)
	{
		T t = a[i];
		insert_ordered_array1(a, i, t);
	}
	if (show)
		for (int i = 0; i < n; i++)
			printf("a[%d] = %d   ", i, a[i]);
}
template<class T>
void insert_ordered_array1(T a[], int n, const T& x)
{
	// n实际会取1,2,..n-1，故内部i取的为0,1,2..n-2
	int i=0; // 不能for循环内部定义int i = n-1会报错无法识别i
	for (i = n - 1; i >= 0 && x < a[i]; i--) // x<a[i] i从n-1开始到0结束
		a[i + 1] = a[i]; // 如果x<a[i]说明应当把x赋给a[i],而a[i]原有值移动到a[i+1]
	a[i + 1] = x; // 如果x>a[i]直接令a[i+1]=x即可,需要注意的是a的空间要大于n否则a[i+1]越界
	// i = n-1, a[n] = x ; 右插    i = 0 时x<a[0]那么a[1]=a[0],然后i--，执行a[0]=x 左插
	// 取特殊情况 一开始就右插到a[i+1],那么至少比较1次不执行赋值交换
	// 如果左插到a[1],需要从x<a[i]比较到x<a[1],也就是i次,x<a[1]比完以后还要比较一次a[0]才结束循环实际上是i+1次
	// 故最坏情况每次大循环都依次左插到a[i+1],a[i],..a[1]要比较1,2,..,i+1次，也就是n(n+1)/2次，又因为左插到a[0]是i+1次，也即是n-1+1次，所以平均次数实际上是[n(n+1)/2 + n]/(n+1)次
    	// 因为外部调用的原因这里i只能取到n-2，所以复杂度是[n(n-1)/2+n-1]/n其实是一个意思。
}
