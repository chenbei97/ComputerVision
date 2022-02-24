#pragma once
#ifndef chapter18_indexOfMax_
#define chapter18_indexOfMax_
#include "chapter1_illegalParameterValue.h"
using namespace std;
template<class T>
int indexOfMax(T a[], int n)
{
    if (n <= 0)
        throw illegalParameterValue("n must be > 0");
    int indexOfMax = 0;
    for (int i = 1; i < n; i++)
        if (a[indexOfMax] < a[i])
            indexOfMax = i;
    return indexOfMax;
}
#endif // !chapter18_indexOfMax_
