#include <iostream>
template<class T>
void insert_ordered_array(T a[], int& n, const T& x);
void _charter2_best_worst_average_operation_count()
{
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
	int i; // ������ѭ����߶���int i=0,��Ϊ����ִ��һ��a[i+1]=x
	for (i = n - 1; i >= 0 && x < a[i]; i--)
		a[i + 1] = a[i]; // ��Ȼiû�г�ʼ������ִ����forѭ����i��ֵΪ-1
	a[i + 1] = x; // ���뿪ͷʱi=-1,��ִ��a[0]=x
	n++;
}