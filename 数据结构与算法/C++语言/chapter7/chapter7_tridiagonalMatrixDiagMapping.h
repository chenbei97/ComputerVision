#pragma once
#ifndef chapter7_tridiagonalMatrixDiagMapping_
#define chapter7_tridiagonalMatrixDiagMapping_
#include "myExceptions.h"
using namespace std;
template<class T>
class tridiagonalMatrixDiag
{
public:
    tridiagonalMatrixDiag(int theN = 10);
    tridiagonalMatrixDiag(T*, const int&);
    ~tridiagonalMatrixDiag() { if (element != NULL) element = NULL; delete[] element; }
    T get(int, int) const;
    void set(int, int, const T&);
    friend ostream& operator<<<>(ostream&, const tridiagonalMatrixDiag<T>&);
private:
    int n;       
    T* element; 
};
template<class T>
tridiagonalMatrixDiag<T>::tridiagonalMatrixDiag(int theN)
{
    if (theN < 1)
        throw illegalParameterValue("Matrix size must be > 0");
    n = theN;
    element = new T[3 * n - 2];
}

template<class T>
tridiagonalMatrixDiag<T>::tridiagonalMatrixDiag(T* data, const int& theN)
{
    if (theN < 1)
        throw illegalParameterValue("Matrix size must be > 0");
    n = theN;
    element = new T[3 * n - 2];
    copy(data, data + 3 * n - 1, element);// 是末位元素的后1个位置
}

template <class T>
T tridiagonalMatrixDiag<T>::get(int i, int j) const
{
    if (i < 1 || j < 1 || i > n || j > n)
        throw matrixIndexOutOfBounds();
    switch (i - j)
    {
    case 0:
        return element[i + n - 2];
    case 1:
        return element[i - 2];
    case -1:
        return element[i + 2*n - 2];
    default:
        return 0;
    }
}
template<class T>
void tridiagonalMatrixDiag<T>::set(int i, int j, const T& newValue)
{
    if (i < 1 || j < 1 || i > n || j > n)
        throw matrixIndexOutOfBounds();
    switch (i - j)
    {
    case 0:
        element[i + n - 2] = newValue; break;
    case 1:
        element[i - 2] = newValue; break;
    case -1:
        element[i + 2*n - 2] = newValue; break;
    default:
        if (newValue != 0)
            throw illegalParameterValue
            ("nontridiagonal elements must be zero");
    }
}
template<class T>
ostream& operator<<<>(ostream& out, const tridiagonalMatrixDiag<T>& m)
{
    /*
​		① i  - j = 0 ,A(xi,xi)=element[i+n-2];
​		② i  - j = 1 ,A(xi,yj)=element[i-2];
​		③ i  - j = -1 ,A(xi,yj)=element[i+2n-2];
        */
    for (int i = 1; i <= m.n; i++)
    {
        for (int j = 1; j <= m.n; j++)
        {
            switch (i - j)
            {
            case 0:
                cout << m.element[i + m.n - 2] << "  "; break;
            case 1:
                cout << m.element[i - 2] << "  "; break;
            case -1:
                cout << m.element[i + 2*m.n - 2] << "  ";; break;
            default:
                cout << 0 << "  "; break;
            }
        }
        out << endl;
    }
    return out;
}
#endif chapter7_tridiagonalMatrixDiagMapping