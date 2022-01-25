#include <iostream>
#include "sort_method.h"
template<class T>
int binarySearch(T a[], int n, const T& x);
void _chapter3_binarySearch()
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
  // ���ֲ��ҵ�ǰ������������,�������������·���2��if������
	// ����������Ҫ��ִ�д����Ǧ�(logn),ÿ��whileѭ����ʱ��(1)
	int left = 0; // ���
	int right = n - 1; // �Ҷ�
	while (left <= right) // ��ȵ�ʱ��Ҳ��ִ��,middle=left=right
		// ֮��ִ��left=middle+1,left>left�˳�while������right=middle-1,right<left�˳�while
	{
		int middle = (left + right) / 2; 
		if (x == a[middle]) return middle; // �м�λ���ҵ��˾��˳�
		if (x > a[middle]) left = middle + 1; // û�ҵ��Ҳ��ҵ�Ԫ�ش����м�Ԫ��˵�����ҵ�x����������[middle+1,n-1]
		else right = middle - 1; // ����������[0,middle-1]
	}
	return -1; //û�ҵ�����-1
}