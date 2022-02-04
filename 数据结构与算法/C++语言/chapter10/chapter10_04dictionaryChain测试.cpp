#include "chapter10_dictionaryChain.h"
#include <iostream>
void _chapter10_dictionaryChain_testVode()
{
	dictionaryChain<int, int> z; // 使用int,int可以进行比较
	pair<int, int> p; // 因为insert是通过new实现,p可以反复使用,只是提供1个数值

	p.first = 2; p.second = 10;z.insert(p); 
	p.first = 10; p.second = 50;z.insert(p);
	p.first = 6; p.second = 30;z.insert(p);
	p.first = 8; p.second = 40;z.insert(p);
	p.first = 1; p.second = 5;z.insert(p);
	p.first = 12; p.second = 60;z.insert(p);
	cout << "chain size is " << z.size() << endl;
	cout << "The chain's " << z << endl; // 打印顺序是按照key从小到大的
	// find返回的是pairNode的成员element键值对指针,访问second成员使用->运算符
	cout << "key = 12 " << " value is " << z.find(12)->second << endl;
	z.insert(pair<int, int>{12, 600});
	cout << "key = 12 " << " value is " << z.find(12)->second << endl; // 覆写

	z.erase(1);z.erase(2);z.erase(6);
	cout << "After erase,the chain's " << z << endl;

}