#pragma once
// 定义了一些异常类型,集成了第1章的3个异常类,非法参数、非法输入和非法索引
#ifndef myExceptions_
#define myExceptions_
#include <string>
#include <iostream>
using namespace std;

// illegal parameter value
class illegalParameterValue
{
public:
    illegalParameterValue(string theMessage = "Illegal parameter value")
    {
        message = theMessage;
    }
    void outputMessage() { cout << message << endl; }
private:
    string message;
};

// illegal input data
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

// illegal index
class illegalIndex
{
public:
    illegalIndex(string theMessage = "Illegal index")
    {
        message = theMessage;
    }
    void outputMessage() { cout << message << endl; }
private:
    string message;
};

// matrix index out of bounds
class matrixIndexOutOfBounds
{
public:
    matrixIndexOutOfBounds
    (string theMessage = "Matrix index out of bounds")
    {
        message = theMessage;
    }
    void outputMessage() { cout << message << endl; }
private:
    string message;
};

// matrix size mismatch
class matrixSizeMismatch
{
public:
    matrixSizeMismatch(string theMessage =
        "The size of the two matrics doesn't match")
    {
        message = theMessage;
    }
    void outputMessage() { cout << message << endl; }
private:
    string message;
};
// matrix没有初始化 用于 A=5这样的赋值如果A不知道size无法赋值
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
// stack is empty
class stackEmpty
{
public:
    stackEmpty(string theMessage =
        "Invalid operation on empty stack")
    {
        message = theMessage;
    }
    void outputMessage() { cout << message << endl; }
private:
    string message;
};

// queue is empty
class queueEmpty
{
public:
    queueEmpty(string theMessage =
        "Invalid operation on empty queue")
    {
        message = theMessage;
    }
    void outputMessage() { cout << message << endl; }
private:
    string message;
};

// hash table is full
class hashTableFull
{
public:
    hashTableFull(string theMessage =
        "The hash table is full")
    {
        message = theMessage;
    }
    void outputMessage() { cout << message << endl; }
private:
    string message;
};

// edge weight undefined
class undefinedEdgeWeight
{
public:
    undefinedEdgeWeight(string theMessage =
        "No edge weights defined")
    {
        message = theMessage;
    }
    void outputMessage() { cout << message << endl; }
private:
    string message;
};

// method undefined
class undefinedMethod
{
public:
    undefinedMethod(string theMessage =
        "This method is undefined")
    {
        message = theMessage;
    }
    void outputMessage() { cout << message << endl; }
private:
    string message;
};
#endif myExceptions_
