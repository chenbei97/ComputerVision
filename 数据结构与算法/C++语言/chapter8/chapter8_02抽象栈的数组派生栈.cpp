#include "chapter8_arrayStack.h"
#include <iostream>
using namespace std;
void _chapter8_arrayStack()
{
    arrayStack<int> s;
    if (s.empty())
        cout << "The stack is empty" << endl;
    for (int i = 1; i <= 25; i++)
        s.push(i);
    cout << "The stack size is " << s.size() << endl;
    cout << "Stack should be 1234...25, bottom to top" << endl;
    cout << s << endl;
    while (!s.empty())
    {
        cout << "before pop , stack top is " << s.top() << endl;
        s.pop();
    }
    cout << s << endl;
    try { s.pop(); }
    catch (stackEmpty message)
    {
        cout << "pop failed " << endl;
        message.outputMessage();
    }
}