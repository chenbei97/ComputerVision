#pragma once
#ifndef chapter7_lowerTriangularMatrixRow_
#define chapter7_lowerTriangularMatrixRow_
#include "myExceptions.h"
using namespace std;
template<class T>
class lowerTriangularMatrixRow
{
public:
    lowerTriangularMatrixRow(int theN = 10);
    lowerTriangularMatrixRow(T * , const int &);
    ~lowerTriangularMatrixRow() { if (element != NULL) element = NULL; delete[] element; }
    T get(int, int) const;
    void set(int, int, const T&);
    friend ostream& operator<<<>(ostream&, lowerTriangularMatrixRow<T>&);
private:
    int n;       
    T* element;  
};
template<class T>
lowerTriangularMatrixRow<T>::lowerTriangularMatrixRow(int theN)
{
    if (theN < 1)
        throw illegalParameterValue("Matrix size must be > 0");
    n = theN;
    element = new T[n * (n + 1) / 2];

}
template<class T>
lowerTriangularMatrixRow<T>::lowerTriangularMatrixRow(T* data, const int& theN)
{
    if (theN < 1)
        throw illegalParameterValue("Matrix size must be > 0");
    n = theN;
    element = new T[n * (n + 1) / 2];
    copy(data, data + n * (n + 1) / 2 +1 , element);
}
template<class T>
T lowerTriangularMatrixRow<T> ::get(int i, int j) const
{
    if (i < 1 || j < 1 || i > n || j > n)
        throw matrixIndexOutOfBounds();
    if (i >= j)
        return element[i * (i - 1) / 2 + j - 1];
    else
        return 0;
}
template<class T>
void lowerTriangularMatrixRow<T> :: set(int i, int j, const T& newValue)
{
    if (i < 1 || j < 1 || i > n || j > n)
        throw matrixIndexOutOfBounds();
    if (i >= j)
        element[i * (i - 1) / 2 + j - 1] = newValue;
    else
        if (newValue != 0)
            throw illegalParameterValue
            ("elements not in lower triangle must be zero");
}
template<class T>
ostream& operator<<<>(ostream& out, lowerTriangularMatrixRow<T>& m)
{
    // Ω·¬€ «A(i,j) = element[i(i-1)/2+j-1]
    for (int i = 1; i <= m.n; i++)
    {
        for (int j = 1; j <= m.n; j++)
        {
            if (j > i)
                out << 0 << "  ";
            else
            {
                cout << m.element[i * (i - 1) / 2 + j - 1] << "  ";
            }
        }
        out << endl;
    }
    return out;
}
#endif chapter7_lowerTriangularMatrixRow_