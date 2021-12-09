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
	int i; // 不能在循环里边定义int i=0,因为至少执行一次a[i+1]=x
	for (i = n - 1; i >= 0 && x < a[i]; i--)
		a[i + 1] = a[i]; // 虽然i没有初始化但是执行完for循环后i的值为-1
	a[i + 1] = x; // 插入开头时i=-1,才执行a[0]=x
	n++;
}
