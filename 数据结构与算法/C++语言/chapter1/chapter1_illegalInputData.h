#pragma once
#ifndef chapter1_illegalInputData_
#define chapter1_illegalInputData_
#include <string>
#include <iostream>
using namespace std;
class illegalInputData
{
public:
    illegalInputData(string theMessage = "Illegal data input")
    {
        message = theMessage;
    }
    void outputMessage() { cout << message << endl; }
private:
    string message;
};
#endif chapter1_illegalInputData_
