#include <iostream>
template<class T>
void insert_ordered_array1(T a[], int n, const T& x);
template<class T>
void rearrange_byinsert(T a[], int n, bool show = true);
void _charter2_insert_sort()
{
	// �������������Ԫ�صĻ����Ͻ���
	const int n = 6;
	int a[n] = { 3,0,4,5,2,1 };
	rearrange_byinsert(a, n);
}
template<class T>
void rearrange_byinsert(T a[], int n, bool show)
{
	// �����������Ԫ�أ���a[i](i=1,2,..n-1)��Ϊx���в���
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
	// nʵ�ʻ�ȡ1,2,..n-1�����ڲ�iȡ��Ϊ0,1,2..n-2
	int i=0; // ����forѭ���ڲ�����int i = n-1�ᱨ���޷�ʶ��i
	for (i = n - 1; i >= 0 && x < a[i]; i--) // x<a[i] i��n-1��ʼ��0����
		a[i + 1] = a[i]; // ���x<a[i]˵��Ӧ����x����a[i],��a[i]ԭ��ֵ�ƶ���a[i+1]
	a[i + 1] = x; // ���x>a[i]ֱ����a[i+1]=x����,��Ҫע�����a�Ŀռ�Ҫ����n����a[i+1]Խ��
	// i = n-1, a[n] = x ; �Ҳ�    i = 0 ʱx<a[0]��ôa[1]=a[0],Ȼ��i--��ִ��a[0]=x ���
	// ȡ������� һ��ʼ���Ҳ嵽a[i+1],��ô���ٱȽ�1�β�ִ�и�ֵ����
	// �����嵽a[1],��Ҫ��x<a[i]�Ƚϵ�x<a[1],Ҳ����i��,x<a[1]�����Ժ�Ҫ�Ƚ�һ��a[0]�Ž���ѭ��ʵ������i+1��
	// ������ÿ�δ�ѭ����������嵽a[i+1],a[i],..a[1]Ҫ�Ƚ�1,2,..,i+1�Σ�Ҳ����n(n+1)/2�Σ�����Ϊ��嵽a[0]��i+1�Σ�Ҳ����n-1+1�Σ�����ƽ������ʵ������[n(n+1)/2 + n]/(n+1)��
	// ��Ϊ�ⲿ���õ�ԭ������iֻ��ȡ��n-2�����Ը��Ӷ���[n(n-1)/2+n-1]/n��ʵ��һ����˼��
}
