#pragma once
#ifndef charter7_matrixIndexOutOfBounds_
#define charter7_matrixIndexOutOfBounds_
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
#endif // charter7_matrixIndexOutOfBounds_