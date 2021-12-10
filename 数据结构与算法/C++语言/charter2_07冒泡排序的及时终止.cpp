#include <iostream>
template<class T>
void bubble_sort_timely_termination(T a[], int n);
void _charter2_bubble_sort_timely_termination()
{
	const int n = 6;
	int a[n] = { 3,0,4,5,2,1 };
	bubble_sort_timely_termination(a, n);
	for (int i = 0; i < n; i++)
		printf("a[%d] = %d   ", i, a[i]);
}
template<class T>
void bubble_sort_timely_termination(T a[], int n)
{
	bool swapped =true; // 默认无序交换过
	for (int k = n; (k > 1) && swapped; k--) // 没有发生交换就提前终止,否则执行a[0]都a[k-1]之间的元素两两交换
	{
		swapped = false; // 进入循环立刻先视为有序 后面只有存在前者大于后者就置为true
		for (int i = 0; i < n - 1; i++)
			if (a[i] > a[i + 1]) // 如果前者元素大于后者就说明无序,此时交换发生swapped=true
			{
				T temp = a[i];
				a[i] = a[i + 1];
				a[i + 1] = temp;
				swapped = true;
			}
	}
}