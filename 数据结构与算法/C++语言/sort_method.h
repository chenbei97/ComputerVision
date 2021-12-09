#pragma once
#include <iostream>
#include <assert.h>
enum sortMethods { countSort, selectSort, bubbleSort };
template<class T>
void array_sorting_method(T a[], int n, int method , bool reverse = false , bool show =true); // ģ�庯������������ʵ�ֶ���һ���ļ��з������Ӵ���

template<class T>
void count_sort(T a[], int n, bool reverse , bool show );

template<class T>
void select_sort(T a[], int n, bool reverse , bool show );

template<class T>
void bubble_sort(T a[], int n, bool reverse, bool show);

template<class T>
void array_sorting_method(T a[], int n, int method , bool reverse , bool show)
{
	if (method == countSort)
		count_sort(a, n, reverse, show);
	else if (method == selectSort)
		select_sort(a, n, reverse, show);
	else if (method == bubbleSort)
		bubble_sort(a, n, reverse, show);

}

template<class T>
void bubble_sort(T a[], int n, bool reverse, bool show)
{
	for (int i = n; i > 1; i--) // i = n,n-1,...2(��n-1��)
	{
		if (!reverse)
		{
			for (int j = 0; j < i - 1; j++) // j = 0,1,..i-2=n-2 (��n-1��) a[j+1]���Ϊa[n-1]û��Խ��
			{
				//printf("i = %d   j = %d\n", i ,j);
				if (a[j] > a[j + 1]) // ǰ�߱Ⱥ��ߴ��ǰ��(���)��������=>����
				{
					T temp = a[j];
					a[j] = a[j + 1];
					a[j + 1] = temp;
				}
			}
			if (show)
			{
				for (int i = 0; i < n; i++) // չʾһ��ð�ݵĹ���
					std::cout << "a[" << i << "] = " << a[i] << "   ";
				std::cout << std::endl;
			}
		}
		else 
		{ // �Ƚ�����Ԫ��ʱ���԰�С�Ļ�������ʵ�ֽ��򲻱���ѡ�����������鷳
			for (int j = 1; j < i;j++)  // jȡ1,2,3,..n-1,j-1ȡ0,1,2..,n-2
				if (a[j - 1] < a[j]) // ǰ�߱Ⱥ���С�Ѻ���(���)����ǰ��=>����
				{
					T temp = a[j-1];
					a[j-1] = a[j];
					a[j] = temp;
				}
			if (show)
			{
				for (int i = 0; i < n; i++) // չʾһ��ð�ݵĹ���
					std::cout << "a[" << i << "] = " << a[i] << "   ";
				std::cout << std::endl;
			}
		}
	}
}

template<class T>
void select_sort(T a[], int n, bool reverse , bool show )
{
	// ��������������[0,n-1],[0,n-2],...[0,1]Ѱ�����ֵ����,Ȼ������ֵ����ĩβ
	// ��������������[0,n-1],[1,n-1],[2,n-1],...[n-2,n-1]Ѱ�����ֵ����, Ȼ������ֵ���ڿ�ͷj��λ��
	// ����ʱj��������[1,2],[1,3],[1,4],...,[1,i](i=n-1����) ��maxLoc=0,��1��ʼ��Ϊ���ٱ�һ�� , j ��n-1����j<=i or j < i+1
	// ����ʱj��������[i-1,n-2],...,[n-4,n-2],[n-3.n-2](i=1��ʼ) ��maxLoc=n-1,��n-2������Ϊ���ٱ�һ��, j<=n-2 or j <n-1
	// ����д��һ��ѭ����,i��n-1,n-2,...,1�仯j��0,2..n-2�仯,��ϵ����i+j=n-1,����j=n-1-i��ʼ ��ʼ��λ�þ������ֵ��ŵ�λ��
	
	for (int i = n-1; i > 0; i--) //   i��λ��n-1��ʼ , ����ȡ��1
	{
		int maxLoc ; 
		T temp;
		if (!reverse)
		{
			maxLoc = 0;// �Ƚ���һ��Ԫ����Ϊ�����ֵ������
			// iȡn-1ʱjҪȡ�Ⱥŷ�ֹjȡ������jҪ��1��ʼ������һ��a[0]��a[0]�Ƚ�
			for (int j = 1; j <i+1; j++) // ��Ϊ j <=n-1 , ��j <=i or j<i+1
			{
				if (a[j] > a[maxLoc]) // j <= n- 1��֤��Խ��
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
			// Ҫ��j��n-1-i��ʼֱ��n-2��ÿ��С���鶼��Ϊn-1������Ȼ����бȽ�
			for (int j = n-1-i ; j < n-1; j++) // j<=n-2 or j <n-1 i=1ʱj=n-2
			{
				if (a[j] > a[maxLoc])  // 
					maxLoc = j; // j��ȡ��1~n-1
			}
			temp = a[n-1-i]; // ÿ��iѭ����ͷλ��Ӧ����j��λ��Ҳ����n-1-i
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
	T* rank = new T[n]; // rank���ڵõ�����
	for (int i = 0; i < n; i++)
		rank[i] = 0; // ������ȫ����ʼ��Ϊ0
	for (int i = 1; i < n; i++)
		for (int j = 0; j < i; j++)
		{
			count++;
			if (a[j] <= a[i]) rank[i]++;
			else rank[j]++;
		}
	assert(count == n * (n - 1) / 2);
	T* temp = new T[n]; // temp���ڴ������������
	for (int i = 0; i < n; i++)
	{
		temp[rank[i]] = a[i]; // rank[i]��a[i]���ƶ�����λ��
	}
	
	if (!reverse) // reverse=false��ʾ���� ��С����
	{
		if (show)
		{
			for (int i = 0; i < n; i++)
				std::cout << "before =>  a[" << i << "] = " << a[i] << "   new index = " << rank[i] << "   after =>  temp[" << rank[i] << "] = a["<<i<<"] = " << temp[rank[i]] << std::endl;
		}
		for (int i = 0; i < n; i++)
			a[i] = temp[i]; // ��������˳��Ż�ԭ����a
	}
	else
	{ // ����
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
