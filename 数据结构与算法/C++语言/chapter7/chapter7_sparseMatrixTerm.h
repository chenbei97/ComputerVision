#pragma once
#ifndef chapter7_sparseMatrixTerm_
#define chapter7_sparseMatrixTerm_
using namespace std;
template <class T>
struct matrixTerm
{
    // ����һ��ϡ���������Ҫ�Ľṹ�壬����ṹ�����ڳ�ʼ�����Ա�
    // ���Ա����ڴ洢�����Ľṹ��Ԫ�أ�ÿ��Ԫ�ص����к�ֵ
    int row,
        col;
    T value; 
    operator T() const { return value; }; // ����()ǿ��ת������,���Եõ�value
};
#endif chapter7_sparseMatrixTerm
