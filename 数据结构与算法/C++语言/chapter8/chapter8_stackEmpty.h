#pragma once
#ifndef chapter8_stackEmpty_
#define chapter8_stackEmpty_
#include <string>
#include <iostream>
using namespace std;
class stackEmpty
{
public:
    stackEmpty(string theMessage =
        "Invalid operation on empty stack")
    {
        message = theMessage;
    }
    void outputMessage() { cout << message << endl; }
private:
    string message;
};
#endif // !chapter8_stackEmpty_
