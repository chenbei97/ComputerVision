#pragma once
#include <string>
#include <iostream>
using namespace std;
class illegalIndex
{
public:
    // ʹ��string ����ֱ�Ӽ��� const char *
    illegalIndex(string theMessage = "Illegal index")
    {
        message = theMessage;
    }
    void outputMessage() { cout << message << endl; }
private:
    string message;
};