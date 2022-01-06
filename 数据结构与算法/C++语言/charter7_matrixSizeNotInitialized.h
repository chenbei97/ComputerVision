#pragma once
#ifndef charter7_matrixSizeNotInitialized_
#define charter7_matrixSizeNotInitialized_
#include <string>
#include <iostream>
class matrixSizeNotInitialized
{
public:
    matrixSizeNotInitialized(std::string theMessage =
        "matrix's column and row should be initialed first !")
    {
        message = theMessage;
    }
    void outputMessage() { std::cout << message << std::endl; }
private:
    std::string message;
};
#endif // charter7_matrixSizeNotInitialized_