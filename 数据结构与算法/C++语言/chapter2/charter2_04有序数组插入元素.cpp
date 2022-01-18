#include <iostream>
template<class T>
void insert_ordered_array(T a[], int& n, const T& x);
void _charter2_best_worst_average_operation_count()
{
	// 有序数组插入元素的时间复杂度为n/2 + n/(n+1)
	// 最好的只需1次，最差的时候需要n次，插入元素在a[0]和a[1]处都是n次
	const int n = 5;
	int n1 = n;
	int a[n+1] = { 1,3,5,7,9 };
	int x = 0;
	insert_ordered_array(a, n1, x);
	std::cout << "n = " << n1 << std::endl;
	for (int i = 0; i < n; i++)
	{
		printf("a[%d] = %d ", i, a[i]);
	}
}
template<class T>
void insert_ordered_array(T a[], int& n, const T& x)
{
	int i; // 不能for循环内部定义int i = n-1会报错无法识别i
	for (i = n - 1; i >= 0 && x < a[i]; i--)// x < a[i] i从n - 1开始到0结束
		a[i + 1] = a[i]; // 如果x<a[i]说明应当把x赋给a[i],而a[i]原有值移动到a[i+1]
	a[i + 1] = x; // 如果x>a[i]直接令a[i+1]=x即可,需要注意的是a的空间要大于n否则a[i+1]越界
	n++;
	// i = n-1, a[n] = x ; 右插    i = 0 时x<a[0]那么a[1]=a[0],然后i--，执行a[0]=x 左插
	// 取特殊情况 一开始就右插到a[i+1],那么至少比较1次不执行赋值交换
	// 如果左插到a[1],需要从x<a[i]比较到x<a[1],也就是i次,x<a[1]比完以后还要比较一次a[0]才结束循环实际上是i+1次
	// 故最坏情况每次大循环都依次左插到a[i+1],a[i],..a[1]要比较1,2,..,i+1次，也就是n(n+1)/2次
}