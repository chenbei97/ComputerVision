#include <iostream>
using namespace std;
void _chapter7_irregular_array2d()
{
	int rows = 5;
	int lengths[5] = { 6,3,4,2,7 }; // 每一行的长度
	// 声明1个二维数组并分配所需要的行数
	// 不过这个二维数组是用指针数组来间接定义的
	int** arr = new int* [rows]; // 指向指针数组的指针为**类型
	//  指针的类型怎么看？去掉名字即可,即int**类型
	// 指针指向的类型?不仅去掉名字还要去掉名字左边的1个*,即int *类型
	// int * 类型可以是地址也可以是地址数组
	// int *[rows] 就是 int *[] 地址数组类型,也就是俗称的指针数组

	for (int i = 0; i < rows; i++)
		arr[i] = new int[lengths[i]]; // arr[i]也是个指针,指向一维数组本身
	
	// 不规则数组的遍历
	for (int i = 0; i < rows; i++) 
	{
		for (int j = 0; j < lengths[i]; j++)
		{
			arr[i][j] = i * rows + j + 1;
		}
	}
	for (int i = 0; i < rows; i++)
	{
		int* t = arr[i];
		for (int j = 0; j < lengths[i]; j++)
			cout << *t++ << "  ";
	}
	cout << endl;
}