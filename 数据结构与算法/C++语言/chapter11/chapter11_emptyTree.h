#pragma once
#ifndef chapter11_emptyTree_
#define chapter11_emptyTree_
#include <string>
#include <iostream>
using namespace std;
class emptyTree
{
public:
    emptyTree(string theMessage =
        "Invalid operation on empty tree")
    {
        message = theMessage;
    }
    void outputMessage() { cout << message << endl; }
private:
    string message;
};
#endif // !chapter11_emptyTree_
