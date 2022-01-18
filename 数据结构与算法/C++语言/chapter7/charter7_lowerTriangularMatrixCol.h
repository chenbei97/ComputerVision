#pragma once
#ifndef lowerTriangularMatrixCol_
#define lowerTriangularMatrixCol_
#include "myExceptions.h"
using namespace std;
template<class T>
class lowerTriangularMatrixCol
{
public:
    lowerTriangularMatrixCol(int theN = 10);
    lowerTriangularMatrixCol(T*, const int&);
    ~lowerTriangularMatrixCol() { if (element != NULL) element = NULL; delete[] element; }
    T get(int, int) const;
    void set(int, int, const T&);
    friend ostream& operator<<<>(ostream&, lowerTriangularMatrixCol<T>&);
private:
    int n;
    T* element;
};
template<class T>
lowerTriangularMatrixCol<T>::lowerTriangularMatrixCol(int theN)
{
    if (theN < 1)
        throw illegalParameterValue("Matrix size must be > 0");
    n = theN;
    element = new T[n * (n + 1) / 2];

}
template<class T>
lowerTriangularMatrixCol<T>::lowerTriangularMatrixCol(T* data, const int& theN)
{
    if (theN < 1)
        throw illegalParameterValue("Matrix size must be > 0");
    n = theN;
    element = new T[n * (n + 1) / 2];
    copy(data, data + n * (n + 1) / 2 + 1, element);
}
template<class T>
T lowerTriangularMatrixCol<T> ::get(int i, int j) const
{
    if (i < 1 || j < 1 || i > n || j > n)
        throw matrixIndexOutOfBounds();
    if (i >= j)
        return element[i - 1 + n*(n - 1) / 2 - (n - j)*(n - j + 1) / 2];
    else
        return 0;
}
template<class T>
void lowerTriangularMatrixCol<T> ::set(int i, int j, const T& newValue)
{
    if (i < 1 || j < 1 || i > n || j > n)
        throw matrixIndexOutOfBounds();
    if (i >= j)
        element[i - 1 + n*(n - 1) / 2 - (n - j)*(n - j + 1) / 2] = newValue;
    else
        if (newValue != 0)
            throw illegalParameterValue
            ("elements not in lower triangle must be zero");
}
template<class T>
ostream& operator<<<>(ostream& out, lowerTriangularMatrixCol<T>& m)
{
    // Ω·¬€ «A(i,j)=element[i-1+n(n-1)/2 - (n-j)(n-j+1)/2]
    for (int i = 1; i <= m.n; i++)
    {
        for (int j = 1; j <= m.n; j++)
        {
            if (j > i)
                out << 0 << "  ";
            else
            {
                cout << m.element[i - 1 + m.n*(m.n - 1) / 2 - (m.n - j)*(m.n - j + 1) / 2] << "  ";
            }
        }
        out << endl;
    }
    return out;
}
#endif lowerTriangularMatrixCol_