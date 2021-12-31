#include "charter6_chainListWithIterator.h"
#include "charter6_studentRecord1.h"
#include <stdlib.h>
// 排序方法是独立实现的没有作为链表类的成员函数
// 注意使用的是带迭代器的单向链表，不是拓展的单向链表或者单向循环链表
// 使用的学生分数测试场景是_charter6_studentRecord1(只有!=和<<重载)
void _charter6_studentRecord_binsort(_charter6_chainListWithIterator<_charter6_studentRecord1>& theChain, int range);
void _charter6_StudentRecord1_binSort_testCode()
{
	typedef _charter6_chainListWithIterator<_charter6_studentRecord1> chain; // 名字太长取个别名
	typedef  _charter6_studentRecord1 stu; // 别名只在局部域内有效
	stu s;
	chain c;
	int aidx = 97; // 字符a的ASCII码位置
	for (int i = 1; i <= 20; i++)  // 给20个学生初始化
	{
		s.score = i / 2; 
		s.name = new string (1,aidx++); // 用于命名
		c.insert(0, s); // 把最低分头插,那么最高分排在首尾,是最坏的测试数据
	}
	cout << "The unsorted chain is" << endl;
	cout << "  "<<c << endl;
	_charter6_studentRecord_binsort(c, 10); // 10分是最高档分数
	cout << "The sorted chain is" << endl;
	cout << "  " << c << endl;
}
void _charter6_studentRecord_binsort(_charter6_chainListWithIterator<_charter6_studentRecord1>& theChain, int range)
{
	// 传入的是1个学生分数类型的链表,range是分数的档位数或者说链表大小
	typedef _charter6_chainListWithIterator<_charter6_studentRecord1> chain; // 名字太长取个别名
	typedef  _charter6_studentRecord1 stu; // 别名只在局部域内有效
	chain* bin; // 每个箱子都是1个链表,一个指向箱子数组地址的指针
	
	// 唯一可能运行失败的语句,因为内存可能分配不足
	bin = new chain[range+1]; // new 1个箱子数组,容量是range+1,与score相同,设想场景为0,1,2,3,4,5
	
	int size = theChain.size(); // 不写在for循环中,因为theChain.size()动态的变短
	// 为何执行size次,因为有size个元素,每次都取出1个
	for (int i = 1; i <=size ; i++) // 从链表的第1个学生开始,时间复杂度Θ(n)
	{
		stu x = theChain.get(0); // 拿到第0个学生的信息 Θ(1)
		theChain.erase(0); // 把传入的链表第0个学生擦去 Θ(1)
		// =>反复执行总是得到链表的第0个学生,且链表越来越短 
		bin[x.score].insert(0, x);//把拿到的学生信息根据分数插入到箱子数组的不同链表中 Θ(1)

		// 此时完成好了不同分数学生的分级
		// 接下来只需要循环取出来给到新链表即可
	}

	// 从箱子收集学生信息
	for (int j = range; j >= 0; j--) // j=5,4,3,2,1,0,依次从不同箱子取出元素,时间复杂度Θ(n+range)
	{
		while (!bin[j].empty()) // 箱子取1个就要擦掉1个,所以判断条件就是不为空就执行while
		{
			stu x = bin[j].get(0);// 拿到j箱子的首个学生 Θ(1)
			bin[j].erase(0);// j箱子擦掉 Θ(1)
			theChain.insert(0, x); // theChain是个链表引用,还是可以继续头插的,尾插还要指定索引所以头插 Θ(1)
		}// 因为j从高分遍历,但是是头插,所以高分排在后面,这样就是升序了
	}
	delete[] bin; // 箱子是数组 new 和delete必须配套
}
