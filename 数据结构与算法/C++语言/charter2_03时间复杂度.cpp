#include <iostream>
#include "assert.h"
template<class T1 ,class T2>
T1 polynomial_calculate_accumulate(T1 coeff[], int n , const T2 & x);

template<class T1, class T2>
T1 polynomial_calculate_hornor(T1 coeff[], int n, const T2& x);

int factorical1(int n);

template<class T>
int find_maxval_loc_in_array1(T a[], int n);

template<class T>
void rank_calculate(T a[] , int n , int r[] , bool show =true);

template<class T>
void rearrange_byrank(T[], int n, int r[], bool reverse = false, bool show = true);

template<class T>
void rearrange_byselect(T[], int n, bool show = true);

template<class T>
void swap_array_element(T a[] ,T idx1 , T idx2);

void _charter2_time_complexity()
{
	// 多项式计算
	const int n = 10; // 10阶方程
	double coeff[n+1] ; // 11个系数
	for (int i = 0; i < n+1; i++)
	{
		coeff[i] = 1 / (double)factorical1(i);// 得带小数点不然会出错
		std::cout << "coeff[" << i << "] = " << coeff[i] << std::endl;
	}
		
	double  x = (double)n;
	std::cout << "exp(x) = " << exp(x) << std::endl;
	double res1 = polynomial_calculate_accumulate(coeff, n, x);
	double res2 = polynomial_calculate_hornor(coeff, n, x);
	std ::cout <<"res1 = " << res1 << "    res2 = " << res2 << std::endl;

	// 名次计算
	/*
	​	外循环所在的元素和以前的元素都没有比较过，所以内循环就是让这个a[i]以前的元素都a[j]要和它进行比较，故j<i；如果这个元素比以前的一个元素大排名就要提升1，如果相等的元素因为是后出现的元素，排名依然+1。
		以5个元素数组举例，运行的程序实际上是a[0]&a[1] => 1次比较
		a[0]&a[2]、a[1]&a[2] => 2次比较
		a[0]&a[3]、a[1]&a[3]、a[2]&a[3] => 3次比较
		a[0]&a[4]、a[1]&a[4]、a[2]&a[4]、a[3]&a[4] => 4次比较
		....推广之
		a[0]&a[n-1]、a[1]&a[n-1]、a[2]&a[n-1]、a[3]&a[n-1]、...a[n-2]&a[n-1] => n-1次比较(因为n=0就无需比较,n-1已经是边界)
		总的比较次数为：1+2+3+...n-1 = n(n-1)/2
	*/
	int a1[6] = {4,3,9,3,7,11};
	int r1[6];
	rank_calculate(a1,6,r1);
	rearrange_byrank(a1,6,r1,true);
	
	// 选择排序
	// 交换函数测试
	swap_array_element(a1, 0, 5);
	std::cout << a1[0] << std::endl; // 3和11交换了
	int a2[7] = { 32,2,9,6,7,13 ,7};
	rearrange_byselect(a2,7);
}
template<class T>
void rearrange_byselect(T a[], int n,  bool show)
{
	// 选择排序是先找到元素最大的位置,然后将这个元素交换到数组的末尾或者开始
	// 找到这个最大值以后继续在前n-1个元素寻找,位置是[0,n-2]
	// 以此类推直到最后有2个元素数组[0,1],继续查找即可 1个元素时已经不必进行比较了
	for (int i = n; i > 1; i--)
	{
		// 前i个元素查找最大元素
		int idx = find_maxval_loc_in_array1(a, i); // 此函数的时间复杂度为i-1(比较i-1次)
		// 查找最大值索引的总的时间复杂度为(n-1)+(n-2)+...1=(n-1)n/2
		swap_array_element(a, idx, i - 1);//交换这个最大的元素到末尾位置
	}
	if (show)
		for (int i = 0; i < n; i++) std::cout << "a["<<i<<"] = "<<a[i] << std::endl;
}

template<class T>
void swap_array_element(T a[], T idx1, T idx2)
{
	T temp;
	temp = a[idx1];
	a[idx1] = a[idx2];
	a[idx2] = temp;
}



template<class T>
void rearrange_byrank(T a[], int n, int r[] , bool reverse , bool show)
{
	T* temp = new T[n]; // 一个指向动态数组本身的指针 temp[] 或者*temp++都可以访问数组元素
	for (int i = 0; i < n; i++)
	{
		temp[r[i]] = a[i]; // r[i]是a[i]被移动的新位置
	}
	if (! reverse) // reverse=false表示升序 从小到大
	{
		for (int i = 0; i < n; i++)
			a[i] = temp[i]; // 把这样的顺序放回原来的a
	}
	else
	{ // 降序
		for (int i = 0; i < n; i++)
			a[i] = temp[n-1 - i];
	}
	if (show)
	{
		for (int i = 0; i < n; i++)
			std::cout << "a[" << i << "] = " << a[i] << std::endl;
	}
	delete[] temp;
}
template<class T>
void rank_calculate(T a[], int n, int r[] ,bool show )
{
	// 输入的数组形式为a[0,n-1]
	int count = 0;
	for (int i = 0; i < n; i++)
		r[i] = 0; // 名次先全部初始化为0
	for (int i = 1; i < n; i++)
		for (int j = 0; j < i; j++)
		{
			count++;
			if (a[j] <= a[i]) r[i]++;
			else r[j]++;
		}
	assert(count == n * (n - 1) / 2);
	if (show)
	{
		for (int i = 0; i < n; i++)
			std::cout << "r[" << i << "] = " << r[i] << std::endl;
		std::cout << "count = " << count << std::endl;
	}	
}
template<class T1, class T2>
T1 polynomial_calculate_accumulate(T1 coeff[], int n, const T2& x)
{
	// 计算多项式y=c0+c1x+c2x^2+...cnx^n
	T1 x_n = 1; // x_n从n=0,1,2...  => 1,x,x^2,x^3,...
	T1 value = coeff[0]; // c0开始,c0+Σcnx_n
	for (int i = 1; i <= n; i++)
	{
		// 输入的数组形式为a[0,n]
		x_n *= x; // x,x^2,x^3,...
		//std::cout << "x_n = " << x_n<< std::endl;
		value += x_n * coeff[i]; // i从1开始直到n都计算
		//std::cout << "value = " << value <<std::endl;
	}
	return value;
}
template<class T1, class T2>
T1 polynomial_calculate_hornor(T1 coeff[], int n, const T2& x)
{
	// y(x) = (...(cn * x+cn-1) * x + cn-2 ) * x + cn-3 ) *...) * x + c0 
	T1 value = coeff[n];
	for (int i = 1; i <= n; i++)
	{
		// 输入的数组形式为a[0,n]
		value = value * x + coeff[n-i]; // 某次计算的结果整体value作为下次与x整体相乘
		std::cout << "value = " << value << std::endl;
	}
	return value;
}
int factorical1(int n)
{
	if (n <= 1) return 1;
	else return n * factorical1(n - 1);
}
template<class T>
int find_maxval_loc_in_array1(T a[], int n)
{
	if (n <= 0)
		throw("n must be > 0");
	int loc = 0; // 最大位置初始化为第1个元素的索引0
	for (int i = 1; i < n; i++)
	{
		if (a[loc] < a[i])
			loc = i; // 更新最大值索引位置
	}
	return loc;
}