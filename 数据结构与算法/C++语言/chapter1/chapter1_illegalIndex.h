#pragma once
#ifndef chapter1_illegalIndex_
#define chapter1_illegalIndex_
#include <string>
#include <iostream>
using namespace std;
class illegalIndex
{
public:
    // 使用string 可以直接兼容 const char *
    illegalIndex(string theMessage = "Illegal index")
    {
        message = theMessage;
    }
    void outputMessage() { cout << message << endl; }
private:
    string message;
};
#endif chapter1_illegalIndex_