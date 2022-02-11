#include "chapter12_maxHeap.h"
void _chapter12_maxHeap_testCode()
{
	maxHeap<int> h(4);
	h.push(21);
	h.push(15);
	h.push(20);

	cout << "heap size is " << h.size() << endl;
	cout << "heap capacity is " << h.capacity() << endl;
	cout << h << endl;

	h.push(14);
	cout << "heap size is " << h.size() << endl;
	cout << "heap capacity is " << h.capacity() << endl;
	h.push(10);
	cout << "heap size is " << h.size() << endl;
	cout << "heap capacity is " << h.capacity() << endl;
	h.push(2);
	/*
				21
			   /   \
			15    20
		   /   \    /
		14   10 2
	array = [ ][21][15][20][14][10][2]
	*/
	cout << h << endl; // 21  15  20  14  10  2


	cout << "The max element is " << h.top() << endl;
	h.pop();
	cout << h << endl;
	cout << "The max element is " << h.top() << endl;
	h.pop();
	cout << h << endl;
	cout << "The max element is " << h.top() << endl;
	h.pop();
	cout << "heap size is " << h.size() << endl; // 15  14  2  10
	cout << "heap capacity is " << h.capacity() << endl; // heap capacity is 8
	/*
			15
		   /   \
		14    2
		/
	  10
	*/

	// test initialize
	int z[11] = { 0,20,12,35,15,10,80,30,17,2,1 };
	h.initialize(z, 10);
	h.push(0);
	cout << "heap size is " << h.size() << endl;
	cout << "heap capacity is " << h.capacity() << endl;
	cout << h << endl;
	// 80  17  35  15  10  20  30  12  2  1  0

	cout << "测试新的数组" << endl;
	maxHeap<int> y(6);
	int t[6 + 1] = { 0,21,15,20,14,10,2 };
	y.initialize(t,6);
	y.push(1);
	cout << "heap size is " << y.size() << endl;
	cout << "heap capacity is " << y.capacity() << endl;
	cout << y << endl;
}