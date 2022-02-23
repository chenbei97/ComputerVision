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
	indexOfMax = indexOfMin = 0; // ��ʼ��Ϊa[0]���/С
	for (int i = 1; i < n; i++) {
		if (a[indexOfMax] < a[i]) indexOfMax = i;
		if (a[indexOfMin] > a[i]) indexOfMin = i;
		// �Ƚϴ���Ϊ2(n-2)
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
	indexOfMax = indexOfMin = 0; // ��ʼ��Ϊa[0]���/С
	for (int i = 1; i < n; i++) {
		if (a[indexOfMax] < a[i]) indexOfMax = i;
		else if (a[indexOfMin] > a[i]) indexOfMin = i; // a[i]����ܱȵ�ǰ���ֵ�����϶���������Сֵ�����ٱ�
		// ���Ƚϴ���2(n-2)
	}
	return true;
}
