#include "chapter8_derivedArrayStack.h"
#include "chapter8_stackEmpty.h"
using namespace std;
void _chapter8_derivedArrayStack()
{
	derivedArrayStack<int> s;
	if (s.empty())
		cout << "The stack is empty" << endl;
	for (int i = 1; i <= 25; i++)
		s.push(i);
	cout << "The stack size is " << s.size() << endl;
	cout << "Stack should be 1234, bottom to top" << endl;
	cout << s << endl;

	while (!s.empty())
	{
		cout << "Stack top is " << s.top() << endl;
		s.pop();
		cout << "Popped top element" << endl;
	}
	try { s.pop(); }
	catch (stackEmpty message)
	{
		cout << "Last pop failed " << endl;
		message.outputMessage();
	}
}