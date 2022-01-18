#include "charter8_arrayStack.h"
#include <iostream>
using namespace std;
void switchBoxWiring(int [] , int);
void _charter8_switchBoxWiring()
{
	const int n = 8;
	int net1[n + 1] = { 0,1,2,2,1,3,3,4,4 };
	int net2[n + 1] = { 0,1,4,2,3,5,6,7,8 };
	int net3[n + 1] = { 0,1,1,2,1,3,3,4,4 };
	switchBoxWiring(net1, n);
	switchBoxWiring(net2, n);
	switchBoxWiring(net3, n);
}
void switchBoxWiring(int net[], int n)
{
	arrayStack<int>* stack = new arrayStack<int>[n];
	for (int i = 1; i <= n; i++)
		if (!stack->empty())
		{
			int Pin = net[i];
			int topPin = net[stack->top()];
			if (Pin == topPin) // net[i]�ǿɲ��ߵ�,���Դ�ջ��ɾ��
				stack->pop();
			else stack->push(i);
			cout << "if��pin = " << Pin <<" topPin = "<<topPin<< " and stack is " << *stack << endl;
		}
		else
		{
			stack->push(i);
			cout << "el��pin = " << net[i] << " topPin = " << net[stack->top()] << " and stack is " << *stack << endl;
		}
	if (stack->empty()) // �ɲ��ߵ����������йܽż����ջ��
		cout << "switch box wirnet is routable" << endl;
	else
		cout << "switch box wirnet is not routable" << endl;
}