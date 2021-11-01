#include "contanter.h"
/*
<1>列表list概念
		将数据链式存储，链表是物理存储单元上非连续的存储结构
		数据元素的逻辑顺序由链表的指针链接实现
		链表的组成：一系列结点组成
		结点的组成：一个是存储数据元素的数据域，一个是存储下一个结点地址的指针域
		可以对任意位置进行快速插入或删除元素
		对数组而言插入数据得把所有数据依次后移
		链表只需要插入结点，上一个节点指针域指向该节点，该节点指针域再指向下一个节点即可
		缺点是遍历速度慢，因为链表地址不连续，同时占用空间很大
						 0x01      0x02       0x03      0x04 ...     0x0n
		数据域：[10] ---> [20] ---> [30] ---> [40] ---> [...]
		地址域：[0x02] ---> [0x03] ---> [0x04] ---> [...] 
		STL的链表是一个双向循环链表：
				即在上述基础上，地址域不仅记录了后一个结点地址也记录了前一个结点地址
				非循环表示头部记录的上一个地址为空，尾部记录的下一个地址也为空
				对于循环，则是让尾部的下一个地址记录的是首部的地址，首部的上一个地址则记录了尾部的地址
		链表属于双向迭代器，只支持前移和后移，不是连续的内存空间
<3>list构造函数
		3.1 list<T> lst;
		3.2 list(beg ,end) ;
		3.3 list(n,elem) ;
		3.4 list(const list &lst) ;
<4>list赋值交换
		4.1 list & operator=(const list &lst) ; // v2 =v1 ;
	    4.2 assign(beg,end) ; // [beg ,end) 拷贝数据
		4.3 assign(n,elem) ; // n个elem拷贝赋值
		4.4 swap(lst) ; // 交换
<5>list大小操作
		5.1 empty() ; // 判断容量是否为空
		5.2 size(); // 长度
		5.3 resize(int num) ; // 容器变长则以默认值0填充新位置 变短则删除
		5.4 resize(int num ,elem) ;  // 容器变长elem填充新位置,变短删除
<6>list插入和删除
		6.1 push_back(elem) ; // 尾部插入元素elem
		6.2 pop_back() ; // 删除最后一个元素
		6.3 push_front(elem); // 头部插入元素elem
		6.4 pop_front() ;// 删除第一个元素
		6.5 insert(pos ,elem) ; // 返回新数据位置,迭代器指向位置pos插入元素ele
		6.6 insert( pos , int count , ele) ; // 插入count个
		6.7 insert(pos ,beg ,end) ; // 无返回值
		6.8 erase(beg ,end) ;  // 删除从[beg,end)之间元素
		6.9 erase(pos) ;  // 删除指向的位置元素
		6.10 clear(); // 清空
		6.11 remove(elem) ; // 移除所有和elem匹配的元素
<7>list数据存储 (不支持随机访问，不支持[]和at访问,若需要访问中间元素只支持++和--,不支持+1)
		7.1 front() ; // 第一个数据元素
		7.2 back() ; // 最后一个数据元素
<8>list反转和排序
		8.1 reverse() ;//反转链表
		8.2 sort() ; //链表排序
		注： 所有不支持随机访问迭代器的不支持标准算法 但可以使用成员函数L.sort()
<9>list排序案例：对自定义的数据类型进行排序
		首先按照年龄排序，然后年龄相同时按照身高排序
*/
// <9>list排序案例

class Person
{
public:
	int _age;
	int _height;
	string _name;
	Person(string name, int age, int height)
	{
		this->_age = age;
		this->_height = height;
		this->_name = name;
	}
};
void printPerson(const list<Person>& lst)
{
	for (list<Person> ::const_iterator it = lst.begin(); it != lst.end(); it++)
	{
		cout << "姓名：" << (*it)._name << "年龄：" << (*it)._age << "身高：" << (*it)._height << endl;
	}
}
// 指定排序规则
bool comparePerson(Person &p1 , Person  &p2)
{
	// 年龄相同时继续按照身高降序
	if (p1._age == p2._age)
	{
		return p1._height > p2._height;
	}
	else
	{// 按照年龄升序
		return p1._age < p2._age;
	}
	
}
void test_0031()
{
	list<Person> lst;
	Person p1("A",18,181);
	Person p2("B", 21, 181);
	Person p3("C", 30, 181);
	Person p4("D", 18, 178);
	Person p5("E", 19, 181);
	Person p6("F", 18, 188);
	lst.push_back(p1);
	lst.push_back(p2);
	lst.push_back(p3);
	lst.push_back(p4);
	lst.push_back(p5);
	lst.push_back(p6);
	printPerson(lst);
	cout << "排序后：" << endl;
	// lst.sort(); // 自定义数据排序必须指定规则
	lst.sort(comparePerson);
	printPerson(lst);

}
bool myCompare(int v1 ,int v2)
{
	return v1 > v2; // bool类型降序返回真
}
void printlist(const list<int>  & lst)
{
	for (list<int> ::const_iterator it = lst.begin(); it != lst.end(); it++)
	{
		cout << *it << endl;
	}
}
void test_0030()
{
	//3.1 list<T> lst;
	list<int> L1;
	L1.push_back(10);
	L1.push_back(20);
	L1.push_back(30);
	//printlist(L1);
	//3.2 list(beg, end);
	list<int> L2(L1.begin(), L1.end());
	//printlist(L2);
	//3.3 list(n, elem);
	list<int> L4(10, 1000);
	//printlist(L4);
	//3.4 list(const list & lst);
	list<int> L3(L2);
	//printlist(L3);
	//6.5 insert(pos ,elem) ; // 返回新数据位置,迭代器指向位置pos插入元素ele
	list<int> ::iterator it = L1.begin();
	L1.insert(++it, 1100);
	//printlist(L1);
	// 6.9 erase(pos);  // 删除指向的位置元素
	it = L1.begin();
	L1.erase(++it); // 重新删除1100
	//printlist(L1);
	// 6.11 remove(elem); // 移除所有和elem匹配的元素
	L1.push_back(1000);
	L1.remove(1000);
	//printlist(L1);
	//8.1 reverse() ;//反转链表
	L1.reverse();
	//printlist(L1);
	//8.2 sort() ; //链表排序
	//所有不支持随机访问迭代器的不支持标准算法
	//sort(L1.begin(), L1.end());
	L1.sort(); // 成员函数支持 
	printlist(L1);
	//默认升序可以改为降序
	L1.sort(myCompare);
	printlist(L1);
}
int list_containter()
//int main()
{
	//stack_queue_containter();
	test_0030();
	test_0031();
	return 0;
}