#include "chapter12_minHeap.h"
void _chapter12_minHeap_testCode()
{
	minHeap<int> h(4);
	h.push(21);
	h.push(15);
	h.push(20);
	h.push(14);
	h.push(10);
	h.push(2);
	cout << "heap size is " << h.size() << endl;
	cout << "heap capacity is " << h.capacity() << endl;
	cout << h << endl; // 2  14  10  21  15  20
		/*
				2
			   /   \
			14    10
		   /   \    /
		21   15 20
	*/

	h.pop();
	h.pop();
	h.pop();
	cout << "The min element is " << h.top() << endl;
	cout << h << endl;
	/*
			15
		   /   \
		21    20
	*/

	// test initialize
	int z[11] = { 0,20,12,35,15,10,80,30,17,2,1 };
	h.initialize(z, 10);
	h.push(0);
	cout << "heap size is " << h.size() << endl;
	cout << "heap capacity is " << h.capacity() << endl;
	cout << h << endl;
	// 0  1  30  15  2  80  35  17  20  12  10
}