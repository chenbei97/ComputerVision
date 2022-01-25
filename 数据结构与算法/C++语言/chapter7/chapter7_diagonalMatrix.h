#pragma once
#ifndef chapter7_diagonalMatrix_
#define chapter7_diagonalMatrix_
#include "myExceptions.h"
using namespace std;
/*
对角矩阵A可以表示为一个二维数组element[row][col]
A(i,j)=element[i-1][j-1],但是二维数组需要n^2的内存空间
使用一维数组存储,由于稀疏性,0元素不存储,所以只需要n的内存空间
A(i,j)=element[i-1]即可,也就是只存n个数,但是外界还是可以用(i)(j)来访问
*/
template<class T>
class diagonalMatrix
{
public:
    diagonalMatrix(int theN = 10);
    diagonalMatrix(T*,const int &);
    ~diagonalMatrix() { delete[] element; }
    T get(int, int) const; // 不是使用重载()的方式,提供2个函数修改和访问元素
    void set(int, int, const T&);//使用T &,外边传5会报错,定义const就可以不传变量了
    friend ostream& operator<<<>(ostream&, const diagonalMatrix<T>&);
private:
    int n;       // 矩阵维度
    T* element;  // 存储
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
    if (i < 1 || j < 1 || i > n || j > n) // 获取元素
        throw matrixIndexOutOfBounds();
    if (i == j)
        return element[i - 1];   // 是对角元素
    else
        return 0;              // 非对角元素都是0
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
