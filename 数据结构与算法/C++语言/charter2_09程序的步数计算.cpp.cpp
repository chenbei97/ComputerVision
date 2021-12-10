#include <iostream>
#include <assert.h>
int step_count_cops = 0;
template<class T>
T sum_cops(T a[], int n);
template<class T>
T rsum_cops(T a[], int n);
void _charter2_calculation_of_program_steps()
{
    const int n = 4;
    int a[n] = { 1,2,3,4 };
    printf("sum = %d stepCount = %d\n",sum_cops(a, 4),step_count_cops);
    assert(step_count_cops = 2*n +3); // 累加总步数=2n+3
    step_count_cops = NULL;
    printf("rsum = %d stepCount = %d\n", rsum_cops(a, 4), step_count_cops);
    assert(step_count_cops = 2 * n + 2); // 递归总步数=2n+2

}
template<class T>
T sum_cops(T a[], int n)
{
    T res = 0; step_count_cops++; // T res = 0 =1个程序步=1步
        for (int i = 0; i < n; i++) // 也是1个程序步 但是执行频率不同,包含了n+1步,因为i=n还要判断一次才能终止for循环 
        {
            step_count_cops++; // 每次for循环执行一次都增加一步,这里累积了n步
            res += a[i]; step_count_cops++; // 该语句是1个程序步,执行一次增加1步,这里累积了n步
        }
    step_count_cops++;//这是i=n的那一步
    step_count_cops++;// return语句的个程序步=>共计1+n+n+1+1=2n+3步
    return res;//最后一个程序步
}
template<class T>
T rsum_cops(T a[], int n)
{
    step_count_cops++; // if语句是1个程序步
    if (n > 0) // 进入此函数一定会执行一次
    {
        step_count_cops++;// return是1个程序步
        return rsum_cops(a, n - 1) + a[n - 1];//a[n-1]+a[n-2]+...a[1]本身是一个程序步
        // n=1时也会继续执行2步,然后进入rsum(a,0)+a[0],至此为止累积2n步,rsum(a,0)再执行2步
    }
    step_count_cops++; // rsum(a,0)执行的一步
    return 0;
}