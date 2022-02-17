#include "chapter12_maxHeap.h"
#include <iostream>
using namespace std;
template<class T>
void _chapter12_heapSort(T* a,int n, bool rever=false);
void _chapter12_heapSort_testCode() {
	int a[11] = { 0,9,14,21,8,19,44,6,11,43,-1 };
	_chapter12_heapSort(a, 10);
	for (int i = 0; i <= 10; i++) {
		cout << a[i] << " ";
	}
	cout << "\n";
	cout << "-------------------------------------------" << endl;
	_chapter12_heapSort(a, 10, true);
	for (int i = 1; i <= 10; i++) {
		cout << a[i] << " ";
	}
	cout << "\n";
}
template<class T>
void _chapter12_heapSort(T  *a , int n,bool rever) {
	maxHeap<T> heap(1); // 初始容量1
	heap.initialize(a,n);
	for (int i = n - 1; i >= 1; i--) {
		T x = heap.top();
		heap.pop();
		a[i + 1] = x;  // a[1,n]为排序后的结果,最大的放在a[n],升序
	}
	heap.deactivateArray(); // 防止把数组a也删除
	if (rever) {
		int* b = new int[n];
		for (int i = 1; i <= n; i++) {
			b[i] = a[n + 1 - i];
		}
		a = b;
	}
}