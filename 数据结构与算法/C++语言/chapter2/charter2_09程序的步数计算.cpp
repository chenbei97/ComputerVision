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
    printf("sum = %d stepCount = %d\n", sum_cops(a, 4), step_count_cops);
    assert(step_count_cops = 2 * n + 3); // �ۼ��ܲ���=2n+3
    step_count_cops = NULL;
    printf("rsum = %d stepCount = %d\n", rsum_cops(a, 4), step_count_cops);
    assert(step_count_cops = 2 * n + 2); // �ݹ��ܲ���=2n+2

}
template<class T>
T sum_cops(T a[], int n)
{
    T res = 0; step_count_cops++; // T res = 0 =1������=1��
    for (int i = 0; i < n; i++) // Ҳ��1������ ����ִ��Ƶ�ʲ�ͬ,������n+1��,��Ϊi=n��Ҫ�ж�һ�β�����ֹforѭ�� 
    {
        step_count_cops++; // ÿ��forѭ��ִ��һ�ζ�����һ��,�����ۻ���n��
        res += a[i]; step_count_cops++; // �������1������,ִ��һ������1��,�����ۻ���n��
    }
    step_count_cops++;//����i=n����һ��
    step_count_cops++;// return���ĸ�����=>����1+n+n+1+1=2n+3��
    return res;//���һ������
}
template<class T>
T rsum_cops(T a[], int n)
{
    step_count_cops++; // if�����1������
    if (n > 0) // ����˺���һ����ִ��һ��
    {
        step_count_cops++;// return��1������
        return rsum_cops(a, n - 1) + a[n - 1];//a[n-1]+a[n-2]+...a[1]������һ������
        // n=1ʱҲ�����ִ��2��,Ȼ�����rsum(a,0)+a[0],����Ϊֹ�ۻ�2n��,rsum(a,0)��ִ��2��
    }
    step_count_cops++; // rsum(a,0)ִ�е�һ��
    return 0;
}