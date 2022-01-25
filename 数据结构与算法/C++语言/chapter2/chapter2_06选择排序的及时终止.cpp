#include <iostream>
template<class T>
void select_sort_timely_termination(T a[] , int n);
void _chapter2_select_sort_timely_termination()
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
	bool sorted = false; // Ĭ������,����Ż����ѭ��
	for (int k = n; (k > 1) && !sorted; k--) // kȡn,n-1,..2=>iȡn-1,n-2,..,1
	{
		int idx = 0; // �Ƚ����Ǵӵ�1��Ԫ��a[1]��ʼ,a[0]Ĭ�ϳ�ʼ���ֵ
		sorted = true; // ����ѭ������ָ��Ϊ����,ѭ����ȥ�ж��Ƿ����ǰһ��Ԫ�ش��ں�һ��Ԫ��
		for (int i = 1; i < k; i++)
			if (a[idx] <= a[i]) idx = i; // ���ǰ��С�ں���˵�����������,����¼���ֵλ��
			else sorted = false; // �κδ�ѭ���м�[1,k-1]�д���ǰ�ߴ��ں��߾�˵������,���ĳ�δ�ѭ���Ѿ������������ٽ��к�����ѭ����ǰ��ֹ
		T temp = a[idx];
		a[idx] = a[k - 1];  // ���ǰ����ֵ����ÿ�δ�ѭ�������
		a[k - 1] = temp;
	}
}