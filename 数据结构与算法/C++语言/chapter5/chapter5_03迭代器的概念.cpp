/*
​	迭代器是一个指针，指向开头或者结尾，可以通过算术运算得到一个数组的任意位置，然后解引用即可访问元素。

​	C++的STL定义了5种迭代器，所有迭代器都具备操作符==、!=、解引用操作符*：

​	1.输入迭代器：额外提供指向元素的只读操作、前++和后++操作符

​	2.输出迭代器：额外提供指向元素的写操作和++操作符

​	3.向前迭代器：额外提供++操作符

​	4.双向迭代器：额外提供++和--操作符

​	5.随机访问迭代器：最一般的迭代器，可以随意的实现跳跃移动，也可以使用指针算数运算实现跳跃移动，如下方的数组迭代器y。
*/
#include <stdio.h>
#include <iostream>
void _simple_iterator();
void _chapter5_iterator_concept()
{
	_simple_iterator();
}
void _simple_iterator()
{
	const int n = 5;
	int x[n] = { 0,1,2,3,4 };
	int count = 0;
	printf("使用迭代器: \n");
	for (int* y = x; y != x + n; y++)
	{
		printf("x[%d] = %d    ",count,*y );
		count++;
	}
	printf("\n不使用迭代器: \n");
	// <=> 等价于 下方代码
	for (int i = 0; i != n; i++)
		std::cout << "x["<<i<<"] = " <<x[i]<< "   ";
	std::cout <<std::endl;
}
