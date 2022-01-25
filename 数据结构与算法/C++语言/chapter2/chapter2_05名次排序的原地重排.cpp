#include <iostream>
/*
| i/实际位置 | 0    | 1    | 2    | 3    | 4    | 5    |
| ---------- | ---- | ---- | ---- | ---- | ---- | ---- |
| r/名次     | 3    | 0    | 4    | 5    | 2    | 1    |
| a/数组     | d    | a    | e    | f    | c    | b    |
​	(1) i = 0
​		①开始执行i=0，r[0]=3≠i,所以实际位置和名次不符合，需要执行交换操作
​		交换a[0]和a[r[0]]=a[3]，然后交换r[0]=3和r[r[0]]=5，此时表格如下所示，加粗的为交换的2个元素。
​		**5** 0 4 **3** 2 1
​		**f** a e **d** c b
​		推广可以知道交换的位置是**<u>a[i]和a[rank[i]]</u>**，a中决定了交换的位置是i和rank[i]，所以名次也要更新，**<u>rank[i]和rank[rank[i]]</u>**		进行交换。其目的是将rank的那些名次按照顺序重排，那么a也随之有序。
​		②继续判定r[0]是否等于i=0，此时r[0]=5≠i=0，继续交换操作。交换a[0]和a[r[0]]=a[5]，并交换r[0]和r[r[0]]=r[5]。
​		**1** 0 4 3 2 **5**
​		b** a e d c **f**
​		③继续判定r[0]与i，仍然不相等，执行a[0]与a[r[0]]=a[2]交换，并交换r[0]与r[r[0]]。
​		**0** **1** 4 3 2 5
​		**a** **b** e d c f
​		此时判定发现r[0]和i=0是相同的，由此可以看到**<u>对计算出的名次排序好，就等同于对原数组排序好</u>**。
​	(2) i = 1
​		r[0]和i=0相同后，i到下一个位置，这说明第0个元素已经排好不必再进行比较，只需要对后边的n-1个元素排好即可，这里n=6。
​		比较r[1]和i=1是否相等？r[1]=1相等，所以i继续增1，**<u>推广每次i增加比较的都是r[i]与i，这也是while循环的条件</u>**。
​		x x 4 3 2 5
​		x x e d b f
​	(3) i = 2
​		r[2]=4和i=2不等，所以交换a[2]与a[r[2]]=a[4]，r[2]与r[4]。
​		x x **2** 3 **4** 5
​		x x **b** d **e** f
​		此时r[2]=2=i=2，i++。
​		x x x 3 **4** 5
​		x x x d **e** f
​	(4) 此时可以看出r[3]=i=3,r[4]=i=4,r[5]=i=5，后面已经有序不必再进行交换。
*/
template<class T>
void swap_array_element1(T a[], T idx1, T idx2);
template<class T>
void situ_rearrangement(T a[], int n);
void _chapter2_count_sort_situ_rearrangement()
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