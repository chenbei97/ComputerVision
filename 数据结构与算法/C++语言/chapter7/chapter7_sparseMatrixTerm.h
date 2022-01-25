#pragma once
#ifndef chapter7_sparseMatrixTerm_
#define chapter7_sparseMatrixTerm_
using namespace std;
template <class T>
struct matrixTerm
{
    // 定义一个稀疏矩阵类需要的结构体，这个结构体用于初始化线性表
    // 线性表用于存储这样的结构体元素，每个元素的行列和值
    int row,
        col;
    T value; 
    operator T() const { return value; }; // 利用()强制转换类型,可以得到value
};
#endif chapter7_sparseMatrixTerm
