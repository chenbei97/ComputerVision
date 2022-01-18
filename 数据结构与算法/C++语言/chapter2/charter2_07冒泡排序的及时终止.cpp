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
	bool swapped =true; // Ĭ�����򽻻���
	for (int k = n; (k > 1) && swapped; k--) // û�з�����������ǰ��ֹ,����ִ��a[0]��a[k-1]֮���Ԫ����������
	{
		swapped = false; // ����ѭ����������Ϊ���� ����ֻ�д���ǰ�ߴ��ں��߾���Ϊtrue
		for (int i = 0; i < n - 1; i++)
			if (a[i] > a[i + 1]) // ���ǰ��Ԫ�ش��ں��߾�˵������,��ʱ��������swapped=true
			{
				T temp = a[i];
				a[i] = a[i + 1];
				a[i + 1] = temp;
				swapped = true;
			}
	}
}