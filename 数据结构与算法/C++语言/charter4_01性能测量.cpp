#include <iostream>
template<class T>
void _charter4_insert_sort(T a[], int n);
void _charter4_ppm1();
void _charter4_ppm2();
void _charter4_program_performance_measurement()
{
	_charter4_ppm1(); // 方式1计时
	std::cout << "\n" << std::endl;
	_charter4_ppm2();// 方式2计时
	system("pause");
}
void _charter4_ppm2()
{
	const int num = 10000;
	int a[num], step = 10;
	double clockPerMill = double(CLOCKS_PER_SEC) / 1000; // 1滴答=1ms 原来1滴答=1s
	for (int n = 0; n <= num; n += step)
	{
		long numOfRepeat = 0; // 记录执行while循环的次数,与当前时间到t1的距离远近有关
		// 越近,clock()-t1<160判断的次数越多,越远就越少,while结束时花费的时间除while的次数就是1次while真正的时间
		clock_t t1 = clock(); // 当前时钟数
		do 
		{//利用时间控制的循环,每次n的时间运行超过160ms都是不合理的
			numOfRepeat++;
			for (int i = 0; i < n; i++)
				a[i] = n - i; // 初始化
			_charter4_insert_sort(a, n);
			//printf("n = %d numOfRepeat = %long\n", n,numOfRepeat);
		} while (clock() - t1 < 160); //程序从_charter4_ppm1的结果来看n=num才花费150ms,所以要求不超过160ms
		// n较小时clock精度不够记录不到这么小的时间差,但最大也就160ms,所以实际运行时间在0-160ms即可超过则beak

		double cost_time = ((double)clock() - t1) / clockPerMill; // 初始化数组+排序的时间经历的滴答数 除每个滴答数花费的ms就是ms
		// 然后注释掉排序的时间再运行一遍,两个时间做差就是排序时间
		printf("numOfRepeat = %d  length(a) = %d  cost time = %f ms\n", numOfRepeat, n, cost_time / numOfRepeat);
		if (n == 100) step = 50; 
		if (n == 5000) step = 100;
	}
}
void _charter4_ppm1()
{
	const int num = 10000;
	int a[num], step = 10;
	double clockPerMill = double(CLOCKS_PER_SEC) / 1000; //转换为1ms的时钟数
	printf("clockPerMill = %lf\n", clockPerMill);// 每s的滴答数是1000,每1ms的滴答数1次
	for (int n = 0; n <= num; n += step)
	{ // n=0,10,20,...,1000
		for (int i = 0; i < n; i++)
		{ // i=0,1,2,..n-1
			a[i] = n - i; // 初始化数组,i会从0取遍到999,且初始化的数据是n-i相当于降序,降序是最坏的数据
		}
		clock_t start_time = clock(); // t1
		_charter4_insert_sort(a, n); // 对[0,n-1]的数组进行排序,随着n的增加插入排序复杂度越来越高
		double cost_time = ((double)clock() - start_time) / clockPerMill; // 除1ms的时钟数得到ms
		printf("length(a) = %d , cost time = %f ms\n", n, cost_time);

		if (n == 100) step = 100; // 当n≥100时,花费时间增长的很快,需要确定的渐近线点数稀疏即可
		if (n == 5000) step = 500;
	}
}
template<class T>
void _charter4_insert_sort(T a[], int n)
{
	for (int i = 1; i < n; i++) //执行i=1,2,..n-1,n(不进入循环)
	{
		T t = a[i]; // +1
		int j; // +1
		for (j = i - 1; j >= 0 && t < a[j]; j--)//for语句多一次判断,j=0,1,..n-2依次执行比较2,..n次
			a[j + 1] = a[j]; // j=0,1,2,...,n-2各执行1次,内部语句共执行n-1次
		a[j + 1] = t; // +1
	}
	// +1合计3(n-1)
// 最好的情况是2级for不执行内部语句相当于只执行比较,也是n-1次，合计4(n-1)次
// 最坏的情况是2级for每次都执行到头。
// i=1,j=0,执行1次比较后再比较判定是否进入语句a[j+1] = a[j],相当于执行2次for语句,1次内部语句
// i=n-1,j=n-2也是，执行n次for语句,n-1次内部语句
// for语句执行了2+3+..+n次，内部语句执行了1+1..+1共n-2+1=n-1次,合计n(n+1)/2-1+(n-1)+3(n-1)=(n^2+9n-10)/2次
}
