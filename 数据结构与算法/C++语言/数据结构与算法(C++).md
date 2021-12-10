## 1.C++回顾

​	前言部分和第一章的大部分内容不再详细说明，只从第一章的末尾测试与调试开始

### 1.1测试的概念

​	何谓测试？测试的目的是为了检测程序的错误而非正确，测试数据的不同对程序的正确性的检验有很大的影响。

​	测试有2种方法，一种是已知期望的结果，然后比对程序运行的结果；一种是程序运行的结果是否满足另一个必须满足的条件。例如以解二次方程x^2-5x+6=0为例，第一种方法是期望的结果为2、3，检验是否成立；第二种方法是通过公式计算出来结果后，带入检验方程是否等于0的强条件。

​	测试至少要求实现语句覆盖，对一个指定长度n的数组排序还要检验特殊情形，如n=0,1或者<0的情况，如果有边界n=100，也要测试n=100的情况。

### 1.2测试数据的设计

​	测试数据如何设计呢？主要有2种方法，黑盒测试法和白盒测试法。

​	前者考察的是程序功能，满足功能即认为正确，但是代码未必是正确的，可能是以某种方式恰好符合了这样的期望结果。最常用的黑盒法是I/O分类和因果图，这里只讨论I/O分类。以二次方程求解为例，任意方程的输出结果无非3种情况：不相等的实数根、相等的实数根以及共轭的复数根。那么测试数据至少就应当包含这3类情况的每一种，例如某组测试数据为二次方程系数的三元数组(a,b,c) = {(1,-5,6),(1,-8,16),(1,2,5)}对应的解分别是实数根2、3，实数根4、4，复数根-1±2i，就可以覆盖以上的所有情况。

​	后者考察的是程序代码，测试数据必须能够全面覆盖所有程序。覆盖包括**<u>语句覆盖和分支覆盖</u>**，语句覆盖是所有代码都可以执行一次；分支覆盖是所有条件判断都可以取到true或者false执行一次。

​	对分支覆盖进行加强还可称为**<u>从句覆盖</u>**，即要求每个条件的从句都要出现true或者false的情况。如下所示c1、c2、c3、c4称为从句，而s1、s2是语句。分支覆盖的要求是整个条件(c1 && c2)||(c3 && c4)应当出现true和false，而从句覆盖是要求4个从句c1、c2、c3、c4都可以至少出现一次true和false。

​	按照某个测试集执行程序会得到不同的语句执行路径，简单的程序**<u>执行路径覆盖</u>**和语句覆盖、分支覆盖和从句覆盖都是等价的，如下方的二次方程求根的程序；而找到数组最大值坐标的执行路径个数，随着n的增加成指数增加，即2^n条执行路径，此时执行路径覆盖是很难实现的，测试集需要拥有任意长度n的数组数量。执行语句覆盖一般也能实现语句和分支覆盖，当分支覆盖和从句覆盖等价时也实现了从句覆盖。

```c++
if ((c1 && c2)||(c3 && c4))
    s1;
else
    s2;
```

### 1.3测试程序举例

​	具体代码文件见配套的<charter2_01测试与调试.cpp>，注意使用复数complex可以接收相应的复数结果

​	下方的程序是计算二次方根的，测试函数为_charter2_test_and_debug，计算函数为quadratic_equation_find_root

