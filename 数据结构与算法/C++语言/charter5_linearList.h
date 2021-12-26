#pragma once
/*
抽象数据类型 linearList
{
    实例
        有限个元素的集合
    操作
        实例构造(): 创建线性表
        empty(): 表空返回true,否则false
        size(): 返回表的长度
        get(index): 获取索引index的元素
        indexOf(x): 返回第一次出现x的索引,若没找到返回-1
        erase(index):删除索引index的元素,索引大于index的元素按索引减1
        insert(index,x):把x插入到索引index.索引大于index的元素索引都加1
        output(): 从左到右输出元素
        实例析构~(): 销毁线性表

    在C++中有两种类，一种是抽象类一种是具体类，只有具体类才可以实例化。
​	抽象类的函数都是纯虚函数，即没有代码实现的纯虚函数，只有函数的定义。
    注意：抽象类的虚函数必须全部实现，才能变成具体类，否则依然是抽象类
    且虚函数的初始化必须是0，使用const 0进行初始化。
}
*/
#include <ostream>
template<class T>
class _charter5_linearList
{
public:
    virtual ~_charter5_linearList() {}; // 析构函数
    virtual bool empty() const = 0;  // const=0的含义是纯虚函数初始化必须赋值，而且必须初始化为0
    virtual int size() const = 0;
    virtual T& get(int theIndex) const = 0;
    virtual int indexOf(const T& theElement) const = 0;
    virtual void erase(int theIndex) = 0;
    virtual void insert(int theIndex, const T& theElement)  = 0;
    virtual void output(std::ostream& out) const = 0; //把线性表插入输出流
};
