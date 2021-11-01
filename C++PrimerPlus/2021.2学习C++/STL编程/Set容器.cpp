#include "contanter.h"
/*
<1>集合容器set特点
		所有元素在插入时自动被排序
		本质set/multiset属于关联式容器，底层结构是二叉树实现
<2>set构造函数和赋值
		2.1 set<T> st ; // 模板实现类实现 ，默认构造函数  vector<int>  v
		2.2 set(const set &st) ; // 拷贝构造函数
		2.3 set &operator = (const set &st) ;
<3>set大小和交换
		3.1 empty() ; // 判断容量是否为空
		3.2 swap(st);  // 交换
		3.3 size(); // 长度
<4>set插入和删除
		4.1 insertelem) ;   //插入数据只有insert
		4.2 clear() ;
		4.3 erase(pos) ;
		4.4 erase(beg ,end) ;
		4.5 erase(elem);
<5>set查找和统计
		5.1 find(key); // key存在返回该键的元素迭代器 不存在返回set.end()
		5.2 count(key) ; // 统计key个数 = 0 or 1
<6>set和multiset区别
		set不允许容器有重复元素，multiset可以有
		set插入数据时会返回结果 表示插入是否成功
		multiset不会检测数据 因此可以插入重复数据
<7>pairr对组的创建
		成对出现的数据可以利用对组返回两个数据
		7.1 pair<type,type> p (value1 , value2) ;
		7.2 pair<type,type> p = make_pair (value1 , value2) ;
<8>set内置类型指定排序规则
		set默认升序，利用仿函数可以改变排序规则 : 重载()
<9>set自定义数据类型指定排序规则
		


*/
void spilit_line()
{
	cout << "----------------------------分割线----------------------------" << endl;
};
class Person1
{
public:
	int _age;
	string _name;
	Person1(string name,int age)
	{
		
		this->_age = age;
		this->_name = name;
	}
};
class comparePerson
{
public:
	bool operator() (const Person1 & p1, const Person1 & p2) const
	{
		if (p1._age == p2._age) // 名字升序
		{
			return p1._name < p2._name;
		}
		else
		{
			return p1._age > p2._age;
		}
	}
};
void printSet(const set<int>& st);
class My_Compare
{
public:
	bool operator ()  (int v1, int v2) const
	{
		return v1 > v2;
	}
};
void test_0033()
{
	// 0. 正常默认升序
	set<int> s1;
	s1.insert(10);
	s1.insert(20);
	s1.insert(30);
	printSet(s1);
	// 1.set内置类型指定排序规则
	set<int , My_Compare> s2; // 利用仿函数降序
	s2.insert(10);
	s2.insert(20);
	s2.insert(30);
	// printSet(s2); 不能再直接遍历
	// 插入之前就制定好规则
	for (set<int, My_Compare> ::iterator it = s2.begin(); it != s2.end(); it++)
	{
		cout << "仿函数降序输出：" << *it << " ";
	}
	cout << endl;

	// 2.set自定义数据类型指定排序规则
	Person1 p1("A", 18);
	Person1 p2("B", 21);
	Person1 p3("C", 30);
	Person1 p4("D", 18);
	Person1 p5("E", 19);
	Person1 p6("F", 18);
	// 自定义数据类型不能直接插入 必须制定规则去排序插入
	set<Person1, comparePerson>  s;
	s.insert(p1);
	s.insert(p2);
	s.insert(p3);
	s.insert(p4);
	s.insert(p5);
	s.insert(p6);
	for (set<Person1> ::const_iterator it = s.begin(); it != s.end(); it++)
	{
		cout << "姓名：" <<(*it)._name <<" " << "年龄："<<(*it)._age<<  endl;
	}

}
void printSet(const set<int>& st)
{
	{
		for (set<int> ::const_iterator it = st.begin(); it != st.end(); it++)
		{
			cout << (*it) << endl;
		}
	}
}
void test_0032()
{
	set<int> st;
	// 插入数据只有insert
	st.insert(10);
	st.insert(10);
	st.insert(11);
	st.insert(12);
	printSet(st);
	set<int> s1(st);
	set<int> s2;
	s2 = s1;
	//5.1 find(key); // key存在返回该键的元素迭代器 不存在返回set.end()
	set<int> ::iterator pos = s1.find(10);
	if (pos != s1.end())
	{
		cout << "找到元素为："<<* pos <<endl;
	}
	else
	{
		cout << "未找到" << endl;
	}
	int num = s1.count(10);
	cout << "个数为：" <<num << endl;

	//set和multiset区别
	pair<set<int> ::iterator, bool> ret = s1.insert(100);
	if (ret.second)
	{
		cout << "数据插入成功" << endl;
	}
	else
	{
		cout << "数据插入失败" << endl;
	}
	multiset<int> s5;
	s5.insert(100);
	s5.insert(100);
	s5.insert(100);
	cout << "multiset：100的个数为" <<s5.count(100)<< endl;
	//成对出现的数据可以利用对组返回两个数据
	/*	7.1 pair<type, type> p(value1, value2);*/
	pair<string, int> p("tom", 18);
	cout << "姓名：" << p.first <<"年龄："<< p.second << endl;
	//	7.2 pair<type, type> p = make_pair(value1, value2);
	pair<string, int> p2 = make_pair("tom", 18);
	cout << "姓名：" << p2.first << "年龄：" << p2.second << endl;
}
int set_containter()
//int main()
{
	//list_containter();
	//test_0032();
	 test_0033();
	return 0;
}