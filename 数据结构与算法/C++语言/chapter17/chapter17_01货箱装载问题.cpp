#include "chapter17_container.h"
#include "chapter12_maxHeap.h"
#include <iostream>
using namespace std;
// theBoxes����������,capacity���������������,xΪ���Ž�
void containerLoading(container* theBoxes, int capacity, int numberOfBoxes, int* x);
void _chapter17_containerLoading() {
	container* theBoxes = new container[11]; // �±�0����
	for (int i = 1; i <= 10; i++) {
		theBoxes[i].id = i;
		theBoxes[i].weight = i * 5;
	}
	// 5,10,15,20,25,30,35,  40,45,50
	// ��{5->35}=140,��ߵľͳ���
	int* x = new int [11]; // ���Ž�
	int capacity = 150; //������150
	containerLoading(theBoxes, capacity, 10, x);
	cout << "the best x is\n";
	for (int i = 1; i <= 10; i++) {
		cout << "(" << theBoxes[i].id << "," << x[i] << ")  ";
	} // 7��1,3��0
	cout << endl;
}
void containerLoading(container* theBoxes, int capacity,
	int numberOfBoxes, int* x) {
	// ʹ��1��������������С������,����Ϊ�˼�
	// ���Եİ������Ѿ���С���������
	// Ϊ�δ�С��������?̰���㷨��������С�ľ�������������
	int n = numberOfBoxes;
	for (int i = 1; i <= n; i++) {
		x[i] = 0; // ��ȫ����ʼ��Ϊ0
	}

	// capcaity��ʣ�������
	for (int i = 1; i <= n && theBoxes[i].weight <= capacity; i++) {
		x[theBoxes[i].id] = 1; // ���ջ����Ŵ����x�Ķ�Ӧ����
		capacity -= theBoxes[i].weight; //��ȥʹ�ù��Ļ�������
	}
}