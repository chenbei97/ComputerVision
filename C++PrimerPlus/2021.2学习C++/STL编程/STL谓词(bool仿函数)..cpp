#include "contanter.h"
/*
1. 返回bool类型的仿函数为谓词
2. operator()接收一个参数为一元谓词，两个参数为二元谓词
3. 这里与之前的函数对象重载()不同，这里是利用类的构造函数重载
*/
// 1. 一元谓词
void print_weici(const vector<int>& v);
class behindfive
{
public:
	bool operator()( int val)
	{
		return val > 5;
	}

};
// 2.二元谓词
class two_sort
{
public:
	bool operator() (int v1 ,int v2)
	{
		return  v1 > v2;// 二元谓词升序
	}


};
void test_0037()
{
	vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(- i * 10 );
	}
	print_weici(v);
	sort(v.begin(), v.end());
	spilit_line();
	print_weici(v);
	// 利用二元仿函数改变排序规则
	sort(v.begin(), v.end(), two_sort());
	spilit_line();
	print_weici(v);
}
void print_weici(const vector<int> & v)
{
	for (vector<int> ::const_iterator it = v.begin(); it != v.end(); it++)
	{
		cout <<   (*it) << " ";
	}
	cout << endl;
}
void test_0036()
{
	vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	// fnd_if参数为 ：迭代器范围、谓词，返回迭代器
	vector<int> ::iterator pos  = find_if(v.begin(), v.end(), behindfive());
	if (pos == v.end())
	{
		cout << "未找到"<<endl;
	}
	else
	{
		cout << "找到了大于5数字的为：" <<(*pos)<< endl;
	}
}
int one_two_predicate()
//int main()
{
	// stl_func_object();
	test_0036();
	test_0037();
	return 0;
}