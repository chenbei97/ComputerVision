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
	T* rank = new T[n]; // rank用于得到名次
	for (int i = 0; i < n; i++)
		rank[i] = 0; // 名次先全部初始化为0
	for (int i = 1; i < n; i++)
		for (int j = 0; j < i; j++)
		{
			count++;
			if (a[j] <= a[i]) rank[i]++;
			else rank[j]++; // 得到名次
		}
	for (int i = 0; i < n; i++)
	{
		while (rank[i] != i) // 如果名次和实际索引顺序相同则i++检测下一轮
		{
			int t = rank[i]; // 如果名次和实际顺序不等,记录名次指定的位置
			swap_array_element1(a, i, t); // 首先把a的当前元素交换到名次指定的位置
			swap_array_element1(rank, i, t);//a发生了变化,名次也发生了变化,让rank[i]和rank[rank[i]]交换即可
			// rank记录的是名次位置,当前a[i]移动到a[rank[i]]=a[t]
			// 当前rank[i]的值是t=rank[i](原有名次)应当和实际索引i交换
		}
	}
	for (int i =0 ; i < n ; i++) // rank的顺序由计算的名次恢复为顺序名次
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