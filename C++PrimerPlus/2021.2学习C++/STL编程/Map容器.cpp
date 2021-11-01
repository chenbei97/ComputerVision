#include "contanter.h"
/*
<1>map容器概念
		1.1 map的所有元素都是pair，第一个为key 第二个为value
		1.2 所有元素会根据键值自动排序
		1.3 map/muitimap属于关联式容器，底层为二叉树，multimap允许有重复key值的元素
<2>map构造和赋值
		2.1 map<T1,T2> mp ; // 默认构造
		2.2 map(const map &mp) ; //拷贝构造
		2.3 map& operator = (const map & mp) ; // 重载赋值
<3>map大小和交换
		3.1 size();
		3.2 empty();
		3.3 swap(mp);
<4>map插入和删除
		4.1 insert(elem) ;
					4.1.1 m.insert(pair<int, int>(1, 10)); //匿名赋值
					4.1.2 m.insert(make_pair(5, 50)); // 成对赋值
					4.1.3 m.insert(map<int, int> ::value_type(6, 60)); //作用域赋值
					4.1.4 m[7] = 70; // 函数重载赋值(不建议使用)不安全如果使用cout<<m[8]<<endl;又会新建新的值
		4.2 clear();
		4.3 erase(pos) ; //删除pos指定元素 返回下一个元素的迭代器
		4.4 erase(beg ,end) ; // 删除[beg,end)元素 返回下一个元素迭代器
		4.5 erase(key) ;// 删除key的元素
<5>map查找和统计
		5.1 find(key) ; // 查找key是否存在，存在返回key的迭代器否则返回set.end();
		5.2 count(key) ; // 统计key个数
<6>map排序
		6.1 默认按照key从小到大升序

<7>map案例员工分组
	

*/
class comparemap
{
public:
	bool operator () (int v1, int v2) const
	{
		return v1 > v2; // 升序
	}

};
void printmap(const map<int , int ,comparemap> & mp)
{
	for (map<int, int,comparemap> ::const_iterator it = mp.begin(); it != mp.end(); it++)
	{
		cout << "map的键为：" << (*it).first << "	" << "map的值为：" << (*it).second<< endl;;
	}
}
void test_0034()
{
	// 6.1 默认按照key从小到大升序 仿函数重载
	map <int, int ,comparemap> m;
	m.insert(pair<int, int>(1, 10)); //匿名赋值
	m.insert(pair<int, int>(2, 20));
	m.insert(pair<int, int>(3, 30));
	m.insert(pair<int, int>(4, 40));
	m.insert(make_pair(5, 50)); // 成对赋值
	m.insert(map<int, int> ::value_type(6, 60)); //作用域赋值
	m[7] = 70; // 函数重载赋值 不安全如果使用cout<<m[8]<<endl;又会新建新的值
	map<int, int ,comparemap>m2(m);
	map<int, int,comparemap>m3;
	m3 = m2;
	printmap(m3);
	//cout << "-------------------------分割线------------------------------" << endl;
	spilit_line();
	m3.erase(m3.begin());//按位置删除
	m3.erase(3); // 按key删除
	printmap(m3);
	multimap<int, int > m5;
	m5.insert(pair<int, int>(100, 100));
	m5.insert(pair<int, int>(100, 100));
	spilit_line();
	// 5.1 find(key); // 查找key是否存在，存在返回key的迭代器否则返回set.end();
	map<int, int> ::iterator pos = m5.find(100);
	if (pos != m5.end())
	{
		cout << "找到元素key=100的值为：" <<(*pos).second<< endl;
	}
	else
	{
		cout << "没有找到！" << endl;
	}
	//5.2 count(key); // 统计key个数
	cout << "key=100的个数为：" << m5.count(100) << endl;
}
int map_containter()
//int main()
{
	//set_containter();
	test_0034();
	return 0;
}