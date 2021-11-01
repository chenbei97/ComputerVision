#include "contanter.h"
 /*
 <1>deque容器概念
		双端数据可以对头端进行插入删除操作
		vector对于头部插入效率低，数据量越大越低
		vector访问元素的速度会比deque快
		存在中控器记录每段缓冲器的地址,每段缓冲器存放了数据,分段连续所以访问比较慢
		deque迭代器支持随机访问
<2>deque构造函数
		2.1 deque<T> deq T ; // 默认构造
		2.2 deque(beg,end) ; // 将[beg , end)区间元素拷贝给本身
		2.3 deque(n ,elem) ;  // 将n个elem拷贝给本身
		2.4 deque(const deque &deq) ; // 拷贝构造函数
<3>deque赋值操作
		3.1 deque& operator=(const deque &deq) ;
		3.2 assign(beg , end) ;
		3.3 assign(n,elem) ;
<4>deque大小操作
		4.1 deque.empty() ;
		4.2 deque.size();
		4.3 deque.resize(num) ;
		4.4 deque.resize(num,elem) ; // 以elem来填充新位置
<5>deque插入和删除
		5.1 pop_front(elem) ; // elem为插入的数据 
		5.2 push_front(elem) ; 
		5.3 pop_back() ; 
		5.4 push_back();
		5.5 insert(pos ,elem) ; // 返回新数据的位置
		5.6 insert(pos , n, elem) ; // 插入n个elem 无返回值
		5.7 insert(pos, beg, end) ; // 插入{beg,end)的数据 无返回值
		5.8 clear();
		5.9 erase(beg,end) ; // 返回下一个数据的位置
		5.10 erase(pos) ; //删除pos位置数据 返回下一个数据的位置
<6>deque数据存储
		6.1 at(int idx) ; //返回索引idx所指的数据
		6.2 operator[] ; // 返回索引idx所指的数据
		6.3 front() ;// 第一个元素
		6.4 back() ; // 最后一个
		
<7>deque排序操作
		7.1 sort(iterator beg , iterator end); // 默认升序
		
 */
void printDeque(const deque<int>  &d) // 传入的是deque数据类型的引用传递 且是纯常量引用
{
	for (deque<int> :: const_iterator it = d.begin(); it != d.end(); it++)
	{
		// const 可以防止输出时误写操作
		// * it =100;
		cout << (*it) << " ";
	}
	cout << endl;
}
void test_0028()
{
	//2.1 deque<T> deq T; // 默认构造
	deque<int> d1;
	for (int i = 0; i < 5; i++)
	{
		d1.push_back( -i);
	}
	printDeque(d1);
	//2.2 deque(beg, end); // 将[beg , end)区间元素拷贝给本身
	deque<int> d2(d1.begin(), d1.end());
	printDeque(d2);
	//2.3 deque(n, elem);  // 将n个elem拷贝给本身
	deque<int>d3(10, 100);
	printDeque(d3);
	//2.4 deque(const deque & deq); // 拷贝构造函数
	deque<int>d4(d3);
	printDeque(d4);
	// 7.1 sort(iterator beg, iterator end);
	sort(d1.begin() ,d1.end());
	printDeque(d1);
}
int deque_containter()
//int main()
{
	//vector_containter();
	test_0028();
	return 0;
}
