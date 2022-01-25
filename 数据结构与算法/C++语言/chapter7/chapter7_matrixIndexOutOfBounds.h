#pragma once
#ifndef chapter7_matrixIndexOutOfBounds_
#define chapter7_matrixIndexOutOfBounds_
#include <string>
#include <iostream>
class matrixIndexOutOfBounds
{
public:
    matrixIndexOutOfBounds
    (std::string theMessage = "Matrix index out of bounds")
    {
        message = theMessage;
    }
    void outputMessage() { std::cout << message << std::endl; }
private:
    std::string message;
};
#endif // chapter7_matrixIndexOutOfBounds_