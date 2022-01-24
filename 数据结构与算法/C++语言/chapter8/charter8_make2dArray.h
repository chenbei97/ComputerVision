#pragma once
#ifndef charter8_make2dArray_
#define charter8_make2dArray_
#include <exception>
template <class T>
bool make2dArray(T**& x, int numberOfRows, int numberOfColumns)
{
    try {
        x = new T * [numberOfRows]; // x��ָ��ָ�������ָ������,������ָ�������ڴ�
        for (int i = 0; i < numberOfRows; i++) // ÿ����ָ��x[i]��ָ��һ���ڴ�
            x[i] = new int[numberOfColumns];
        return true;
    }
    catch (std::bad_alloc) { return false; }// �����ڴ�ʧ��ʱ����false
}
#endif charter8_make2dArray_
