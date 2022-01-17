#include <iostream>
#include "charter8_arrayStack.h"
using namespace std;
arrayStack<int> charter8_tower[4];
void towerOfHanoi_byStack(int);
void moveTopDisk(int, int, int, int);
void _charter8_towerOfHanoi_byStack()
{
	towerOfHanoi_byStack(4);
}
void towerOfHanoi_byStack(int n )
{
	for (int d = n; d > 0; d--)
		charter8_tower[1].push(d);//��ʼ״̬,��x�Ѵ���ӵ�С����(����������)ѹ��ջ,��y,zΪ��
	moveTopDisk(n, 1, 2, 3);
}
void moveTopDisk(int n , int x , int y, int z)
{
	if (n > 0)
	{
		moveTopDisk(n - 1, x, z, y);// �ƶ���x��Ԫ�ص�z
		int d = charter8_tower[x].top(); // ÿ�δ�1����pop��Ԫ�ر�push������1����
		charter8_tower[x].pop();
		charter8_tower[y].push(d);
		cout << "mov top disk "<<d<<" from tower " << x << " to top of tower " << y << endl;
		moveTopDisk(n - 1, z, y, x); // �ƶ���z��Ԫ�ص�y
	}
}