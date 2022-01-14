#pragma once
#ifndef stackEmpty_
#define stackEmpty_
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
#endif // !stackEmpty_