```c++
#include "charter2.h"
#include <complex>
typedef std::complex<double>dcomplex; // 对double的情况使用别名
void quadratic_equation_find_root(const double & a , const double &b ,const double &c, dcomplex& x1, dcomplex& x2);
void _charter2_test_and_debug()
{
	double a = 1, b = -5, c = 6;
	dcomplex x1, x2;
	quadratic_equation_find_root(a, b, c, x1, x2);
	a = 1, b = 2, c = 5;
	quadratic_equation_find_root(a, b, c, x1, x2);
}
void quadratic_equation_find_root(const double& a, const double& b, const double& c , dcomplex & x1, dcomplex & x2 )
{
	if (a == 0)
		throw("a should be ≠ 0");
	double delta = b * b - 4 * a * c; // b^2-4ac
	double k = -b / (2 * a);
	if (delta > 0) // 两个不同实数根
	{
		double d = sqrt(delta) / (2*a);
		x1 = k + d;
		x2 = k - d;
	}
	else if (delta == 0)
	{
		// 两个相同实数根
		x1 = x2 = k;
	}
	else
	{
		// 共轭复根
		dcomplex d(0, sqrt(-delta) / (2 * a));
		x1 = k+d;
		x2 = k-d;
	}
	std:: cout << "x1 = " << x1.real()<<" + " <<x1.imag()<<"i"<< 
		"   x2 = " << x2.real()<<" + "<<x2.imag()<<"i" << std::endl;
}
```

​	下方是查找数组最大值所在的位置函数，如果是无顺序的数组a[5]={0,1,2,3,4}这样的数据在分支覆盖中不满足，因为不存在a[loc]>a[i]的情况，而测试语句中使用的可以满足语句覆盖也能满足分支覆盖。

```c++
template<class T>
int find_maxval_loc_in_array(T a[], int n);
// _charter2_test_and_debug中的测试语句
int d[6] = { 0,9,20,44,3,17 };
int loc;
loc = find_maxval_loc_in_array(d, sizeof(d) / sizeof(d[0]));
// _charter2_test_and_debug中的测试语句
// 函数实现
template<class T>
int find_maxval_loc_in_array(T a[], int n)
{
	if (n <= 0)
		throw("n must be > 0");
	int loc = 0; // 最大位置初始化为第1个元素的索引0
	for (int i = 1; i < n; i++)
	{
		if (a[loc] < a[i])
			loc = i; // 更新最大值索引位置
	}
    std::cout << "maxval index = " << loc << std::endl;
	return loc;
}
```

## 2.程序性能分析

### 2.1空间和时间复杂度

#### 2.1.1空间复杂度

​	空间复杂度需要的空间总体分为**<u>固定部分和可变部分</u>**。固定部分主要分为**<u>指令空间和数组空间</u>**的简单变量空间和常量空间；可变部分是指**<u>环境栈空间</u>**，可以是动态分配的空间也可以是递归函数使用的递归栈空间。

​	指令空间取决于

- 编译器的性能
- 编译器的选项
- 目标计算机

​	例如编译器需要的内存可能是不同的，1MB或者4MB；编译器的选项可以使用优化模式，这可能在程序中利用知识简化运算，也可以使用覆盖模式，此时读取的代码模块并不是分配在新内存上而是覆盖，这样程序所需要的空间是最大模块所需要的空间，而不是所有模块需要的空间之和；计算机的配置也有较大影响，装有浮点处理的硬件可以把每个浮点操作转为一条机器指令，否则需要生成代码模拟浮点操作。

​	数据空间一般和计算机的字长有关，一个字可以是2字节、4字节也可以是8字节，一个字节等于8位，现在64位的计算机就是指一个字有8字节。以32位计算机为例，不同数据类型占据不同的空间，如下表所示。

|      类型      | 空间大小(字节数) |             范围              |
| :------------: | :--------------: | :---------------------------: |
|      bool      |        1         |          true,false           |
|      char      |        1         |          [-128,127]           |
| unsigned char  |        1         |            [0,255]            |
|     short      |        2         |        [-32768,32767]         |
| unsigned short |        2         |           [0,65535]           |
|      long      |        4         |        [-2^31,2^31-1]         |
| unsigned long  |        4         |          [0,2^32-1]           |
|      int       |        4         |        [-2^31,2^31-1]         |
|  unsigned int  |        4         |          [0,2^32-1]           |
|     float      |        4         |         ±3.4E±38(7位)         |
|     double     |        8         |        ±1.7E±308(15位)        |
|  long double   |        10        |       ±1.2E±4392(19位)        |
|    pointer     |        2         | near, _cs, _ds, _es, _ss 指针 |
|    pointer     |        4         |         far、huge指针         |
|                |                  |                               |

