#pragma once
#ifndef charter9_queueEmpty_
#define charter9_queueEmpty_
#include <string>
#include <iostream>
class queueEmpty
{
public:
    queueEmpty(std::string theMessage =
        "Invalid operation on empty queue")
    {
        message = theMessage;
    }
    void outputMessage() { std::cout << message << std::endl; }
private:
    std::string message;
};
#endif // !charter9_queueEmpty_
