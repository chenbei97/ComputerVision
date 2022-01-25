#include <iostream>
using namespace std;
void towerOfHanoi_byRecursion(int, int, int, int);
void _chapter8_towerOfHanoi_byRecursion()
{
	towerOfHanoi_byRecursion(4, 1, 2, 3);//可以看出打印的信息条数为15条
}
void towerOfHanoi_byRecursion(int n , int towerx, int towery, int towerz)
{
	// 此程序并不是移动元素的程序，只是一个测试程序步的程序
	// 把n个碟子从x转移到y
	if (n > 0)
	{
		// 先把前n-1个碟子转移到z,最大的碟子就可以放在y
		// towerx,towery,towerz是塔的索引,可以看成arrayStack数组的1个元素
		// 按下方这样的顺序对不同的塔进行pop和push操作就可以完成调换
		cout << "n = " << n << " x = " << towerx << "  y = " << towery <<endl;
		towerOfHanoi_byRecursion(n-1,towerx, towerz, towery); 
		cout <<"tower "<< towerx << " is popping " << "and pushed in tower " << towery << endl;
		//cout << "mov top disk from tower " << towerx << " to top of tower " << towery << endl;
		// 之后就可以把z上的n-1个碟子移动到y
		towerOfHanoi_byRecursion(n - 1, towerz, towery, towerx);
		//cout << "mov top disk from tower " << towerz << " to top of tower " << towerx << endl;
	}
}
