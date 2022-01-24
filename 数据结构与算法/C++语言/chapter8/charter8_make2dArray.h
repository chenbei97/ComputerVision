#pragma once
#ifndef charter8_make2dArray_
#define charter8_make2dArray_
#include <exception>
template <class T>
bool make2dArray(T**& x, int numberOfRows, int numberOfColumns)
{
    try {
        x = new T * [numberOfRows]; // x是指向指针数组的指针引用,分配行指针数组内存
        for (int i = 0; i < numberOfRows; i++) // 每个行指针x[i]再指向一块内存
            x[i] = new int[numberOfColumns];
        return true;
    }
    catch (std::bad_alloc) { return false; }// 分配内存失败时返回false
}
#endif charter8_make2dArray_
