#pragma once
#ifndef linkedMatrix_
#define linkedMatrix_
#include <iostream>
#include "charter7_linkedMatrixElements.h"
#include "myExceptions.h"
// 相比原书代码去除了>>的重载,直接定义了一个参数构造函数
template<typename T>
class linkedMatrix
{
    friend ostream& operator<<<> (ostream&, linkedMatrix<T>&);
public:
    linkedMatrix() { rows = 0; cols = 0; };
    linkedMatrix(const int&, const int&,linkedMatrixChain<rowLinkedList<T>>&) ;
    ~linkedMatrix() {};
    T operator() (const int & , const int &)  ;
    void transpose(linkedMatrix<T>& b);
    void output();
private:
    int rows,      
        cols;      
    linkedMatrixChain<rowLinkedList<T> > headerChain;
    // headerChain[i]为行链表结构体,headerChain[i].rowChain[j]为行链表元素结构体
};

template<typename T>
linkedMatrix<T> ::linkedMatrix(const int& rows, const int& cols,
    linkedMatrixChain<rowLinkedList<T>>& headerChain)
{
    for (typename  linkedMatrixChain<rowLinkedList<T>>::iterator itRow = headerChain.begin();
        itRow != headerChain.end(); itRow++)
    {
        if ((*itRow).row <= 0 || (*itRow).row > rows)
            throw matrixIndexOutOfBounds("some matrix elements'row are out of bound");
        for (typename linkedMatrixChain<rowLinkedListElement<T>>::iterator itCol = (*itRow).rowChain.begin();
            itCol != (*itRow).rowChain.end(); itCol++)
        {
            if ((*itCol).col <= 0 || (*itCol).col > cols)
                throw matrixIndexOutOfBounds("some matrix elements'col are out of bound");
        }
    }
    this->rows = rows;
    this->cols = cols;
    this->headerChain = headerChain;
}

template<class T>
T linkedMatrix<T> :: operator () (const int& row, const int& col) 
{
    if (row < 1 || col < 1 || row > rows || col > cols) 
        throw matrixIndexOutOfBounds();
    typename linkedMatrixChain<rowLinkedList<T> >::  iterator  it = headerChain.begin();
    typename linkedMatrixChain<rowLinkedList<T> >:: iterator  itEnd = headerChain.end();
    while (it != itEnd)
    {
        int r = it->getRow();
        if (row != r) //没有这个行坐标的元素
            it++;
        else
        {
            typename linkedMatrixChain<rowLinkedListElement<T> >::iterator rt = it->rowChain.begin();
            typename linkedMatrixChain<rowLinkedListElement<T> >::iterator rtEnd = it->rowChain.end();
            while (rt != rtEnd)
            {
                int c = rt->getCol();
                if (col != c)
                    rt++;
                else
                {
                    return rt->getValue();
                }
            }
            if (rt == rtEnd) // 有这行没这列
                return 0;
        }
    }
    if (it == itEnd)// 没有找到这行返回0
        return 0;
}

template<class T>
void linkedMatrix<T> ::output()
{
    cout << "rows = " << rows << " columns = " << cols << endl;
    if (headerChain.empty())
    {
        cout << "No non-zero terms" << endl;
    }
    cout << headerChain << endl;
}

template<class T>
ostream& operator<<<>(ostream& out, linkedMatrix<T>& x)
{
    for (int i = 1; i <= x.rows; i++)
    {
        for (int j = 1; j <= x.cols; j++)
            out << x(i, j) << "  ";
        out << endl;
    }
    return out;
}

template<class T>
void linkedMatrix<T>::transpose(linkedMatrix<T>& b)
{
    // 转置的矩阵放在b里边
    b.headerChain.clear(); 
    b.rows = cols;
    b.cols = rows;
    linkedMatrixChain<rowLinkedListElement<T> >* bin; // 1个指向行链表类型的指针,元素是结构体
    bin = new linkedMatrixChain<rowLinkedListElement<T> >[cols + 1]; // 行列表有cols个元素
    typename linkedMatrixChain<rowLinkedList<T> >::iterator // 定义行链表的链表的迭代器
        ih = headerChain.begin(),
        ihEnd = headerChain.end(); // 由于遍历自身矩阵的每个行链表

    while (ih != ihEnd) // 遍历行
    {
        int r = ih->getRow(); //每个行链表都有属性row
        typename linkedMatrixChain<rowLinkedListElement<T> >::iterator // 定义当前行链表的迭代器
            ir = ih->rowChain.begin(), 
            irEnd = ih->rowChain.end();
        rowLinkedListElement<T> x; // 用于存放当前行链表遍历的元素
        x.col = r; // 转置的第1步是先交换行列的坐标
        while (ir != irEnd) // 遍历当前行链表的每列
        {
            x.value = ir->getValue(); // ir是当前列的元素值
            bin[ir->col].push_back(x); // 循环结束在bin[col]会存储*this每列的所有元素.且元素已经交换过行列
            // bin[ir->col]最开始的那个就是行链表的头节点,这是需要被存储的地址,后面元素已经自动链接
            ir++;  
        }
        ih++; 
    }

    rowLinkedList<T> h;
    for (int c = 1; c <= cols; c++)
        if (!bin[c].empty()) // 有的列可能都是0元素先判断
        {
            // h赋予不同的值然后b.headerChain 添加即可
            h.row = c;
            h.rowChain = bin[c]; // 从箱子拿出来
            b.headerChain.push_back(h);
            bin[c].zero(); // 取出了1个给h就删掉
        }
    h.rowChain.zero();   // h用完了就没用了
    delete[] bin;
    /*
    例如 *this = [ [0,0,1,2,4,0]
                            [0,5,9,6,10,0]
                            [0,13,17,9,3,0]]
    rows = 3, cols = 6 , bin[6+1] (只用到1,2,3,4,5,6)
    那么bin的结果就是
    bin[1]和bin[6]没有元素,bin[0]是用不到的,这也是为何bin申请的是cols+1的内存
    bin[2]：                           (col=2,value=5),(col=3,value=13)
    bin[3]：(col=1,value=1),(col=2,value=9),(col=3,value=17)
    bin[4]：(col=1,value=2),(col=2,value=6),(col=3,value=9)
    bin[5]：(col=1,value=4),(col=2,value=10),(col=3,value=13)
    转置主要是做4件事：
        ① 把存储的每个元素的属性值要修改,也就是x.col = r
        ② b的私有属性cols和rows交换 ,b.rows = cols && b.cols = rows
        ③ 拿到转置后的头节点,恰好是*this的第1行的所有非0元素的地址(原本是每行的首个非0元素地址),也就是bin[col]
        ④ 存储行链表的头链表的属性值也要修改,即 h.row = c && h.rowChain = bin[c]
    c = 1,2,3,4,5,6 (only 2,3,4,5 not empty)
    h.row = 2,3,4,5, h.rowChain = bin[2],bin[3],bin[4],bin[5],相当于把第1行的所有非0元素地址给了b的头节点链表
*/
}

#endif linkedMatrix_