#include "charter5_vectorList.h"
#include <numeric>
#include <algorithm>
using namespace std;
void _charter5_vector_test();
void _charter5_linearList_by_vector()
{
	// 对容器的性质进行测试,便于对charter5_vectorList.h中vector的使用进行解释
	_charter5_vector_test();
	
	// 对实现的vectorList进行测试
	_charter5_linearList<double>* x = new _charter5_vectorList<double>(20); // 父类指针可以指向子类指针
	// 但是x没有子类的方法,即不存在x->capacity();
	_charter5_vectorList<int> y(2), z; // 直接创建实例,子类存在capacity()方法
	cout << "y.capacity() = " << y.capacity() << endl;
	cout << "Initial size of x, y, and z = "
		<< x->size() << ", " // size是共有的方法
		<< y.size() << ", "
		<< z.size() << endl;

	// 对insert函数测试
	y.insert(0, 2);
	y.insert(1, 6);
	y.insert(0, 1);
	y.insert(2, 4);
	y.insert(3, 5);
	y.insert(2, 3);
	cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
	cout << "Size of y = " << y.size() << endl;
	cout << "Capacity of y = " << y.capacity() << endl;
	if (y.empty()) cout << "y is empty" << endl;
	else cout << "y is not empty" << endl;
	y.output(cout);
	cout << endl << "Testing overloaded <<" << endl;//直接打印也是可以的
	cout << y << endl;

	// 测试 indexOf
	int index = y.indexOf(4);
	if (index < 0) cout << "4 not found" << endl;
	else cout << "The index of 4 is " << index << endl;
	index = y.indexOf(7);
	if (index < 0) cout << "7 not found" << endl;
	else cout << "The index of 7 is " << index << endl;

	// 测试get
	cout << "Element with index 0 is " << y.get(0) << endl;
	cout << "Element with index 3 is " << y.get(3) << endl;

	// 测试erase
	y.erase(1);
	cout << "Element 1 erased" << endl;
	cout << "The list is " << y << endl;
	y.erase(2);
	cout << "Element 2 erased" << endl;
	cout << "The list is " << y << endl;
	cout << "Size of y = " << y.size() << endl;
	cout << "Capacity of y = " << y.capacity() << endl;
	if (y.empty()) cout << "y is empty" << endl;
	else cout << "y is not empty" << endl;

	// 测试异常处理
	try { y.insert(-3, 0); }
	catch (illegalIndex e)
	{
		cout << "Illegal index exception" << endl;
		cout << "Insert index must be between 0 and list size" << endl;
		e.outputMessage();
	}

	//测试复制构造
	_charter5_vectorList<int> w(y);
	y.erase(0);
	y.erase(0);
	cout << "w should be old y, new y has first 2 elements removed" << endl;
	cout << "w is " << w << endl;
	cout << "y is " << y << endl;

	//  测试迭代器
	y.insert(0, 4);
	y.insert(0, 5);
	y.insert(0, 6);
	y.insert(0, 7);
	for (_charter5_vectorList<int>::iterator i = y.begin(); //iterator使用了别名实际上就是vector自带的
		i != y.end(); i++)
		cout << *i << "  ";
	cout << endl;

	// 测试3个stl的方法
	reverse(y.begin(), y.end());
	cout << "The reversed list is " << y << endl;
	int sum = accumulate(y.begin(), y.end(), 0);
	cout << "The sum of the elements is " << sum << endl;
	sort(y.begin(), y.end());
	cout << "The sorted list is " << y << endl;
	sort(y.begin(), y.end(), greater<int>());
	cout << "The list is descending order is " << y << endl;

}
void _charter5_vector_test()
{
	vector<int> arrint1(10);
	vector<int>arrint2(arrint1); // 存在这种构造函数
	arrint2.insert(arrint2.begin(), 10, 2); //插入10个2
	cout << arrint2.capacity() << endl; // 容量自动倍增=20
	arrint2.insert(arrint2.end(), 5);
	cout << arrint2.capacity() << endl; // 尾插又加10
	// arrint2.insert(3, 8);直接插入位置3是不允许的,第1个参数是迭代器类型
	for (vector<int>::const_iterator it = arrint2.begin(); it != arrint2.end(); it++)
		cout << *it << "   ";
	cout << endl;
	printf("arrint2[5] = %d\n", arrint2[5]); // arrint2[5] = 2
}