​	一个结构变量的空间大小是结构成员所需空间大小之和，一个数组也是所有成员空间大小之和。

​	关于空间复杂度的大致区分如下图所示。

![](D:\VisualStudioItems\数据结构与算法\空间复杂度.jpg)

​	如何使用实例特征估计空间复杂度？请看以下几个例子

​	例1：顺序查找，在数组中从左到右查找第一个与x相等的元素，找到返回它第一次出现的位置，否则返回-1

​	n是数组顺序查找的实例特征，形参a、x、n，常量0、1和代码需要空间，这是独立于实例特征的固定空间大小，它们不依赖于n。所以空间复杂度s(n)=0。

```c++
template<class T>
int sequantialSearch(T a[], int n , const T &x)
{
    int i ;
    for (i = 0; i < n && a[i] != x; i++); // 空循环 
    if (i == n) // 如果循环都走完了还没找到就返回-1
        return -1;
    else return i; // 找到时循环会终止 此时返回对应的i
}
```

 例2：第1个程序是递归函数对数组元素进行求和，n=0时为0，n＞0时进行计算；第2个程序是普通循环对数组元素求和。

​	a、n也是形参，但是递归函数的形式参数和返回地址的空间需要存储，对于a是一个指针(4字节)、n是int也是4字节、返回的地址假定也是4字节，那么每次递归调用需要12字节的递归栈空间。由于递归深度为n+1，所以共需s(n)=12(n+1)字节的栈空间。而后者函数只是分配一些固定空间，theSum、i以及常数0的空间与n无关，s(n)=0。

```c++
template<class T>
T rSum(T a[],int n)
{
    if(n>0)
        return rSum(a,n-1)+a[n-1];
    return 0;
}
template<class T>
T sum(T a[], int n)
{
    T theSum = 0;
    for(int i =0 ; i<n;i++)
        theSum += a[i];
    return theSum;
}
```

​	例3：也是递归函数，不过是求阶乘，根据n和1的关系，递归深度是max(n,1)，每次递归返回的地址和n都是4字节，所以s(n)=8*max(n,1)，其它不依赖于n

```c++
int factorical(int n)
{
    if (n<=1) return 1;
    else return n*factorical(n-1);
}
```

​	以上所有源代码见<charter2_02空间复杂度.cpp>中

#### 2.1.2时间复杂度

​	时间复杂度=编译时间和运行时间。编译时间与实例特征无关，程序编译后可以多次运行；运行时间取决于操作次数与操作类型花费时间的和。例如加减乘除的花费时间是不同的，通过计算程序这些操作的次数，再乘对应的时间即可。

​	但是这样估计运行时间是不精确的，因为四则运算浮点数和整型数花费的时间又是不同的，还与操作对象数据类型有关；当前计算机还可能是多线程的，可以同时处理一个整数操作和一个浮点数操作，并非顺序执行；算术操作流水线和存储等级也使得m次操作的时间未必是m倍的单次操作时间。

​	一般估计程序运行时间的方法是：找到一个或几个关键步骤花费的时间，然后确定程序的总步数，相乘即可得到偏大的运行时间。

​	例1：以多项式求值为例，计算y(x) = c0+c1x1+c2x^2+...cnx^n，在下方的程序代码中每次循环需要计算2次乘法和1次加法，所以加法次数为n、乘法次数为2n

