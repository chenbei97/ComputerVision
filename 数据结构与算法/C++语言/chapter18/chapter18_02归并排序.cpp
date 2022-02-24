#include <iostream>
using namespace std;
template<class T>
void mergeSort(T a[], int n);
template<class T>
void mergePass(T x[], T y[], int n, int segmentSize);
template<class T>
void merge(T c[], T d[], int startOfFirst, int endOfFirst, int endOfSecond);
void _chapter18_mergeSort() {
	//int a[10] = { 10,7,8,9,4, 2, 3, 6, 5,1 };
	//mergeSort(a, 10);
	int a[5] = { 1,5,4,2,3 };
	mergeSort(a, 5);
	for (int i = 0; i < 5; i++) {
		cout << a[i] << " ";
	}
	cout << "\n";
}
template<class T>
void mergeSort(T a[], int n)
{
	T* b = new T[n];
	int segmentSize = 1;
	while (segmentSize < n) {
		mergePass(a, b, n, segmentSize); // 负责得到需要归并的子序列的左右边界
		segmentSize += segmentSize;
		mergePass(b, a, n, segmentSize);
		segmentSize += segmentSize;
	}
}
template<class T>
void mergePass(T x[], T y[], int n, int segmentSize)
{
	// 负责得到需要归并的子序列的左右边界
	// 从x到y归并相邻的数据段
	int i = 0;
	while (i <= n - 2 * segmentSize)
	{
        merge(x, y, i, i + segmentSize - 1, i + 2 * segmentSize - 1);
        i = i + 2 * segmentSize;
	}
	// 少于2个满数据段
	if (i + segmentSize < n) {
		merge(x, y, i, i + segmentSize - 1, n - 1);
	}
	else { // 只剩1个数据段,复制到y
		for (int j = i; j < n; j++)
			y[j] = x[j];
	}
}
template<class T>
void merge(T c[], T d[], int startOfFirst, int endOfFirst, int endOfSecond)
{
	// 把2个相邻数据段从c归并到d
	int first = startOfFirst; // 第1个数据段的索引
	int second = endOfFirst + 1; //第2个数据段的索引
	int result = startOfFirst;// 归并数据段的索引

	// 直到1个数据段归并到d
	while ((first <= endOfFirst) && (second <= endOfSecond)) {
		if (c[first] <= c[second])
			d[result++] = c[first++];
		else d[result++] = c[second++];
	}
	//	// 归并剩余元素
		if (first > endOfFirst)
			for (int q = second; q <= endOfSecond; q++) {
				d[result++] = c[q];
			}
		else
			for (int q = first; q <= endOfFirst; q++) {
				d[result++] = c[q];
			}
}

