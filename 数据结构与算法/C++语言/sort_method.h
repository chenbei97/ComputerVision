#pragma once
#include <iostream>
#include <assert.h>
enum sortMethods { countSort, selectSort, bubbleSort,insertSort};
template<class T>
void array_sorting_method(T a[], int n, int method , bool reverse = false , bool show =true); // 模板函数必须声明和实现都在一个文件中否则报链接错误

template<class T>
void count_sort(T a[], int n, bool reverse , bool show );

template<class T>
void select_sort(T a[], int n, bool reverse , bool show );

template<class T>
void bubble_sort(T a[], int n, bool reverse, bool show);

template<class T>
void insert_sort(T a[], int n, bool reverse, bool show);

template<class T>
void array_sorting_method(T a[], int n, int method , bool reverse , bool show)
{
	if (method == countSort)
		count_sort(a, n, reverse, show);
	else if (method == selectSort)
		select_sort(a, n, reverse, show);
	else if (method == bubbleSort)
		bubble_sort(a, n, reverse, show);
	else if (method == insertSort)
		insert_sort(a, n, reverse, show);

}
template<class T>
void insert_sort(T a[], int n, bool reverse, bool show)
{
	for (int i = 1; i < n; i++) // a[i]作为x, 从i=1直到n-1
	{
		T x = a[i]; // 后1个元素
		int j = 0;
		for (j = i - 1; j >= 0 && x < a[j]; j--) // i-1开始是前一个元素
			a[j+1] = a[j]; // i=1=>如果a[1]<a[0],把a[0]换到a[1]的位置上即a[1]=a[0]
		a[j + 1] = x;// i=1=>a[0]的位置要放原来的a[1]位置,因为a[0]>a[1]要交换
		//推广=>a[i]<a[j]=a[i-1],a[i]的位置应当放置a[i-1]即a[i]=a[i-1]<=>a[j+1]<a[j],然后再把原来a[i-1]放a[i]，即a[j+1]=x
		// 如果a[i]>a[j]也就无须执行交换了
		// 不可以用i去控制,i控制a[i],a[i]=a[j]会导致外循环出现错误
	}
	if (reverse)
	{
		for (int i = 0; i < n / 2; i++) 
		{ //奇数也没问题
			T t = a[i];
			a[i] = a[n - 1 - i];//n=10, a[4] = a[10-1-4]=a[5](偶数) 不会取到a[5]=a[4]
			a[n - 1 - i] = t; // n=5 a[0]=a[4],a[1]=a[2],会取到a[2]=a[2]不影响结果
		}
	}
	if (show)
		for (int i = 0; i < n; i++)
			printf("a[%d] = %d   ", i, a[i]);
}

template<class T>
void bubble_sort(T a[], int n, bool reverse, bool show)
{
	for (int i = n; i > 1; i--) // i = n,n-1,...2(共n-1次)
	{
		if (!reverse)
		{
			for (int j = 0; j < i - 1; j++) // j = 0,1,..i-2=n-2 (共n-1次) a[j+1]最大为a[n-1]没有越界
			{
				//printf("i = %d   j = %d\n", i ,j);
				if (a[j] > a[j + 1]) // 前者比后者大把前者(大的)换到后面=>升序
				{
					T temp = a[j];
					a[j] = a[j + 1];
					a[j + 1] = temp;
				}
			}
			if (show)
			{
				for (int i = 0; i < n; i++) // 展示一次冒泡的过程
					std::cout << "a[" << i << "] = " << a[i] << "   ";
				std::cout << std::endl;
			}
		}
		else 
		{ // 比较相邻元素时可以把小的换到后面实现降序不必像选择排序那样麻烦
			for (int j = 1; j < i;j++)  // j取1,2,3,..n-1,j-1取0,1,2..,n-2
				if (a[j - 1] < a[j]) // 前者比后者小把后者(大的)换到前边=>降序
				{
					T temp = a[j-1];
					a[j-1] = a[j];
					a[j] = temp;
				}
			if (show)
			{
				for (int i = 0; i < n; i++) // 展示一次冒泡的过程
					std::cout << "a[" << i << "] = " << a[i] << "   ";
				std::cout << std::endl;
			}
		}
	}
}

