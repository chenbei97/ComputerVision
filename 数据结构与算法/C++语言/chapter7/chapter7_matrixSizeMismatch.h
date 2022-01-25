#pragma once
#ifndef chapter7_matrixSizeMismatch_
#define chapter7_matrixSizeMismatch_
#include <string>
#include <iostream>
class matrixSizeMismatch
{
public:
    matrixSizeMismatch(std:: string theMessage =
        "The size of the two matrics doesn't match")
    {
        message = theMessage;
    }
    void outputMessage() { std::cout << message << std::endl; }
private:
    std::string message;
};

#endif //  chapter7_matrixSizeMismatch_
