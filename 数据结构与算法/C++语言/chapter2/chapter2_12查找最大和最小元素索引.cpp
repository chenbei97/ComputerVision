#include <iostream>
#include "chapter1_illegalParameterValue.h"
using namespace std;
template<class T>
bool _chapter2_minMax_one(T a[], int n, int& indexOfMin, int& indexOfMax);
template<class T>
bool _chapter2_minMax_two(T a[], int n, int& indexOfMin, int& indexOfMax);
void _chapter2_find_minMax_index() {
	const int n = 5;
	double a[n] = { 1.2,2.3,5.7,-1,4.6 };
	int minIndex, maxIndex;
	_chapter2_minMax_one(a, n, minIndex, maxIndex);
	cout << "the maxest element is " << a[maxIndex] << endl;
	cout << "the minest element is " << a[minIndex] << endl;
	_chapter2_minMax_two(a, n, minIndex, maxIndex);
	cout << "the maxest element is " << a[maxIndex] << endl;
	cout << "the minest element is " << a[minIndex] << endl;
}
template<class T>
bool _chapter2_minMax_one(T a[], int n, int& indexOfMin, int& indexOfMax) {
	if (n < 1) {
		throw illegalParameterValue("bad length of arr");
		return false;
	}
	indexOfMax = indexOfMin = 0; // 初始认为a[0]最大/小
	for (int i = 1; i < n; i++) {
		if (a[indexOfMax] < a[i]) indexOfMax = i;
		if (a[indexOfMin] > a[i]) indexOfMin = i;
		// 比较次数为2(n-2)
	}
	return true;
}
template<class T>
bool _chapter2_minMax_two(T a[], int n, int& indexOfMin, int& indexOfMax)
{
	if (n < 1) {
		throw illegalParameterValue("bad length of arr");
		return false;
	}
	indexOfMax = indexOfMin = 0; // 初始认为a[0]最大/小
	for (int i = 1; i < n; i++) {
		if (a[indexOfMax] < a[i]) indexOfMax = i;
		else if (a[indexOfMin] > a[i]) indexOfMin = i; // a[i]如果能比当前最大值大他肯定不会是最小值无需再比
		// 最多比较次数2(n-2)
	}
	return true;
}
