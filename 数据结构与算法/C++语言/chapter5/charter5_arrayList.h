#pragma once
#include "charter5_linearList.h"
#include <sstream>
// 线性表的具体类声明部分直接实现,复杂的函数分文件实现
template<class T>
class _charter5_arrayList : public _charter5_linearList<T>
{
public:
    // 时间复杂度为O(1),自定义时时间复杂度为O(initialCapacity)
    _charter5_arrayList(int initialCapacity = 10); // 默认构造

    // 时间复杂度为O(n)
    _charter5_arrayList(const _charter5_arrayList<T>&); // 复制构造,把 _charter5_arrayList<T>整体看成1个数据类型

    ~_charter5_arrayList() { delete[] element; }//析构函数

    // 抽象类的虚函数实现
    // 时间复杂度为O(1)
    bool empty() const { return listSize == 0; }// 表示这个成员函数传入的this指针为const,不能更改类的其他成员,如果const在前表示返回值是const

     // 时间复杂度为O(1)
    int size() const { return listSize; }// 元素个数

    // 时间复杂度为Θ(1)
    T& get(int theIndex) const;

    // 时间复杂度为O(max{listSize,1})=>O(listSize)
    int indexOf(const T& theElement) const; // 不能改变类成员也不能改变实例的元素,前者限制类外实例后者限制类内

    // 没有此元素索引Θ(1),有的话为Θ(listSize-theIndex),每一个元素的移动需要O(1),合计O(listSize-theIndex)
    void erase(int theIndex);

    // 是否抛出异常Θ(1),如果插入前数组空间满就会数组长度加倍,为Θ(arrayLength)=Θ(listSize)
    // 移动数组元素Θ(listSize-theIndex),总的时间复杂度O(listSize)
    void insert(int theIndex, const T& theElement);

    // 时间复杂度为O(listSize)
    void output(std::ostream& out) const;

    // 其他方法
    // 时间复杂度为O(1)
    int capacity() const { return arrayLength; }

protected:
    // 确定一个元素在0~listSize-1中的索引,注意不是arrayLength
    // 时间复杂度为Θ(1)
    void checkIndex(int theIndex) const; // 不可更改类成员的成员函数

    // 时间复杂度为Θ(n)
    void changeLength1D(T*& pa, int oldLength, int newLength); // 数组容量已满时加倍

    int arrayLength; // 线性表的容量≥listSize
    int listSize; // 线性表的元素个数
    T* element;
    // 存储线性表元素的一维数组,因为是动态创建的所以析构必须带上delete[]
};
