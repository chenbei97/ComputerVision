/*
����ƥ�����һ�������ź�һ��������ƥ��
���Թ۲�֪��������ɨ����ʽ��ʱ�����������Ǻ������������ƥ��
��ô����ÿ��ɨ�赽������ʱ��ջ��ɨ�赽������ʱ�ͺ�ջ��������ƥ��
���ջ����Ԫ��˵��ƥ��ɹ�������˵��ʣ���������û�������ſ�����֮ƥ��
���������Ŷ�ƥ�����ˣ������Ż���ʣ�࣬Ҳ��ûƥ����ȫ
*/
#include <iostream>
#include "charter8_arrayStack.h"
using namespace std;
void parenthesis_matching(const std::string & str);
void _charter8_parenthesis_matching()
{
	/*
	e x p (  (  (  (  a + b  )  / c ) -  d ) - 1 ) /  ( f + g )
	         3 4 5 6           10    13     16   19   21      25
	(  e x p (  (  (  (  a + b  )  /  (  c  ) -  d ) -  (  1 )  /  ( f + g  )   )   )    )    )
	0         4  5 6  7          11  13    15    18   20 22   24      28 29  30 31 32

	*/
	cout << "exp((((a+b)/c)-d)-1)/(f+g) ��" << endl;
	parenthesis_matching("exp((((a+b)/c)-d)-1)/(f+g)");
	cout << "(exp((((a+b)/(c)-d)-1)/(f+g)) ��" << endl;
	parenthesis_matching("(exp((((a+b)/(c)-d)-(1)/(f+g)))))");
}
void parenthesis_matching(const std::string & str)
{
	arrayStack <int > stack;
	//cout << str.size() << endl;
	//cout << str.at(15) << endl; =>d
	int length = (int)str.size();
	for (int i = 0; i < length; i++)
	{
		if (str.at(i) == '(')
		{
			stack.push(i); //push��������λ��
			cout << "now stack is " << stack << endl;
		}
			
		else
			if (str.at(i) == ')')
				try
				{
						cout << "left parenthesis ("<<stack.top() << 
							") and right parenthesis ("<<i <<") is match" << endl;
						stack.pop(); // ƥ�䵽1����ɾ��,����ջ���׳�
				}
				catch (stackEmpty)
				{
					cout << " No match right parenthesis" << " at (" << i << ")" << endl;
				}	
	}
	while (!stack.empty())
	{
		cout << " No match left parenthesis" << " at (" << stack.top() << ")" << endl;
		stack.pop();
	}

}