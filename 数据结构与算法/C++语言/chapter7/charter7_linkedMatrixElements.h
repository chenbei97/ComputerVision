#pragma once
#ifndef charter7_linkedMatrixElements_
#define charter7_linkedMatrixElements_
#include "charter7_linkedMatrixChain.h"
// 链表矩阵需要使用多个行链表来存储每行的元素,所以链表矩阵的链表元素是1个行链表rowLinkedList
// _charter6_chainListWithIteratorExtend<rowLinkedList<T>> headerChain

// 行链表的数据域有row和包含整个行链表元素的链表,指针域next是行链表之间进行链接
//行链表的元素又是1个结构体类型,数据域存储了col、value

// 两个结构体比原书代码去除了output函数
template<class T>
struct rowLinkedListElement
{
    int col;
    T value;

    bool operator !=(const rowLinkedListElement<T>& y)
    {
        return (value != y.value); // 结构体比较转为value比较
    }
    int getCol() const { return col; } // 必须加const
    T getValue() const { return value; }
};
// 必须要有<<函数否则会编译报错没有与 "charter6_chainListWithIterator.h"<<对应的转换
// 因为链表的<<函数打印的是currentNode->element,而currentNode是chainNode类型
// chainNode有个T element,这里的T 其实就是rowLinkedListElement类型,那么打印element是不知道什么意思的
// 因为element是个结构体不是一个数,所以结构体定义的时候就必须给出<<该结构体的方法
template<class T> 
ostream& operator<<(ostream& out, const rowLinkedListElement<T>& x)
{
    out  <<"col("<< x.getCol() << ") = " << x.getValue() << " "; 
    return out;
}

// 头节点结构体,它的数据域有row和row存储的元素rowLinkedListElement,这样的元素用相应的链表存储
// 同理这也是个结构体,打印这样的结构体时也必须给出相应的重载方法
template<class T>
struct rowLinkedList
{
    int row;
    
    linkedMatrixChain<rowLinkedListElement<T> > rowChain;

    bool operator !=(const rowLinkedList<T>& y)
    {
        return (row != y.row); // 转为是否相同行
    }
    int getRow() const { return row; }
};
template<class T>
ostream& operator<<(ostream& out,const rowLinkedList<T>& x)
{
    // << x.rowChain 调用的就是out  <<","<< x.getCol() << " ) = " << x.getValue() << endl;
    out << "\nrow(" << x.getRow() << ")：";
    out<<x.rowChain; 
    return out;
}
#endif charter7_linkedMatrixElements_