```c++
template<class T1, class T2>
T1 polynomial_calculate_accumulate(T1 coeff[], int n, const T2& x)
{
	// 计算多项式y=c0+c1x+c2x^2+...cnx^n
	T1 x_n = 1; // x_n从n=0,1,2...  => 1,x,x^2,x^3,...
	T1 value = coeff[0]; // c0开始,c0+Σcnx_n
	for (int i = 1; i <= n; i++)
	{
		x_n *= x; // x,x^2,x^3,...
		//std::cout << "x_n = " << x_n<< std::endl;
		value += x_n * coeff[i]; // i从1开始直到n都计算
		//std::cout << "value = " << value <<std::endl;
	}
	return value;
}
```

​	例2：多项式可以利用Horner法则进行分解，y(x) = (...(cn * x+cn-1) * x + cn-2 ) * x + cn-3 ) *...) * x + c0 ， 例如y(x)=5x^3-4x^2+x+7 可以分解为 y(x) = ((5x-4)x+1)x+7 ，需要计算3次加法和3次乘法。根据法则推广总的次数是n次加法和n次乘法，所以下方程序要快于上述版本

```c++
T1 polynomial_calculate_hornor(T1 coeff[], int n, const T2& x)
{
	// y(x) = (...(cn * x+cn-1) * x + cn-2 ) * x + cn-3 ) *...) * x + c0 
	T1 value = coeff[n];
	for (int i = 1; i <= n; i++)
	{
		value = value * x + coeff[n-i]; // 某次计算的结果整体value作为下次与x整体相乘
		std::cout << "value = " << value << std::endl;
	}
	return value;
}
```

##### 2.1.2.1计数排序

​	先说结论，时间复杂度为n(n-1)/2+2n，其中计算排序位置n(n-1)/2，移动元素2n

​	例3：名次计算，一个序列中某个元素的名次等于所有比它小的元素个数总数+它左边和它相同的元素个数，也就是不仅要考虑比别人大，也要考虑与相同大小元素相比出现的相对名次。例如数组[4,3,9,3,7]，比4小的只有2个3且左边没有4所以排名第2，7排名3，9排名4，而2个3大小相等就考虑谁先出现，第1个3先出现所以名次靠后为0，第2个3名次为1，最终返回值为[2,0,4,1,3]。如下程序所示。

​	外循环所在的元素和以前的元素都没有比较过，所以内循环就是让这个a[i]以前的元素都a[j]要和它进行比较，故j<i；如果这个元素比以前的一个元素大排名就要提升1，如果相等的元素因为是后出现的元素，排名依然+1。以5个元素数组举例，运行的程序实际上是a[0]&a[1] => 1次比较

a[0]&a[2]、a[1]&a[2] => 2次比较

a[0]&a[3]、a[1]&a[3]、a[2]&a[3] => 3次比较

a[0]&a[4]、a[1]&a[4]、a[2]&a[4]、a[3]&a[4] => 4次比较

....推广之

a[0]&a[n-1]、a[1]&a[n-1]、a[2]&a[n-1]、a[3]&a[n-1]、...a[n-2]&a[n-1] => n-1次比较(因为n=0就无需比较,n-1已经是边界)

总的比较次数为：1+2+3+...n-1 = n(n-1)/2

```c++
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
```

​	利用计算出的名次就可以对原有的数组进行排序，这种排序也叫计数排序，需要一个附加数组，排序的移动次数为2n，附加数组移动n次，放回原数组次数n次。所以2个函数完成计数排序就需要n(n-1)/2+2n次移动

```c++
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
```

​	在代码文件<sort_method.h>中一次性实现了计数排序，如下所示，开辟2个动态数组分别存储名次和按名次排放的临时数组即可。

```c++
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
```

##### 2.1.2.2选择排序

​	时间复杂度是n(n-1)/2+3(n-1)，比计数排序还要多n-1

​	选择排序是首先整个数组查找最大元素的位置，然后把这个位置的元素移动到末尾；然后在余下的n-1个元素中继续寻找最大位置，然后移动到倒数第2个位置；如此反复，可以得到升序结果，如果需要降序，就放在开头、第2个、第3个...也是可以的，但是查找最值索引函数需要重写，因为find_maxval_loc_in_array查找的是从1往后的i个元素，降序应当查找从n-1往前的i个元素。

