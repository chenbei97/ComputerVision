#include "chapter17_container.h"
#include "chapter12_maxHeap.h"
#include <iostream>
using namespace std;
// theBoxes代表箱子们,capacity代表允许的总重量,x为最优解
void containerLoading(container* theBoxes, int capacity, int numberOfBoxes, int* x);
void _chapter17_containerLoading() {
	container* theBoxes = new container[11]; // 下标0弃用
	for (int i = 1; i <= 10; i++) {
		theBoxes[i].id = i;
		theBoxes[i].weight = i * 5;
	}
	// 5,10,15,20,25,30,35,  40,45,50
	// Σ{5->35}=140,后边的就超了
	int* x = new int [11]; // 最优解
	int capacity = 150; //最多承载150
	containerLoading(theBoxes, capacity, 10, x);
	cout << "the best x is\n";
	for (int i = 1; i <= 10; i++) {
		cout << "(" << theBoxes[i].id << "," << x[i] << ")  ";
	} // 7个1,3个0
	cout << endl;
}
void containerLoading(container* theBoxes, int capacity,
	int numberOfBoxes, int* x) {
	// 使用1个排序按照重量从小到大排,这里为了简单
	// 测试的案例就已经从小到大的重量
	// 为何从小到大排呢?贪婪算法总是找最小的尽可能让数量多
	int n = numberOfBoxes;
	for (int i = 1; i <= n; i++) {
		x[i] = 0; // 先全部初始化为0
	}

	// capcaity是剩余的容量
	for (int i = 1; i <= n && theBoxes[i].weight <= capacity; i++) {
		x[theBoxes[i].id] = 1; // 按照货箱编号存放在x的对应索引
		capacity -= theBoxes[i].weight; //减去使用过的货箱重量
	}
}