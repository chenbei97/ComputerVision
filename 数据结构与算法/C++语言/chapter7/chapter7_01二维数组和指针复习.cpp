#include <iostream>
using namespace std;
void _chapter7_array2D_pointer()
{
	cout << "1.一维指针" << endl;
	// 1.一维指针
	// 1.1 指向元素的指针
	int a = 5;
	int* pa = &a;
    // 1.2 指向数组本身(或者其首元素)的指针,可以通过指针遍历元素
	int as[5] = { 1,2,3,4,5 };
	int* pas_1 = as; // pa0s_1其实和pa0是一种类型的指针,都是int的地址
	int* pas_2 = &as[0]; // pa0s_2和pa0s_1也是1个类型的,而pa0s_2就是指向int的地址
	for (int i = 0; i < 5; i++)
		cout << pas_1[i] << "  " << pas_2[i] << "  " << as[i] << "  ";
	cout << endl; // 本质上2种指针是一个类型
	for (int i = 0; i++ < 5; pas_1++)
		cout << *pas_1 << "  ";
	cout << endl; // 解引用的方式也可以访问

	// 1.3 指向数组地址的指针,此时指针的遍历并没有意义,只是跳到下一个5元素数组的地址
	int (* pas_3)[5] = &as; // 这要求不仅是数组的指针,还必须是具有5个元素的数组的指针
	for (int i = 0; i < 5; i++)
		cout << (*pas_3)[i] << "  "; // 必须先解引用,成了数组再用[]索引,试图(*pa0s_3)++遍历是非法的
	cout << endl;
	cout << "2.二维指针" << endl;
	// 2.二维指针(不考虑指针数组的情况,就是简单的二维数组)
	cout << "2.1直接定义" << endl;
	// 2.1直接定义
	int b1[3][5] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 }; 
	for (int i = 0; i < 3; i++) // 2.1.1 数组[]访问
		for (int j = 0; j < 5; j++)
			cout << b1[i][j] << "  ";
	cout << endl;
	int(*pb1)[5] = b1; // 2.1.2 全局指针[][]访问
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 5; j++)
			cout << pb1[i][j] << "  ";
	cout << endl; 
	for (int i = 0; i < 3; i++) // 2.1.3 间接行指针访问
	{
		int* t = b1[i]; // b1是存储元素的一维数组
		for (int j = 0; j < 5; j++)
			cout << t[j] << "  ";
	}
	cout << endl;
	// 2.1.4 不能通过全局指针++的方式访问,此时的指针遍历没有意义
	for (int i = 0; i < 3; i++)
		cout << pb1[i] << "  " << * pb1[i]<<"  "; // pb1[i]是数组名,虽然也是地址但不是指针不能++
	cout << endl;
	// 如果希望通过全局指针++遍历元素,可以需要下方的间接定义(指针数组定义)
	cout << "2.2 间接定义" << endl;
	// 2.2 间接定义(用存放地址的一维数组int*来定义)
	int b0_1[5] = { 1,2,3,4,5 };
	int b0_2[5] = { 6,7,8,9,10 };
	int b0_3[5] = { 11,12,13,14,15 };
	int *b2[3] = { b0_1,b0_2,b0_3 }; // 相当于指针数组
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 5; j++)
			cout << b2[i][j] << "  "; // 2.2.1直接使用数组[]索引
	cout << endl;
	int** pb2 = b2; // 2.2.2 全局指针[][]访问,全局指针只有3个元素
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 5; j++)
			 cout << pb2[i][j] << "  "; 
	cout << endl;
	for (int i = 0; i < 3; i++)
		cout << *pb2[i] << "  "; // 只有3个元素,不能访问其他元素
	cout << endl;
	for (int i = 0; i++ < 3; pb2++) // 2.2.2 全局指针++只能访问头元素 
		for (int j = 0; j < 5; j++)
			//cout << *(pb2[j]) << "  "; // 不可用*(pb2[j])访问因为pb2[]取不到5
			cout << "  ";
	cout << endl;
	pb2 = b2; // 复位
	for (int i = 0; i < 3; i++)
	{
		int*t = pb2[i]; // 2.2.3 可以借助行指针索引
		for (int j = 0; j < 5; j++)
			// cout << t[j]   << "  "; // []可以访问
			cout << *t++ << "  "; // *(t++)也可
	}
	cout << endl; 
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 5; j++)
			cout << *b2[i]++ << "  "; // 2.2.5 指针++解引用,这里的b2[i]是指向数组名的指针而不是数组名
	cout << endl; // 但是会改变b2的位置
}