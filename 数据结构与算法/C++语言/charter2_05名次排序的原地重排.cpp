#include <iostream>
template<class T>
void swap_array_element1(T a[], T idx1, T idx2);
template<class T>
void situ_rearrangement(T a[], int n);
void _charter2_count_sort_situ_rearrangement()
{
	const int n = 10;
    int a[n] = { 6,5,8,4,3,1,13,0,66 ,-2};
	situ_rearrangement(a, n);
	for (int i = 0; i < n; i++)
		std::cout << "a[" << i << "] = " << a[i] << "   ";
	std::cout << std::endl;
}
template<class T>
void situ_rearrangement(T a[], int n)
{
	int count = 0;
	T* rank = new T[n]; // rank���ڵõ�����
	for (int i = 0; i < n; i++)
		rank[i] = 0; // ������ȫ����ʼ��Ϊ0
	for (int i = 1; i < n; i++)
		for (int j = 0; j < i; j++)
		{
			count++;
			if (a[j] <= a[i]) rank[i]++;
			else rank[j]++; // �õ�����
		}
	for (int i = 0; i < n; i++)
	{
		while (rank[i] != i) // ������κ�ʵ������˳����ͬ��i++�����һ��
		{
			int t = rank[i]; // ������κ�ʵ��˳�򲻵�,��¼����ָ����λ��
			swap_array_element1(a, i, t); // ���Ȱ�a�ĵ�ǰԪ�ؽ���������ָ����λ��
			swap_array_element1(rank, i, t);//a�����˱仯,����Ҳ�����˱仯,��rank[i]��rank[rank[i]]��������
			// rank��¼��������λ��,��ǰa[i]�ƶ���a[rank[i]]=a[t]
			// ��ǰrank[i]��ֵ��t=rank[i](ԭ������)Ӧ����ʵ������i����
		}
	}
	for (int i =0 ; i < n ; i++) // rank��˳���ɼ�������λָ�Ϊ˳������
		std::cout << "rank[" << i << "] = " << rank[i] << "   ";
	std::cout << std::endl;
	delete [] rank;
}
template<class T>
void swap_array_element1(T a[], T idx1, T idx2)
{
	T temp;
	temp = a[idx1];
	a[idx1] = a[idx2];
	a[idx2] = temp;
}