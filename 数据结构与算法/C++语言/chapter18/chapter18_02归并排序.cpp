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
		mergePass(a, b, n, segmentSize); // ����õ���Ҫ�鲢�������е����ұ߽�
		segmentSize += segmentSize;
		mergePass(b, a, n, segmentSize);
		segmentSize += segmentSize;
	}
}
template<class T>
void mergePass(T x[], T y[], int n, int segmentSize)
{
	// ����õ���Ҫ�鲢�������е����ұ߽�
	// ��x��y�鲢���ڵ����ݶ�
	int i = 0;
	while (i <= n - 2 * segmentSize)
	{
        merge(x, y, i, i + segmentSize - 1, i + 2 * segmentSize - 1);
        i = i + 2 * segmentSize;
	}
	// ����2�������ݶ�
	if (i + segmentSize < n) {
		merge(x, y, i, i + segmentSize - 1, n - 1);
	}
	else { // ֻʣ1�����ݶ�,���Ƶ�y
		for (int j = i; j < n; j++)
			y[j] = x[j];
	}
}
template<class T>
void merge(T c[], T d[], int startOfFirst, int endOfFirst, int endOfSecond)
{
	// ��2���������ݶδ�c�鲢��d
	int first = startOfFirst; // ��1�����ݶε�����
	int second = endOfFirst + 1; //��2�����ݶε�����
	int result = startOfFirst;// �鲢���ݶε�����

	// ֱ��1�����ݶι鲢��d
	while ((first <= endOfFirst) && (second <= endOfSecond)) {
		if (c[first] <= c[second])
			d[result++] = c[first++];
		else d[result++] = c[second++];
	}
	//	// �鲢ʣ��Ԫ��
		if (first > endOfFirst)
			for (int q = second; q <= endOfSecond; q++) {
				d[result++] = c[q];
			}
		else
			for (int q = first; q <= endOfFirst; q++) {
				d[result++] = c[q];
			}
}

