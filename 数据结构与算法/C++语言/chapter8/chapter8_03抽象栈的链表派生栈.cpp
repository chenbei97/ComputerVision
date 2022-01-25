#include "chapter8_linkedStack.h"
#include <iostream>
using namespace std;
void _chapter8_linkedStack()
{
    
    linkedStack<int> s;
    if (s.empty())
        cout << "The stack is empty" << endl;
    /*s.isLog(true);*/
    for (int i = 1; i <= 50; i++)
        s.push(i);
    cout << "The stack size is " << s.size() << endl;
    s.isLog(false);
    cout << "The stack is " << endl << s << endl;
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