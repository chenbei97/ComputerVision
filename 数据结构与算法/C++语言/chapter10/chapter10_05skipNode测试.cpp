#include <iostream>
#include "chapter10_skipNode.h"
void _chapter10_skipNode_testCode()
{
	int size = 1;
	auto dict1 = pair<int, int>{ 1,1 };
	skipNode<int,int> node1(dict1,size);
	cout << node1.data.first << " " << node1.data.second << endl;
	skipNode<int, int> node2(pair<int, int>{2, 2}, 2);
	skipNode<int, int> node31(pair<int, int>{3, 3}, 3);
	skipNode<int, int> node32(pair<int, int>{3, -3}, 3);
	skipNode<int, int> node41(pair<int, int>{4, 1}, 1);
	skipNode<int, int> node42(pair<int, int>{4, 2}, 1);
	skipNode<int, int> node43(pair<int, int>{4, 3}, 1);
	skipNode<int, int> node44(pair<int, int>{4, -1}, 1);
	skipNode<int, int> node45(pair<int, int>{4, -2}, 1);
	skipNode<int, int> node46(pair<int, int>{4, -3}, 1);

	node1.next[0] = &node2;
	node2.next[0] = &node31;
	node2.next[1] = &node32;
	node31.next[0] = &node41;
	node31.next[1] = &node42;
	node31.next[2] = &node43;
	node32.next[0] = &node44;
	node32.next[1] = &node45;
	node32.next[2] = &node46;

	node41.next[0] = NULL;
	node42.next[0] = NULL;
	node43.next[0] = NULL;
	node44.next[0] = NULL;
	node45.next[0] = NULL;
	node46.next[0] = NULL;

	skipNode<int, int>* p = &node1;
	// 应当访问的是node1->node2->node31->node41
	while (p!=NULL)
	{
		cout << "the node is (" << p->data.first << "," << p->data.second << ")\n";
		p = p->next[0];
	}

	// 测试一些skipList构造函数的一些语句
	float prob = 0.5;
	float cutoff = prob * RAND_MAX;
	cout << "cutoff is " << cutoff << endl; // cutoff is 16383.5

	int maxPairs = 1000;
	int maxtLevel = (int) ceil(
		logf((float)maxPairs) /  
		logf(1 / prob)
		) - 1; // (int)ceil[logf(maxPairs) / logf(1/prob)] - 1
	cout << "maxtLevel = " << maxtLevel << endl; // maxtLevel = 9
	maxtLevel = ceil(log2((float)maxPairs)) - 1;
	cout << "maxtLevel = "<<maxtLevel << endl; // maxtLevel = 9
}