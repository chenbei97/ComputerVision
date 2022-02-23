#include <iostream>
using namespace std;
template<class T>
bool chapter18_minMax(T a[], int n, int& minIndex, int& maxIndex);
void _chapter18_minMax() {
	const int n = 10;
	int a[n] = { 10,9,7,-1,5,3,2,4,1,13 };
	int minIndex, maxIndex;
	chapter18_minMax(a, n, minIndex, maxIndex);
	cout << " the maxest element is " << a[maxIndex] << endl;
	cout << " the minest element is " << a[minIndex] << endl;
}
template<class T>
bool chapter18_minMax(T a[], int n, int& minIndex, int& maxIndex) {
	// 在a[0,n-1]内找出最大最小值
	if (n < 1) return false;
	if (n == 1) {
		minIndex = maxIndex = 0; 
		return true;
	}
	int start ; // 循环的起点取决于n的奇偶性

	if (n % 2 == 1) { // 奇数,那就拿出1个作为初始最大最小值,后边偶数个元素可以两两比较
		minIndex = minIndex = 0; // a[0]认为是一开始最大和最小的元素
		start = 1; // (1,2),(3,4)...这样两两比较
	}
	else { // 偶数,拿出1个值会有问题,所以拿出2个,所以先比较2个元素
		if (a[0] > a[1]) { // 先比较2个元素a[0]和a[1]
			minIndex = 1;
			maxIndex = 0;
		}
		else {
			minIndex = 0;
			maxIndex = 1;
		}
		start = 2; // 从a[2]开始比较
	}

	// 剩余元素必定是偶数个
	for (int i = start; i < n; i += 2) {
		if (a[i] > a[i+1] ) { // 如果前1个元素大
			if (a[i] > a[maxIndex]) maxIndex = i; // 则让前1个元素和目前最大的比较
			if (a[i + 1] < a[minIndex]) minIndex = i+1; // 后1个元素和目前最小的比较
		}
		else { // 后1个元素大,则正好反过来
			if (a[i+1] > a[maxIndex]) maxIndex = i+1;
			if (a[i] < a[minIndex]) minIndex = i;
		}
	}
	return true;
}