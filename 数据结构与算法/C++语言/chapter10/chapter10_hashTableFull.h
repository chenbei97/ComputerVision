#pragma once
#ifndef chapter10_hashTableFull_
#define chapter10_hashTableFull_
#include <string>
#include <iostream>
class hashTableFull
{
public:
    hashTableFull(std::string theMessage =
        "The hash table is full")
    {
        message = theMessage;
    }
    void outputMessage() { std::cout << message << std::endl; }
private:
    std::string message;
};
#endif // !chapter10_hashTableFull_
