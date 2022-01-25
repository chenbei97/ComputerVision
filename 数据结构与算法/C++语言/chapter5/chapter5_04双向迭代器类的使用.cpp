#include "chapter5_bidirectIterator.h"
#include <iostream>
void _chapter5_bidirectional_iterator()
{
	// 把类的实现和声明写在1个头文件就可以直接使用了
	_chapter5_bidirectIterator<int> iterator;
	int x[5] = { 3,7,9,2,6 };
	int count = 0;
	// 简单来说在charter5_03迭代器的概念.cpp中的迭代器y需要自己先定义指向一个数组
	// 具体的y是有++,--,*等操作的,因为指针本身是带有这些操作的
	// 本文件中是定义一个自己的指针类型,也可以叫迭代器
	// 迭代器带有复制构造
	for (iterator = x; iterator != x + 5; iterator++)
	{
		std::cout << "x[" << count << "] =" << *iterator<< "   ";
		count++;
	}
	std::cout << std::endl;
	iterator = x; // 重新指向开头
	// 比较前+和后+的区别
	printf("iterator++的表达式值没变,"
		"使用的变量依然是自增之前的为x[0]=3,即*iterator++ = %d\n", *iterator++);
	printf("表达式计算结束后,iterator自增,此时检验是否等于x[1]=7,*iterator = %d\n", *iterator);
	printf("此时使用*++iterator,结果应该是x[2]=9,变量先+然后使用,表达式为+后的结果,检验*++iterator = %d\n", *++iterator);
    // --操作符同理  
	iterator.print_position(); // the current pointer position value is 9
	_chapter5_bidirectIterator<int>* piterator = &iterator;
	piterator->print_position(); // the current pointer position value is 9
	// 测试->箭头运算符
	(&iterator)->print_position();// the current pointer position value is 9
}