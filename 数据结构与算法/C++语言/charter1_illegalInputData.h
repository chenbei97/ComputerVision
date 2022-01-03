#pragma once
#include <string>
#include <iostream>
using namespace std;
class illegalInputData
{
public:
    illegalInputData(string theMessage = "Illegal data input")
    {
        message = theMessage;
        outputMessage();
    }
    void outputMessage() { cout << message << endl; }
private:
    string message;
};
