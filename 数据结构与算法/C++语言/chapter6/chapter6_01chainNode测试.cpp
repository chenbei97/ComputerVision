#include "chapter6_chainNode.h"
#include <vector>
#include <iostream>
using namespace std;
void _chapter6_chainNode_testCode()
{
	// (Ĭ�Ϲ�����û�в���)
	_chapter6_chainNode<int> node1 ,node2 ,node3 , node4;
	vector<_chapter6_chainNode<int>> chain = {&node1,&node2,&node3,&node4};
	cout << "ÿ���ڵ��next��ַ��element��С��ʼ��Ϊ��" << endl;
	for (int i = 0; i < chain.size(); i++)
	{
		chain[i].element = i + 1;
		chain[i].next = &chain[i]; // ��ÿ���ڵ�nextָ����ָ�������ʼ��
		cout << "node[" << i+1 << "].element  =  " << chain[i].element << endl;
		cout << "node["<<i+1<<"].next  =>  " << chain[i].next << endl;
	}
	cout << "���ĺ�ÿ���ڵ��next��ַ��element��С��Ϊ��" << endl;
	for (size_t i = 0; i < chain.size(); i++)
	{
		if (i < chain.size() - 1)
			chain[i].next = chain[(unsigned __int64)i + 1].next; // ��ָ�����
		else
			chain[i].next = NULL;
		cout << "node[" << i+1 << "].element  =  " << chain[i].element << endl;
		cout << "node[" << i+1 << "].next  =>  " << chain[i].next << endl;
	}
	// ����node1-node4����û�иı�
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
	
	// �����Ͻ�������������nextָ�������
	// nextָ����һ���ڵ�ʱ�ٴε���next�ͻᵽ���¸��ڵ�ĵ�ַ
	
	// ��������3�ֹ��췽��(Ĭ�Ϲ�����û�в���)
	_chapter6_chainNode<int> node5(node1.element) ;
	cout << "ʹ��node5(node1.element)���й���,��ʱnode5.element = "
		<< node5.element << "  with node5.next  => " << node5.next << endl;
	_chapter6_chainNode<int> node6(6);
	cout << "ʹ��node6(6)���й���,��ʱnode6.element = "
		<< node6.element << "  with node6.next  => " << node6.next << endl;
	_chapter6_chainNode<int> node7(7,&node6);
	cout << "ʹ��node7(7,&node6)���й���,��ʱnode7.element = "
		<< node7.element << "  with node7.next  => " << node7.next 
		<<"  &node6 => "<<&node6<< endl;
	_chapter6_chainNode<int> node8(&node7);
	cout << "ʹ��node8(&node7)���й���,��ʱnode8.element = "
		<< node8.element << "  with node8.next  => " << node8.next
		<< "  &node7 => " << &node7 << endl;

	// ����new����
	// ���Կ���new����ʹ�ýڵ����͵�ָ�����
	_chapter6_chainNode<int> *pnode9 = new _chapter6_chainNode<int>(9, &node8);
	cout << "ʹ��new _charter6_chainNode<int>(9, &node8)���й���,\n��ʱpnode9->element = "
		<< pnode9->element << "  with pnode9->next  => " << pnode9->next
		<< "  &node8 => " << &node8 << endl;
	// ��ʵ������ͺ�����ڵ�ʵ����nextָ����һ������
	node5.next = pnode9;
	cout << "����node5.next��next��element�����ڷ���pnode9��next��element" << endl;
	cout << "node5.next->element = " << node5.next->element << "   node5.next->next = " << node5.next->next << endl;
	cout << "node5.next�ĵ�ַ����pnode9�ĵ�ַ,��node5�����element����ı�,�����ϱ߳����Ѿ���ʼ��Ϊ1" << endl;
	cout << "node5.element = "<< node5.element<<"   node5.next = "<<node5.next << "   pnode9 = " << pnode9 << endl;
}