​	这里鉴于只说明选择排序的思想，不提供reverse选项，带有reverse选项的版本可以在配套代码文件的头文件<sort_method.h>中找到对应的实现。

​	查找最值的时间复杂度是n(n-1)/2，因为每次要比较i-1次。交换函数每次执行需要执行3次，一共执行n-1次，因为i=n,n-1,...2共n-1次，所以总的时间复杂度是n(n-1)/2+3(n-1)

```c++
template<class T>
void rearrange_byselect(T a[], int n,  bool show)
{
	// 选择排序是先找到元素最大的位置,然后将这个元素交换到数组的末尾或者开始
	// 找到这个最大值以后继续在前n-1个元素寻找,位置是[0,n-2]
	// 以此类推直到最后有2个元素数组[0,1],继续查找即可 1个元素时已经不必进行比较了
	for (int i = n; i > 1; i--)
	{
		// 前i个元素查找最大元素
		int idx = find_maxval_loc_in_array(a, i); // 此函数的时间复杂度为i-1(比较i-1次)
		// 查找最大值索引的总的时间复杂度为(n-1)+(n-2)+...1=(n-1)n/2
		swap_array_element(a, idx, i - 1);//交换这个最大的元素到末尾位置
	}
	if (show)
		for (int i = 0; i < n; i++) std::cout << "a["<<i<<"] = "<<a[i] << std::endl;
}
// 交换函数实现
template<class T>
void swap_array_element(T a[], T idx1, T idx2)
{
	T temp;
	temp = a[idx1];
	a[idx1] = a[idx2];
	a[idx2] = temp;
}
```

​	下方程序是带有reverse版本的选择排序实现。重点注意的是降序，依次比较的数组区间是[0,n-2],[1,n-2],..[n-3,n-2]，故j的起点是0，终止于n-2，不到n-1是为了少进行一次比较。而开头位置j要不断移动到下一个元素，这个是通过参数i进行控制。鉴于写在一个循环中，i的循环是从n-1,n-2,...,1变化的已经固定，通过i来确定j的关键是要求j从0开始。

​	那么比较n-1,n-2,...,1和0,1,2,...,n-2的关系可以发现，它们的和是n-1，所以j=n-1-i如此控制。之后的关键点在于谁与谁交换，找到maxLoc以后，这个位置的元素要放在j循环的开头位置，就是n-1-i控制，如此即可实现reverse。

​	show的语句可以打印出选择排序的每一步过程，可以看到从大到小或者从小到大排序好和没排序好的元素，最后一行是全部排序好的结果。

```c++
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
```

##### 2.1.2.3冒泡排序

​	思想是先比较数组n个元素，从左到右相邻2个元素比较，如果前者大于后者则交换，最终最大的元素在右侧；然后在对数组的前n-1个元素继续进行冒泡，如此循环，直到最后一次冒泡，全部的元素都升序排列。

​	冒泡排序的实现在配套代码文件的头文件<sort_method.h>中实现，也在<charter2_03时间复杂度.cpp>实现。前者一次性实现，后者是使用2个函数间接实现。

​	<charter2_03时间复杂度.cpp>的实现，要注意的是第1个函数控制变量i要从n开始，类似于选择排序，也是从前i个元素轮流交换的，i最小取到2；对应在第2个函数中形参n可以取到n和2,进而i只能取到n-2和0，因为i取到n-2后i+1取到n-1正好在边界符合要求。bubble函数的时间复杂度是n-1(比较)+(交换)，故总的时间复杂度为[(n-1)+(n-2)+...1]+(交换)=**<u>n(n-1)/2 +(交换)</u>**。

