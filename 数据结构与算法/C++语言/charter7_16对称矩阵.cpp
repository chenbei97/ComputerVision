#include <iostream>
using namespace std;
template<class T>
void symmetric_matrix(T* data, const int& n);
void _charter7_symmetric_matrix()
{
    const int n = 5;
    int a[n * (n + 1) / 2] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
    symmetric_matrix(a, n);
}
template<class T>
void symmetric_matrix(T* data, const int& n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (j < i)
                cout << data[i * (i - 1) / 2 + j - 1] << "    ";
            else
            {
                cout << data[j * (j - 1) / 2 + i - 1] << "    ";
            }
        }
        cout << endl;
    }

}