template<class T>
void select_sort(T a[], int n, bool reverse , bool show )
{
	// 升序：依次在区间[0,n-1],[0,n-2],...[0,1]寻找最大值索引,然后把最大值放在末尾
	// 降序：依次在区间[0,n-1],[1,n-1],[2,n-1],...[n-2,n-1]寻找最大值索引, 然后把最大值放在开头j的位置
	// 升序时j的区间是[1,2],[1,3],[1,4],...,[1,i](i=n-1结束) 令maxLoc=0,从1开始是为了少比一次 , j ≤n-1所以j<=i or j < i+1
	// 降序时j的区间是[i-1,n-2],...,[n-4,n-2],[n-3.n-2](i=1开始) 令maxLoc=n-1,到n-2结束是为了少比一次, j<=n-2 or j <n-1
	// 降序写在一个循环里,i从n-1,n-2,...,1变化j从0,2..n-2变化,关系满足i+j=n-1,所以j=n-1-i开始 开始的位置就是最大值存放的位置
	
	for (int i = n-1; i > 0; i--) //   i从位置n-1开始 , 可以取到1
	{
		int maxLoc ; 
		T temp;
		if (!reverse)
		{
			maxLoc = 0;// 先将第一个元素认为是最大值的索引
			// i取n-1时j要取等号防止j取不到，j要从1开始可以少一次a[0]和a[0]比较
			for (int j = 1; j <i+1; j++) // 因为 j <=n-1 , 故j <=i or j<i+1
			{
				if (a[j] > a[maxLoc]) // j <= n- 1保证不越界
					maxLoc = j;
			}
			temp = a[i]; 
			a[i] = a[maxLoc];
			a[maxLoc] = temp;
			if (show)
			{
				for (int i = 0; i < n; i++)
					std::cout << "a[" << i << "] = " << a[i] << "   ";
				std::cout << std::endl;
			}
		}
		else
		{
			// [0, n - 1] , [1, n - 1], [2, n - 1], ...[n - 2, n - 1] j = 0,1,2,...n-2
			maxLoc = n - 1;
			// 要求j从n-1-i开始直到n-2，每个小数组都认为n-1是最大的然后进行比较
			for (int j = n-1-i ; j < n-1; j++) // j<=n-2 or j <n-1 i=1时j=n-2
			{
				if (a[j] > a[maxLoc])  // 
					maxLoc = j; // j可取到1~n-1
			}
			temp = a[n-1-i]; // 每次i循环开头位置应当是j的位置也就是n-1-i
			a[n - 1 - i] = a[maxLoc];
			a[maxLoc] = temp;
			if (show)
			{
				for (int i = 0; i < n; i++)
					std::cout << "a[" << i << "] = " << a[i] << "   ";
				std::cout << std::endl;
			}
		}
	}

}

template<class T>
void count_sort(T a[], int n, bool reverse, bool show)
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
			else rank[j]++;
		}
	assert(count == n * (n - 1) / 2);
	T* temp = new T[n]; // temp用于存放排序后的数组
	for (int i = 0; i < n; i++)
	{
		temp[rank[i]] = a[i]; // rank[i]是a[i]被移动的新位置
	}
	
	if (!reverse) // reverse=false表示升序 从小到大
	{
		if (show)
		{
			for (int i = 0; i < n; i++)
				std::cout << "before =>  a[" << i << "] = " << a[i] << "   new index = " << rank[i] << "   after =>  temp[" << rank[i] << "] = a["<<i<<"] = " << temp[rank[i]] << std::endl;
		}
		for (int i = 0; i < n; i++)
			a[i] = temp[i]; // 把这样的顺序放回原来的a
	}
	else
	{ // 降序
		if (show)
		{
			for (int i = 0; i < n; i++)
				std::cout << "before =>  a[" << i << "] = " << a[i] << "   new index = " << rank[i] << "   after =>  temp[" << rank[i] << "] = a[" << i << "] = " << temp[rank[i]] << std::endl;
		}
		for (int i = 0; i < n; i++)
			a[i] = temp[n - 1 - i];
	}
	if (show)
	{
		for (int i = 0; i < n; i++)
			std::cout << "a[" << i << "] = " << a[i] << "   ";
		std::cout << std::endl;
	}

	delete[] temp;
	delete[] rank;
}
