#pragma once
#ifndef chapter9_queueEmpty_
#define chapter9_queueEmpty_
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
#endif // !chapter9_queueEmpty_
