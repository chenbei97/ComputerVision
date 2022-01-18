#pragma once
#ifndef charter7_tridiagonalMatrixColMapping_
#define charter7_tridiagonalMatrixColMapping_
#include "myExceptions.h"
using namespace std;
template<class T>
class tridiagonalMatrixCol
{
public:
    tridiagonalMatrixCol(int theN = 10);
    tridiagonalMatrixCol(T*, const int&);
    ~tridiagonalMatrixCol() { if (element != NULL) element = NULL; delete[] element; }
    T get(int, int) const; 
    void set(int, int, const T&);
    friend ostream& operator<<<>(ostream&, const tridiagonalMatrixCol<T>&);
private:
    int n;       
    T* element; 
};
template<class T>
tridiagonalMatrixCol<T>::tridiagonalMatrixCol(int theN)
{
    if (theN < 1)
        throw illegalParameterValue("Matrix size must be > 0");
    n = theN;
    element = new T[3 * n - 2];
}
template<class T>
tridiagonalMatrixCol<T>::tridiagonalMatrixCol(T* data, const int& theN)
{
    if (theN < 1)
        throw illegalParameterValue("Matrix size must be > 0");
    n = theN;
    element = new T[3 * n - 2];
    copy(data, data + 3 * n - 1, element);// 是末位元素的后1个位置
}
template <class T>
T tridiagonalMatrixCol<T>::get(int i, int j) const
{
    if (i < 1 || j < 1 || i > n || j > n) 
        throw matrixIndexOutOfBounds();
    switch (i - j)
    {
    case 0:
        return element[3 * i - 3];
    case 1:
        return element[3 * i - 5];
    case -1:
        return element[3 * i - 1];
    default:
        return 0;
    }
}
template<class T>
void tridiagonalMatrixCol<T>::set(int i, int j, const T& newValue)
{
    if (i < 1 || j < 1 || i > n || j > n) 
        throw matrixIndexOutOfBounds();
    switch (i - j)
    {
    case 0:
        element[3 * i - 3] = newValue; break;
    case 1:
        element[3 * i - 5] = newValue; break;
    case -1:
        element[3 * i - 1] = newValue; break;
    default:
        if (newValue != 0)
            throw illegalParameterValue
            ("nontridiagonal elements must be zero");
    }
}
template<class T>
ostream& operator<<<>(ostream& out, const tridiagonalMatrixCol<T>& m)
{
    /*
    ​	那么列主映射公式为
​		① A(xi,xi)=>element[3i-3]，对角没有变化
​		② xi-y = 1 , A(xi,y)=>element[3i-5]，原本是左边元素element[3i-4]，现在变成上方元素，故再减1
​		③ xi-y = -1，A(xi,y)=>element[3i-1]，原本是右边元素element[3i-2]，现在变成下方元素，故再加1
    */
    for (int i = 1; i <= m.n; i++)
    {
        for (int j = 1; j <= m.n; j++)
        {
            switch (i - j)
            {
            case 0:
                cout << m.element[3 * i - 3] << "  "; break;
            case 1:
                cout << m.element[3 * i - 5] << "  "; break;
            case -1:
                cout << m.element[3 * i - 1] << "  "; break;
            default:
                cout << 0 << "  "; break;
            }
        }
        out << endl;
    }
    return out;
}
#endif charter7_tridiagonalMatrixColMapping