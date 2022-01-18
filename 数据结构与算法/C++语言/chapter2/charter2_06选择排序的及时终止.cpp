#include <iostream>
template<class T>
void select_sort_timely_termination(T a[] , int n);
void _charter2_select_sort_timely_termination()
{
	const int n = 6;
	int a[n] = { 3,0,4,5,2,1 };
	select_sort_timely_termination(a, n);
	for (int i = 0; i < n; i++)
		printf("a[%d] = %d   ", i, a[i]);
}
template<class T>
void select_sort_timely_termination(T a[], int n)
{
	bool sorted = false; // 默认无序,无序才会进入循环
	for (int k = n; (k > 1) && !sorted; k--) // k取n,n-1,..2=>i取n-1,n-2,..,1
	{
		int idx = 0; // 比较总是从第1个元素a[1]开始,a[0]默认初始最大值
		sorted = true; // 进入循环立刻指定为有序,循环中去判断是否存在前一个元素大于后一个元素
		for (int i = 1; i < k; i++)
			if (a[idx] <= a[i]) idx = i; // 如果前者小于后者说明还是有序的,并记录最大值位置
			else sorted = false; // 任何大循环中即[1,k-1]中存在前者大于后者就说明无序,如果某次大循环已经发现有序则不再进行后续大循环提前终止
		T temp = a[idx];
		a[idx] = a[k - 1];  // 总是把最大值放在每次大循环的最后
		a[k - 1] = temp;
	}
}