#include "all.h"
void printVector1(vector<int>& v) // 容器类型
{
	for (vector<int> ::iterator it = v.begin(); it != v.end(); it++) // front和back对应,begin和end对应
	{
		if (it != v.end() - 1)
			cout << (*it) << ", "; // it是指针
		else
			cout << (*it)<<endl;
	}
}
void printVector2(vector<int>& v)
{
	vector<int> ::iterator itBegin = v.begin();
	vector<int> ::iterator itEnd = v.end();
	while (itBegin != itEnd)
	{
		cout << *itBegin << endl;
		itBegin++;
	}
}
void printVector3(int  val) // 使用函数
{
	cout << val << endl;
}
class printVector4 // 使用类重载()作为函数对象
{
public:
	void operator()(int  val)
	{
		cout << val << endl;
	}
};
void Study_STL_String()
{
	cout << "Study_STL_String()：" << endl;
	const char* c = "cb";
	string s1() ,s2 , s3(c) ,s4(s3); // 不同的构造方式
	string s5 = s4 + "great";// 重载运算符
	s5.append("!"), s5.assign("hello c++"); // 一些方法的使用,追加和覆盖
	cout <<"	"<< s5 << endl;
}
void printDeque(const deque<int>& d) // 传入的是deque数据类型的引用传递 且是纯常量引用
{
	for (deque<int> ::const_iterator it = d.begin(); it != d.end(); it++)
	{
		// const 可以防止输出时误写操作
		// * it =100;
		cout << (*it) << " ";
	}
	cout << endl;
}
void Study_STL_Vector()
{
	vector<int> v1, v2(v1.begin(), v1.end()), v3(10, 100), v4(v3), v5 = v1;// 不同的构造方式

	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i * i); // 一些常用实例方法，添加元素，还有pop_back删除元素
	}
	cout <<"v1.empty()="<<v1.empty() <<" v1.capacity()="<< v1.capacity() 
		<< " v1.size()="<<v1.size() <<" v1.front()="<< v1.front() << " v1.back()="<<v1.back()<<endl;// 其他常用实例方法
	printVector1(v1);
	v1.erase(v1.begin(),v1.end()-1); // 擦除指定迭代器范围
	printVector2(v1);
	// 第三种遍历方式：利用STL提供的遍历算法
	for_each(v1.begin(), v1.end(), printVector3);
	for_each(v1.begin(), v1.end(), printVector4());
}
void Study_STL_Deque()
{
	deque<int> d1;
	for (int i = 0; i < 5; i++)
	{
		d1.push_back(-i);
	}
	printDeque(d1);
	// 其他操作和vector类似
}
void Study_STL()
{
	Study_STL_String();
	Study_STL_Vector();
	Study_STL_Deque();
	system("pause");
}