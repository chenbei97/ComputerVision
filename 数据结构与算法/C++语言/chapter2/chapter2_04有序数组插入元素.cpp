#include <iostream>
template<class T>
void insert_ordered_array(T a[], int& n, const T& x);
void _chapter2_best_worst_average_operation_count()
{
	// �����������Ԫ�ص�ʱ�临�Ӷ�Ϊn/2 + n/(n+1)
	// ��õ�ֻ��1�Σ�����ʱ����Ҫn�Σ�����Ԫ����a[0]��a[1]������n��
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
	int i; // ����forѭ���ڲ�����int i = n-1�ᱨ���޷�ʶ��i
	for (i = n - 1; i >= 0 && x < a[i]; i--)// x < a[i] i��n - 1��ʼ��0����
		a[i + 1] = a[i]; // ���x<a[i]˵��Ӧ����x����a[i],��a[i]ԭ��ֵ�ƶ���a[i+1]
	a[i + 1] = x; // ���x>a[i]ֱ����a[i+1]=x����,��Ҫע�����a�Ŀռ�Ҫ����n����a[i+1]Խ��
	n++;
	// i = n-1, a[n] = x ; �Ҳ�    i = 0 ʱx<a[0]��ôa[1]=a[0],Ȼ��i--��ִ��a[0]=x ���
	// ȡ������� һ��ʼ���Ҳ嵽a[i+1],��ô���ٱȽ�1�β�ִ�и�ֵ����
	// �����嵽a[1],��Ҫ��x<a[i]�Ƚϵ�x<a[1],Ҳ����i��,x<a[1]�����Ժ�Ҫ�Ƚ�һ��a[0]�Ž���ѭ��ʵ������i+1��
	// ������ÿ�δ�ѭ����������嵽a[i+1],a[i],..a[1]Ҫ�Ƚ�1,2,..,i+1�Σ�Ҳ����n(n+1)/2��
}