​	关于交换，bubble函数是无法确定的，因为取决于两两交换的值，如果每次大循环前者一直比后者小，就不用执行交换，时间复杂度=0；如果每次大循环一直都比后者大，每次都要交换，从a[i]和a[i+1]交换持续到a[n-2]和a[n-1]交换，累积为(n-1)+(n-2)+..+1=n(n-1)/2次，又因为交换函数需要三次赋值过程，故时间复杂度等于n(n-1)/2 * 3。这就是最好和最坏的结果，由此引入新的概念：**<u>最好、最坏和平均操作次数</u>**，在后面的[2.1.2.4有序数组插入元素](#2.1.2.4有序数组插入元素)会回过来具体说明。

​	下方这个函数没有实现reverse的功能，该功能在<sort_method.h>中进行实现。

```c++
template<class T> 
void rearrange_bybubble(T a[], int n, bool show)
{
	for (int i = n; i > 1; i--)
		bubble(a, i);
	if (show)
		for (int i = 0; i < n; i++) std::cout << "a[" << i << "] = " << a[i] << std::endl;
}

template<class T>
void bubble(T a[], int n)
{
	for (int i = 0; i < n - 1; i++)
		if (a[i] > a[i + 1]) swap_array_element(a, i, i + 1); 
}
```

​	<sort_method.h>的实现，是一次性的实现，如下方程序所示，可以展示出每步bubble的过程，并带有reverse功能。

```c++
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
```

##### 2.1.2.4有序数组插入元素

​	继续上次bubble函数的讨论，考虑一个顺序查找的场景。顺序查找的时间复杂度不仅取决于数组的长度n，还取决于查找的值的实际情况。最好的情况是，第1个元素a[0]就是要查找的x值，那么只需要一次操作；最差的情况是查找100次a[99]才是x，或者没有找到这个值也是100次。所以平均操作次数为(n+1)/2次。

​	例4：有序数组插入元素，最好的情况是插入的元素比所有元素都大，需要先与a[n-1]进行比较1次，然后无需移动赋值即可；最坏的情况是插入的元素只比a[0]大或者比所有元素都小：只比a[0]大时，元素x要与a[1]、a[2]、...a[n-1]都比较1次共n-1次，但是知道比a[0]大也要比较1次，所以一共是**<u>n次</u>**；如果比所有元素都小，只需要和a[0]、a[1]、a[1]、...a[n-1]比较也是n次，这是因为无需与前一个进行比较，所以最坏的情况还是n次。那么<u>**平均情况实际上是1+2+3+...+n+n次，所以平均时间复杂度为[n(n+1)/2+n]/(n+1)**</u>。程序如下方所示，注意i可以取到n-1和0，i取到0的时候执行a[1]=a[0]，然后i--等于-1，此时继续执行a[-1+1]=x不会越界，但是要求a的容量比n大。

```c++
template<class T>
void insert_ordered_array(T a[], int& n, const T& x)
{
	int i; // 不能for循环内部定义int i = n-1会报错无法识别i
	for (i = n - 1; i >= 0 && x < a[i]; i--)// x < a[i] i从n - 1开始到0结束
		a[i + 1] = a[i]; // 如果x<a[i]说明应当把x赋给a[i],而a[i]原有值移动到a[i+1]
	a[i + 1] = x; // 如果x>a[i]直接令a[i+1]=x即可,需要注意的是a的空间要大于n否则a[i+1]越界
	n++;
	// i = n-1, a[n] = x ; 右插    i = 0 时x<a[0]那么a[1]=a[0],然后i--，执行a[0]=x 左插
	// 取特殊情况 一开始就右插到a[i+1],那么至少比较1次不执行赋值交换
	// 如果左插到a[1],需要从x<a[i]比较到x<a[1],也就是i次,x<a[1]比完以后还要比较一次a[0]才结束循环实际上是i+1次
	// 故最坏情况每次大循环都依次左插到a[i+1],a[i],..a[1]要比较1,2,..,i+1次，也就是n(n+1)/2次
}
```

##### 2.1.2.5计数排序的改进_原地排序

​	计数排序的思路是先计算一个数组的名次，或者说将要被移动的索引rank。映射关系为

a[0]->a[rank[0]]

​	a[1]->a[rank[1]]

​		a[2]->a[rank[2]]

​				a[3]->a[rank[3]]

​					...

​						a[n-1]->a[rank[n-1]]

​	可以先把a[rank[n-1]]的元素按照rank的名次赋值给新的数组temp，再把temp的元素temp[i]一一对应赋值给a[i]，如果需要reverse赋值给a[n-1-i]即可(i=0,1,2,..n-1)，这是计数排序的思路。

​	原地重排可以不借助辅助数组temp，同样需要先计算名次rank。然后得到的新名次是无序的，如果名次变得有序，并对数组实施对应的交换，即可让数组有序。交换的位置要注意是i和rank[i]，其中i是当前a[i]的实际位置,rank[i]是a[i]移动去往的位置。所以交换rank本身的2个名次也是交换rank[i]和rank[rank[i]]。

```c++
// 测试程序
const int n = 10;
    int a[n] = { 6,5,8,4,3,1,13,0,66 ,-2};
	situ_rearrangement(a, n);
	for (int i = 0; i < n; i++)
		std::cout << "a[" << i << "] = " << a[i] << "   ";
	std::cout << std::endl;
// 原地排序代码
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
```

​	代码的运行逻辑以下方例子进行说明，初始的数组为daefcb，计算的名次为304521

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

##### 2.1.2.6选择排序的改进_及时终止

​	原有的选择排序是从1到k(k=n-1,n-2,..,2)的每个区间找到最大值，并把最大值交换到a[k]的位置，也就是放在最后，如此循环操作可以得到有序序列，每次区间查找最大值都要比较k次，总计k+(k-1)+...+1=(n-1)+(n-2)+...+1=n(n-1)/2次，加上交换操作是3k=3(n-1)。它的问题在于如果某次区间比较完后，序列已经有序，仍然会进入下一轮的比较。所以可以引入有序控制变量sorted，**<u>每次循环之前都会先假设为有序，只要存在某个前元素大于后面的元素，就设定为无序继续下一次循环，否则说明已经有序</u>**，循环条件!sorted不满足提前终止循环。

```c++
template<class T>
void select_sort_timely_termination(T a[], int n)
{
	bool sorted = false; // 默认无序,无序才会进入循环
	for (int k = n; (k > 1) && !sorted; k--) // k取n,n-1,..2=>i取n-1,n-2,..,1
	{
		int idx = 0; // 比较总是从第1个元素a[1]开始,a[0]默认初始最大值
		sorted = true; // 进入循环立刻指定为有序,循环中去判断是否存在前一个元素大于后一个元素
		for (int i = 1; i < k; i++)
			if (a[idx] <= a[i]) idx = i; // 如果前者小于后者说明还是有序的,并记录最大值位置
			else sorted = false; // 任何大循环中即[1,k-1]中存在前者大于后者就说明无序,如果某次大循环已经发现有序则不再进行后续大循环提前终止
		T temp = a[idx];
		a[idx] = a[k - 1];  // 总是把最大值放在每次大循环的最后
		a[k - 1] = temp;
	}
}
```

##### 2.1.2.7冒泡排序的改进_及时终止

​	冒泡排序的提前终止思路和选择排序的终止类似，也是先使用一个控制遍历swapped，默认无序，所以swapped=true，所以循环条件中为&&swapped。原冒牌排序每次大循环从1到k(k=n-1,n-2,..,2)的每个区间内两类交换，从a[0]和a[1]交换到a[k-1]和a[k]交换，共k次，累积为k+(k-1)+(k-2)+...1次。关于交换，是无法确定的，如果一开始有序无需交换，if (a[i] > a[i + 1])不成立所以交换次数为0；如果成立，且每个a[i]>a[i+1]都成立，那么每次都要交换，a[i]和a[i+1]交换持续到a[n-2]和a[n-1]，注意这里i可以直接取到n-2，不同于选择排序与k无关，但是i++使得累积交换次数为(n-1)+(n-2)+..+1次，每次交换都需要3次赋值，那么交换的时间复杂度为3*n(n-1)/2。以上所有结论在[2.1.2.3冒泡排序](#2.1.2.3冒泡排序)具体说明过。

​	本函数的改进在于如果已经有序，就不必进入下一个大循环继续比较大小，当然更无需交换，所以节省的时间复杂度要注意只有比较的占用时间，因为有序状态时都不会执行交换。

```c++
template<class T>
void bubble_sort_timely_termination(T a[], int n)
{
	bool swapped =true; // 默认无序交换过
	for (int k = n; (k > 1) && swapped; k--) // 没有发生交换就提前终止,否则执行a[0]都a[k-1]之间的元素两两交换
	{
		swapped = false; // 进入循环立刻先视为有序 后面只有存在前者大于后者就置为true
		for (int i = 0; i < n - 1; i++)
			if (a[i] > a[i + 1]) // 如果前者元素大于后者就说明无序,此时交换发生swapped=true
			{
				T temp = a[i];
				a[i] = a[i + 1];
				a[i + 1] = temp;
				swapped = true;
			}
	}
}
```

##### 2.1.2.8插入排序

​	插入排序的思路是从数组的第一个元素开始(第0个元素无需插入)，把a[i]作为插入元素x，然后执行有序数组插入操作，i=1,2,..n-1，所以有序数组插入元素要执行n-1次，i的大小又影响了insert_ordered_array函数的比较和交换时间复杂度。最终的时间复杂度还是[n(n-1)/2+n-1]/n

```c++
template<class T>
void rearrange_byinsert(T a[], int n, bool show)
{
    // 有序数组插入元素，将a[i](i=1,2,..n-1)作为x进行插入
	for (int i = 1; i < n; i++)
	{
		T t = a[i];
		insert_ordered_array(a, i, t);
	}
	if (show)
		for (int i = 0; i < n; i++)
			printf("a[%d] = %d   ", i, a[i]);
}
template<class T>
void insert_ordered_array1(T a[], int n, const T& x)
{
    // n实际会取1,2,..n-1，故内部i取的为0,1,2..n-2
	int i=0; // 不能for循环内部定义int i = n-1会报错无法识别i
	for (i = n - 1; i >= 0 && x < a[i]; i--) // x<a[i] i从n-1开始到0结束
		a[i + 1] = a[i]; // 如果x<a[i]说明应当把x赋给a[i],而a[i]原有值移动到a[i+1]
	a[i + 1] = x; // 如果x>a[i]直接令a[i+1]=x即可,需要注意的是a的空间要大于n否则a[i+1]越界
	// i = n-1, a[n] = x ; 右插    i = 0 时x<a[0]那么a[1]=a[0],然后i--，执行a[0]=x 左插
	// 取特殊情况 一开始就右插到a[i+1],那么至少比较1次不执行赋值交换
	// 如果左插到a[1],需要从x<a[i]比较到x<a[1],也就是i次,x<a[1]比完以后还要比较一次a[0]才结束循环实际上是i+1次
	// 故最坏情况每次大循环都依次左插到a[i+1],a[i],..a[1]要比较1,2,..,i+1次，也就是n(n+1)/2次，又因为左插到a[0]是i+1次，也即是n-1+1次，所以平均次数实际上是[n(n+1)/2 + n]/(n+1)次
    // 因为外部调用的原因这里i只能取到n-2，所以复杂度是[n(n-1)/2+n-1]/n其实是一个意思。
}
```

​	一次性实现的带有reverse的插入排序函数，在配套文件<sort_method.h>实现，如下所示，这里为了方便对reverse的实现是先升序再进行首尾交换。

```c++
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

```

