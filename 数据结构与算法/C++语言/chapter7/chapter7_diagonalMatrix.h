#pragma once
#ifndef chapter7_diagonalMatrix_
#define chapter7_diagonalMatrix_
#include "myExceptions.h"
using namespace std;
/*
�ԽǾ���A���Ա�ʾΪһ����ά����element[row][col]
A(i,j)=element[i-1][j-1],���Ƕ�ά������Ҫn^2���ڴ�ռ�
ʹ��һά����洢,����ϡ����,0Ԫ�ز��洢,����ֻ��Ҫn���ڴ�ռ�
A(i,j)=element[i-1]����,Ҳ����ֻ��n����,������绹�ǿ�����(i)(j)������
*/
template<class T>
class diagonalMatrix
{
public:
    diagonalMatrix(int theN = 10);
    diagonalMatrix(T*,const int &);
    ~diagonalMatrix() { delete[] element; }
    T get(int, int) const; // ����ʹ������()�ķ�ʽ,�ṩ2�������޸ĺͷ���Ԫ��
    void set(int, int, const T&);//ʹ��T &,��ߴ�5�ᱨ��,����const�Ϳ��Բ���������
    friend ostream& operator<<<>(ostream&, const diagonalMatrix<T>&);
private:
    int n;       // ����ά��
    T* element;  // �洢
};

template<class T>
diagonalMatrix<T>::diagonalMatrix(int theN)
{
    if (theN < 1)
        throw illegalParameterValue("Matrix size must be > 0");

    n = theN;
    element = new T[n];
}

template<class T>
diagonalMatrix<T>::diagonalMatrix(T*data,const int & theN)
{
    if (theN < 1)
        throw illegalParameterValue("Matrix size must be > 0");
    n = theN;
    element = new T[n];
    copy(data,data+n,element);
}

template <class T>
T diagonalMatrix<T>::get(int i, int j) const
{
    if (i < 1 || j < 1 || i > n || j > n) // ��ȡԪ��
        throw matrixIndexOutOfBounds();
    if (i == j)
        return element[i - 1];   // �ǶԽ�Ԫ��
    else
        return 0;              // �ǶԽ�Ԫ�ض���0
}

template<class T>
void diagonalMatrix<T>::set(int i, int j, const T& newValue)
{
    if (i < 1 || j < 1 || i > n || j > n)
        throw matrixIndexOutOfBounds();
    if (i == j)
        element[i - 1] = newValue;
    else
        if (newValue != 0)
            throw illegalParameterValue
            ("nondiagonal elements must be zero");
}

template<class T>
ostream& operator<<<>(ostream& out, const diagonalMatrix<T>& m)
{
    for (int i = 0; i < m.n; i++)
    {
        for (int j = 0; j < m.n; j++)
        {
            if (i != j)
                out << 0 << "  ";
            else
                out << m.element[i] << " ";
        }
        out << endl;
    }
    return out;
}
#endif  chapter7_diagonalMatrix_
