#include "chapter12_maxHblt.h"
#include <iostream>
using namespace std;
void _chapter12_maxHblt_testCode() {
	maxHblt<int> h, j;
	int a[6] = { 0, 7, 9, 1, 8, 11 };
	h.initialize(a, 5);
	cout << "One tree level postorder is" << endl;
	h.output(); // ²ã´Î±éÀú
	cout << "Tree size is " << h.size() << endl;
	
	int b[5] = { 0, 2, 6, 4, 9 };
	j.initialize(b, 4);
	cout << "Other tree level postorder is" << endl;
	j.output();
	cout << "Tree size is " << j.size() << endl;
	
	h.merge(j);
	cout << "After melding, the tree level postorder is" << endl;
	h.output();
	cout << "Tree size is " << h.size() << endl;

	int w = h.top();
	h.pop();
	int x = h.top();
	h.pop();
	int y = h.top();
	h.pop();
	int z = h.top();
	h.pop();
	cout << "After popping four elements, the tree is" << endl;
	h.output();
	cout << "Tree size is " << h.size() << endl;
	cout << "The popped elements, level order, are" << endl;
	cout << w << "  " << x << "  " << y << "  " << z << endl;

	h.push(10);
	h.push(20);
	h.push(5);
	cout << "After pushing 10, 20 & 5, the tree is" << endl;
	cout << "Leftist tree level postorder" << endl;
	h.output();
	cout << "Tree size is " << h.size() << endl;

	h.push(15);
	h.push(30);
	h.push(2);
	cout << "After pushing 15, 30 & 15, the tree is" << endl;
	cout << "Leftist tree level postorder" << endl;
	h.output();
	cout << "Tree size is " << h.size() << endl;

	cout << "The max element is " << h.top() << endl;
	h.pop();
	h.output();

	while (true)
	{
		try
		{
			x = h.top();
			h.pop();
			cout << "Popped " << x << endl;
			cout << "Tree size is " << h.size() << endl;
		}
		catch (queueEmpty) { break; }
	}
}