#include <iostream>
#include "sort_method.h"
template<class T>
int binarySearch(T a[], int n, const T& x);
void _charter3_binarySearch()
{
	const int n = 5;
	int a[n] = {9,6,4,0,-2};
	bubble_sort(a,n,false,false);
	int idx = binarySearch(a, n, 9);
	printf("x loc is %d, x = %d", idx, a[idx]);
}
template<class T>
int binarySearch(T a[], int n, const T& x)
{
  // 二分查找的前提是有序数组,不是有序数组下方的2个if不成立
	// 最坏的情况下需要的执行次数是Θ(logn),每次while循环耗时Θ(1)
	int left = 0; // 左端
	int right = n - 1; // 右端
	while (left <= right) // 相等的时候也会执行,middle=left=right
		// 之后执行left=middle+1,left>left退出while，还是right=middle-1,right<left退出while
	{
		int middle = (left + right) / 2; 
		if (x == a[middle]) return middle; // 中间位置找到了就退出
		if (x > a[middle]) left = middle + 1; // 没找到且查找的元素大于中间元素说明查找的x在右子区间[middle+1,n-1]
		else right = middle - 1; // 否则区间在[0,middle-1]
	}
	return -1; //没找到返回-1
}