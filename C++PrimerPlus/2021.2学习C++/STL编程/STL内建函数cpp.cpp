#include "contanter.h"
/*
STL内建了一些函数对象可以直接使用，产生的对象和用法与一般函数完全相同
需要引入头文件<functional>
<1>算数仿函数
			1.1 template<class T> T plus<T>  // +
			1.2 template<class T> T minus<T> // -
			1.3 template<class T> T multiplies<T> // *
			1.4 template<class T> T divides<T> //  / 
			1.5 template<class T> T modulus<T> // 取模
			1.6 template<class T> T negate<T> // 取反
<2>关系仿函数
			2.1  template<class T> bool equal_to<T> // =
			2.2  template<class T> bool not_equal_to<T> // !=
			2.3  template<class T> bool greater<T> // >
			2.4  template<class T> bool greater_equal<T> // >=
			2.5  template<class T> bool less<T>// <
			2.6  template<class T> bool less_equal<T> // <=
<3>逻辑仿函数
			3.1 template<class T> bool logical_and<T> // 
			3.2 template<class T> bool logical_or<T> // 
			3.3 template<class T> bool logical_not<T> // 

*/
void printvector(const vector<int>& v)
{
	for (vector<int> ::const_iterator it = v.begin(); it != v.end(); it++)
	{
		cout << (*it) << " ";
	}
	cout << endl;
}
void printvector(const vector<bool>& v)
{
	for (vector<bool> ::const_iterator it = v.begin(); it != v.end(); it++)
	{
		cout << (*it) << " ";
	}
	cout << endl;
}
void test_0038()
{
	//1.1 template<class T> T plus < T>  // +
	plus<int> p;
	cout << p(10, 20) << endl;
	//	1.6 template<class T> T negate<T> // 取反
	negate<int>  n;
	cout << n(50) << endl;
	// 2.1  template<class T> bool greater<T> // =
	vector<int> v;
	v.push_back(10);
	v.push_back(30);
	v.push_back(40);
	v.push_back(5);
	printvector(v);
	// 不再需要自定义仿函数
	greater<int> g;
	sort(v.begin(), v.end(), g);
	spilit_line();
	printvector(v);
	// 3.1 template<class T> bool logical_and<T> 
	//  将原始容器取反后放入目标容器
	vector<bool>  v1;
	v1.push_back(true);
	v1.push_back(false);
	v1.push_back(true);
	vector < bool > v2; // 目标容器
	v2.resize(v1.size());// 开辟空间
	printvector(v1);
	transform(v1.begin(), v1.end(),v2.begin(), logical_not<bool>());
	printvector(v2);
}

int incline_function()
//int main()
{
	test_0038();

	return 0;
}