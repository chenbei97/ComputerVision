#pragma once
#include <string>
#include <iostream>
using namespace std;
class illegalIndex
{
public:
    // 需要使用string,使用const char*可能会导致不兼容
    illegalIndex(string theMessage = "Illegal index")
    {
        message = theMessage;
        outputMessage();
    }
    void outputMessage() { cout << message << endl; }
private:
    string message;
};
