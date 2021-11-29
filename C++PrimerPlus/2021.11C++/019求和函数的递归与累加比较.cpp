#include "all.h"
template <class T>
T recursion(T a[] ,int n)
{
	if (n > 0)
	{
		//cout << recursion(a, n - 1) << endl;
		//cout <<"a["<<n-1<<"] = " <<a[n - 1] << endl;
		return recursion(a, n - 1) + a[n - 1];//

	}
		
	return 0;
}
template <class T>
T accumulation(T *a, int n)
{ // T *a 或者 T a[] 均可
	T temp = 0;
	for (int i = 0; i < n; i++)
		temp += a[i];
	return temp;
}
long int factorial(int n)
{
	if (n <= 1) return 1;
	else return n * factorial(n - 1);
}
void recursion_accumulation_of_summationFunction()
{
	int n = 10;
	cout << n << " ! = " << factorial(n) << endl;
	int m = 4000; // 不要太大,递归会炸
	int* arr = new int[m];
	for (int i = 0; i < m; i++)
		arr[i] = i * 2;
	clock_t startTime, endTime;
	startTime = clock();
	cout << "accumulation(arr, m) = "<< accumulation(arr, m) << endl;
	endTime = clock();
	cout << "accumulation use time = " << (double)(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;
	startTime = clock();
	cout << "recursion(arr, m) = " << recursion(arr, m) << endl;
	endTime = clock();
	cout << "recursion use time = " << (double)(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;
	delete[] arr;
}