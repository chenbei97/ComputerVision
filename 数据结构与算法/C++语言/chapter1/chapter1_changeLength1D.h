#pragma once
#ifndef chapter1_changeLength1D_
#define chapter1_changeLength1D_
#include "chapter1_illegalParameterValue.h"
using namespace std;
template<class T>
void changeLength1D(T*& a, int oldLength, int newLength)
{
    if (newLength < 0)
        throw illegalParameterValue("new length must be >= 0");

    T* temp = new T[newLength];             
    copy(a, a + oldLength, temp);
    delete[] a;                             
    a = temp;
}
#endif // !chapter1_changeLength1D_
