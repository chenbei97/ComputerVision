#include <iostream>
using namespace std;
template<class T>
void upperTriangularMatrixCol(T* data, const int& n);
void _charter7_upperTriangularMatrixCol()
{
    const int n = 5;
    int a[n * (n + 1) / 2] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
    upperTriangularMatrixCol(a, n);
    system("pause");
}
template<class T>
void upperTriangularMatrixCol(T* data, const int& n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (j < i)
                cout << 0 << "  ";
            else
            {
                cout << data[j*(j - 1) / 2 + i - 1] << "  ";
            }
        }
        cout << endl;
    }
}