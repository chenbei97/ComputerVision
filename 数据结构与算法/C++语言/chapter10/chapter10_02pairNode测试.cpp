#include <iostream>
#include "chapter10_pairNode.h"
using namespace std;
void _chapter10_pairNode_testCode()
{
	pair<string, int> pair1{ "chenbei",10000 };
	pairNode<string,int> p1(pair1); // ֻ����element����
	pair<string, int> pair2{ "baby",6000 };
	pairNode<string, int> p2(pair1,&p1); // ����element��next����
	// �൱��p2��nextָ��p1
}