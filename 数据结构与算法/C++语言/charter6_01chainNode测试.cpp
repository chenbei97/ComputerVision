#include "charter6_chainNode.h"
#include <vector>
#include <iostream>
using namespace std;
void _charter6_chainNode_testCode()
{
	// (默认构造是没有参数)
	_charter6_chainNode<int> node1 ,node2 ,node3 , node4;
	vector<_charter6_chainNode<int>> chain = {&node1,&node2,&node3,&node4};
	cout << "每个节点的next地址和element大小初始化为：" << endl;
	for (int i = 0; i < chain.size(); i++)
	{
		chain[i].element = i + 1;
		chain[i].next = &chain[i]; // 把每个节点next指针先指向自身初始化
		cout << "node[" << i+1 << "].element  =  " << chain[i].element << endl;
		cout << "node["<<i+1<<"].next  =>  " << chain[i].next << endl;
	}
	cout << "更改后每个节点的next地址和element大小变为：" << endl;
	for (size_t i = 0; i < chain.size(); i++)
	{
		if (i < chain.size() - 1)
			chain[i].next = chain[(unsigned __int64)i + 1].next; // 把指向更改
		else
			chain[i].next = NULL;
		cout << "node[" << i+1 << "].element  =  " << chain[i].element << endl;
		cout << "node[" << i+1 << "].next  =>  " << chain[i].next << endl;
	}
	// 但是node1-node4本身没有改变
	cout << "node1.element = " << node1.element << "   node1.next => " << node1.next<< endl;
	cout << "node2.element = " << node2.element << "   node2.next => " << node2.next << endl;
	cout << "node3.element = " << node3.element << "   node3.next => " << node3.next << endl;
	cout << "node4.element = " << node4.element << "   node4.next => " << node4.next << endl;
	node1.element = 1; node2.element = 2; node3.element = 3; node4.element = 4;
	node1.next = &node2; node2.next = &node3; node3.next = &node4; node4.next = NULL;
	cout << "&node1 => " << &node1 << "   &node2 =>" << &node2 
		<< "   &node3 =>" << &node3 << "   &node4 =>" << &node4 << endl;
	cout << "node1.next = > " << node1.next << endl;//node1=>node2
	cout << "node1.next->next =>  " << node1.next->next << endl;//node2=>node3
	cout << "node1.next->next->next =>  " << node1.next->next->next << endl;//node3=>node4
	cout << "node1.next->next->next->next =>  " << node1.next->next->next->next << endl;// node4=>NULL
	
	// 从以上结果来看更能体会next指针的作用
	// next指向下一个节点时再次调用next就会到下下个节点的地址
	
	// 测试其余3种构造方法(默认构造是没有参数)
	_charter6_chainNode<int> node5(node1.element) ;
	cout << "使用node5(node1.element)进行构造,此时node5.element = "
		<< node5.element << "  with node5.next  => " << node5.next << endl;
	_charter6_chainNode<int> node6(6);
	cout << "使用node6(6)进行构造,此时node6.element = "
		<< node6.element << "  with node6.next  => " << node6.next << endl;
	_charter6_chainNode<int> node7(7,&node6);
	cout << "使用node7(7,&node6)进行构造,此时node7.element = "
		<< node7.element << "  with node7.next  => " << node7.next 
		<<"  &node6 => "<<&node6<< endl;
	_charter6_chainNode<int> node8(&node7);
	cout << "使用node8(&node7)进行构造,此时node8.element = "
		<< node8.element << "  with node8.next  => " << node8.next
		<< "  &node7 => " << &node7 << endl;
}