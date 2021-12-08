#include <iostream>
template<class T>
int sequantialSearch(T a[], int n, const T& x);
template<class T>
T rSum(T a[], int n);
int factorical(int n);
template<class T>
T sum(T a[], int n);
void  _charter2_spatial_complexity()
{
    const int n = 10;
    int a[n] = { 9,2,3,6,5,7,8,2,1,10 };
    int x = 7;
    int result = sequantialSearch(a, n, x);
    std::cout << "sequantial search '10' idx = " << result << std::endl;
    int _sum = rSum(a, n);
    std::cout << "rSum = " << _sum << std :: endl;
    _sum = sum(a,n);
    std::cout << "sum = " << _sum << std::endl;
    result = factorical(n);
    std::cout << "10! = " << result << std::endl;
}
template<class T>
int sequantialSearch(T a[], int n, const T& x)
{
    int i;
    for (i = 0; i < n && a[i] != x; i++);// 空循环
    if (i == n)// 如果循环都走完了还没找到就返回-1
        return -1;
    else return i;// 找到时循环会终止 此时返回对应的i
}
template<class T>
T rSum(T a[], int n)
{
    if (n > 0)
        return rSum(a, n - 1) + a[n - 1];
    return 0;
}
template<class T>
T sum(T a[], int n)
{
    T theSum = 0;
    for (int i = 0; i < n; i++)
        theSum += a[i];
    return theSum;
}
int factorical(int n)
{
    if (n <= 1) return 1;
    else return n * factorical(n - 1);
}