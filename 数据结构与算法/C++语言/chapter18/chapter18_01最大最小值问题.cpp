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
	// ��a[0,n-1]���ҳ������Сֵ
	if (n < 1) return false;
	if (n == 1) {
		minIndex = maxIndex = 0; 
		return true;
	}
	int start ; // ѭ�������ȡ����n����ż��

	if (n % 2 == 1) { // ����,�Ǿ��ó�1����Ϊ��ʼ�����Сֵ,���ż����Ԫ�ؿ��������Ƚ�
		minIndex = minIndex = 0; // a[0]��Ϊ��һ��ʼ������С��Ԫ��
		start = 1; // (1,2),(3,4)...���������Ƚ�
	}
	else { // ż��,�ó�1��ֵ��������,�����ó�2��,�����ȱȽ�2��Ԫ��
		if (a[0] > a[1]) { // �ȱȽ�2��Ԫ��a[0]��a[1]
			minIndex = 1;
			maxIndex = 0;
		}
		else {
			minIndex = 0;
			maxIndex = 1;
		}
		start = 2; // ��a[2]��ʼ�Ƚ�
	}

	// ʣ��Ԫ�رض���ż����
	for (int i = start; i < n; i += 2) {
		if (a[i] > a[i+1] ) { // ���ǰ1��Ԫ�ش�
			if (a[i] > a[maxIndex]) maxIndex = i; // ����ǰ1��Ԫ�غ�Ŀǰ���ıȽ�
			if (a[i + 1] < a[minIndex]) minIndex = i+1; // ��1��Ԫ�غ�Ŀǰ��С�ıȽ�
		}
		else { // ��1��Ԫ�ش�,�����÷�����
			if (a[i+1] > a[maxIndex]) maxIndex = i+1;
			if (a[i] < a[minIndex]) minIndex = i;
		}
	}
	return true;
}