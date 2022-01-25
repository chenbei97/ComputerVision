#include "chapter6_chainListWithIteratorExtend.h"
#include <numeric>
void _chapter6_chainListWithIteratorExtend_testCode()
{
	// 测试insert、size、output和重载运算符
	_chapter6_chainListWithIteratorExtend<int> y;
	cout << y.empty() << endl;
	y.insert(0, 2);
	cout << y.empty() << endl; 
	y.insert(1, 6);
	y.insert(0, 1);
	y.insert(2, 4);
	y.insert(3, 5);
	y.insert(2, 3);
	y.output(cout);
	cout << endl;
	cout << "Size of y = " << y.size() << endl;
	cout << y << endl; // 重载运算符和父类成员firstNode,listSize一样被继承了且没有覆盖

	// 测试erase
	y.erase(5);
	cout << y << endl;

	// 测试迭代器的前++和后++
	for (_chapter6_chainListWithIteratorExtend<int>::_chapter6_iterator i = y.begin(); // 类也被直接继承
		i != y.end(); i++)
		cout << *i << "  ";
	cout << endl;
	for (_chapter6_chainListWithIteratorExtend<int>::_chapter6_iterator i = y.begin();
		i != y.end(); ++i)
	{
		cout << *i << "  ";
		*i += 1;
	}
	cout << endl;

	int sum = accumulate(y.begin(), y.end(), 0);
	cout << "The sum of the elements is " << sum << endl;

	y.clear();
	y.push_back(1);
	y.push_back(2);
	y.push_back(3);
	cout << "Size of y = " << y.size() << endl;
	cout << y << endl;
	y.insert(3, 4);
	y.insert(0, 0);
	cout << "List y should be 0 1 2 3 4" << endl;
	cout << "Size of y = " << y.size() << endl;
	cout << y << endl;

	y.erase(4);
	y.erase(0);
	y.push_back(6);
	cout << "List y should be 1 2 3 6" << endl;
	cout << "Size of y = " << y.size() << endl;
	cout << y << endl;
}