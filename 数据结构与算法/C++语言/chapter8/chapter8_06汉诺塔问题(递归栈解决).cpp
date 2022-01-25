#include <iostream>
#include "chapter8_arrayStack.h"
using namespace std;
arrayStack<int> charter8_tower[4];
void towerOfHanoi_byStack(int);
void moveTopDisk(int, int, int, int);
void _chapter8_towerOfHanoi_byStack()
{
	towerOfHanoi_byStack(4);
}
void towerOfHanoi_byStack(int n )
{
	for (int d = n; d > 0; d--)
		charter8_tower[1].push(d);//初始状态,塔x把大碟子到小碟子(用整数代替)压入栈,塔y,z为空
	moveTopDisk(n, 1, 2, 3);
}
void moveTopDisk(int n , int x , int y, int z)
{
	if (n > 0)
	{
		moveTopDisk(n - 1, x, z, y);// 移动塔x的元素到z
		int d = charter8_tower[x].top(); // 每次从1个塔pop的元素被push到另外1个塔
		charter8_tower[x].pop();
		charter8_tower[y].push(d);
		cout << "mov top disk "<<d<<" from tower " << x << " to top of tower " << y << endl;
		moveTopDisk(n - 1, z, y, x); // 移动塔z的元素到y
	}
}