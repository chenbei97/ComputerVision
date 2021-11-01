#include "contanter.h"
/*
<1>vector容器的概念
	v.rend() ; // 第一个元素位置的前一个
	v.begin();// 第一个元素位置
	v.insert(); // 插入
	v.rbegin();// 最后一个元素位置
	v.end(); // 最后一个元素位置的后一个
	v.push_back(); // 添加
	v.pop_back(); // 删除
	支持随机访问的迭代器
<2>vector容器的构造函数
	2.1 vector<T> v ; // 模板实现类实现 ，默认构造函数  vector<int>  v 
	2.2 vector(v.begin() , v.end()) ; // 将[ v.begin() , v.end() )区间(前闭后开)的元素拷贝给本身
	2.3 vector(n , elem) ; // 构造函数将n个elem拷贝给本身
	2.4 vector(const vector &vec) ; // 拷贝构造函数
<3>vector容器的赋值操作
	3.1 vector & operator=(const vector &vec) ; // v2 =v1 ;
	3.2 assign(beg,end) ; // [beg ,end) 拷贝数据
	3.3 assign(n,elem) ; // n个elem拷贝赋值
<4>vector容器的容量和大小
	4.1 empty() ; // 判断容量是否为空
	4.2 capacity();  // 容量
	4.3 size(); // 长度
	4.4 resize(int num) ; // 容器变长则以默认值0填充新位置 变短则删除
	4.5 resize(int num ,elem) ;  // 容器变长elem填充新位置,变短删除
<5>vector容器的插入和删除
	5.1 push_back(ele) ; // 尾部插入元素ele
	5.2 pop_back() ; // 删除最后一个元素
	5.3 insert(const_iterator pos , ele) ; // 迭代器指向位置pos插入元素ele
	5.4 insert(const_iterator pos , int count , ele) ; // 插入count个
	5.5 erase(const_iterator pos) ;  // 删除指向的位置元素
	5.6 erase(const_iterator start , const_iterator end) ;  // 删除从start到end之间元素
	5.7 clear(); // 清空
<6>vector容器的数据存取
	6.1 at(int idx) ; //返回索引idx的数据
	6.2 operator[] ; // 索引
	6.3 front() ; // 第一个数据元素
	6.4 back() ; // 最后一个数据元素
<7>vector容器的互换容器
	7.1 swap(vec) ; // 将vec与本身的元素互换
	7.2 可以用于收缩内存
<8>vector容器的预留空间
	8.1 减少vector动态扩展容量时的扩展次数
	8.2 reserve(int len) ; // 容器预留len个元素 ，预留位置不初始化 元素不可访问
	8.3 只分配内存不初始化
*/
void printVector(vector<int>& v);
void test_0027()
{
	// 7.1 swap(vec) ; // 将vec与本身的元素互换
	vector<int> v1;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i * i);
	}
	vector<int> v2;
	for (int i = 0; i < 10; i++)
	{
		v2.push_back(i );
	}
	v1.swap(v2);
	//printVector(v1);
	//printVector(v2);
	// 7.2 可以用于收缩内存
	vector<int> v3;
	for (int i = 0; i < 100000; i++)
	{
		v3.push_back(i);
	}
	cout << "v3的容量为：" <<v3.capacity()<< endl;
	cout << "v3的长度为：" << v3.size() << endl;
	v3.resize(3);
	cout << "v3的容量为：" << v3.capacity() << endl;	// 容量不会变
	cout << "v3的长度为：" << v3.size() << endl;
	vector<int>(v3).swap(v3);
	// vector<int>(v3) 为匿名对象 指向较小的内存
	// 匿名对象与v3交换了容器 原来的v3指向了小内存 而匿名对象大内存自动回收了
	cout << "v3的容量为：" << v3.capacity() << endl;	// 
	cout << "v3的长度为：" << v3.size() << endl;

	// 8.2 reserve(int len); // 容器预留len个元素 ，预留位置不初始化 元素不可访问
	
	
	int num = 0; // 统计动态开辟内存的次数
	int* p = NULL;
	vector<int> v4;
	// 利用reserve()预留空间 而不用反复动态开辟
	v4.reserve(100000);// 动态开辟内存次数为：1
	for (int i = 0; i < 100000; i++)
	{
		v4.push_back(i);
		if (p != &v4[0]) // 如果p指针不等于容器的首地址
		{
			p = &v4[0];
			num++;// 动态开辟时首地址总是变化 每次变化以后+1次且重新指向第一个元素首地址
		}
	}
	cout << "动态开辟内存次数为：" << num << endl;//动态开辟内存次数为：30
}
void printVector(vector<int>& v) // 容器类型
{
	for (vector<int> ::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << (*it) << endl;
	}
}
void test_0026()
{
	//2.1 vector<T> v; // 模板实现类实现 ，默认构造函数  vector<int>  v 
	vector<int> v1;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i * i);
	}
	//printVector(v1);
	//2.2 vector v(v.begin(), v.end()); // 将[ v.begin() , v.end() )区间(前闭后开)的元素拷贝给本身
	vector<int>v2(v1.begin(), v1.end());
	//printVector(v2);
	//2.3 vector(n, elem); // 构造函数将n个elem拷贝给本身
	vector<int> v3(10, 100);
	//printVector(v3);
	//2.4 vector(const vector & vec); // 拷贝构造函数 指向纯常量的引用
	vector<int> v4(v3);
	//printVector(v4);
	//3.1 vector & operator=(const vector & vec); // v2 =v1 ;
	vector<int> v5 = v1;
	//printVector(v5);
	//3.2 assign(beg, end); // [beg ,end) 拷贝数据
	vector<int> v6;
	v6.assign(v1.begin(), v1.end());
	//printVector(v6);
	//3.3 assign(n, elem); // n个elem拷贝赋值
	vector<int> v7;
	v7.assign(5, 10); // 赋值行为 上边是构造行为
	//printVector(v7);
	//4.1 empty(); // 判断容量是否为空
	//cout <<v1.empty() << endl;
	//4.2 capacity();  // 容量
	//cout << v1.capacity() << endl; // 动态随机的
	//4.3 size(); // 长度
	//cout << v1.size()<< endl;
	//4.4 resize(int num); // 容器变长则以默认值填充新位置 变短则删除
	v1.resize(8);
	//cout << v1.capacity() << endl;  // 19
	//cout << v1.size() << endl; //15
	//printVector(v1);
	//4.5 resize(int num, elem);  // 容器变长elem填充新位置,变短删除
	v1.resize(15,100);
	//printVector(v1);
	//5.4 insert(const_iterator pos, int count, ele); // 插入count个
	v1.insert(v1.begin(), 2, -40);
	//printVector(v1);
	//5.6 erase(const_iterator start, const_iterator end);  // 删除从start到end之间元素
	v1.erase(v1.begin());
	//printVector(v1);
	// 6.4 back(); // 最后一个数据元素
	cout << v1.back() << endl;
	

}
int vector_containter()
//int main()
{
	//string_containter();
	//test_0026();
    test_0027();
	return 0;
}