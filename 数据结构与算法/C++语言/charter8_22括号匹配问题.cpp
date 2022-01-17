/*
括号匹配就是一个左括号和一个右括号匹配
可以观察知道从左到右扫描表达式的时候，右括号总是和最近的左括号匹配
那么可以每次扫描到左括号时入栈，扫描到右括号时就和栈顶的括号匹配
如果栈顶有元素说明匹配成功，否则说明剩余的右括号没有左括号可以与之匹配
或者右括号都匹配完了，左括号还有剩余，也是没匹配完全
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
	cout << "exp((((a+b)/c)-d)-1)/(f+g) ：" << endl;
	parenthesis_matching("exp((((a+b)/c)-d)-1)/(f+g)");
	cout << "(exp((((a+b)/(c)-d)-1)/(f+g)) ：" << endl;
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
			stack.push(i); //push的是索引位置
			cout << "now stack is " << stack << endl;
		}
			
		else
			if (str.at(i) == ')')
				try
				{
						cout << "left parenthesis ("<<stack.top() << 
							") and right parenthesis ("<<i <<") is match" << endl;
						stack.pop(); // 匹配到1个就删除,否则栈空抛出
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