#include <iostream>
using namespace std;
/*内存分区模型
<程序运行前分成2个区 : 代码区和全局区>
1.代码区 : 存放函数体的二进制代码,操作系统进行管理(共享、只读)
2,全局区 : 存放全局变量和静态变量以及常量(程序运行结束时操作系统释放)
3.栈区 : 编译器自动分配和释放 , 存放函数的参数值，局部变量等
注意事项：不要返回局部变量的地址,栈区开辟的数据由编译器自动释放
4.堆区 : 程序员分配和释放 程序员不释放程序结束时操作系统回收
在C++中主要利用new开辟新内存
*/
//int* func1() // 此函数必须注释掉否则出错
//{
//	int a = 0; // 栈区存放形参、局部变量
//	return  & a;
//}
int* func2()
{
	// 指针p本质也是局部变量存放在栈区,但指针保存的数据在堆区
	int* p = new int(100); //返回的是地址所以用指针接收
	return p;
}
/*
全局区包括 : 全局变量、const修饰的全局变量(全局常量)、静态变量和字符串常量
非全局区 ： 局部变量、const修饰的局部变量(局部常量)
*/
int c = 10;
const int d = 10;
void Memory_Partition_model()
{
	//int main() {
		//普通局部变量
	int a = 10;
	//cout << &a << endl;
	cout << "普通局部变量地址\t" << (int)&a << endl;

	//静态变量
	static int b = 10;
	cout << "静态变量地址\t" << (int)&b << endl;

	// 全局变量
	cout << "全局变量地址\t" << (int)&c << endl;

	//常量
	//1.字符串常量
	cout << "字符串常量地址\t" << (int)&"Hello World " << endl;
	//2.const修饰的变量
	//2.1 const修饰的全局变量
	cout << "const修饰的全局变量地址\t" << (int)&d << endl;
	// 2.2 const修饰的局部变量
	const int e = 10;
	cout << "const修饰的局部变量地址\t" << (int)&e << endl;


	//int* p1 = func1();
	//cout << *p1 << endl; //局部变量无法解引用

	int* p2 = func2();
	cout << *p2 << endl; // new 创建的堆区数据地址可以解引用
	//system("pause");
	//return 0;
}