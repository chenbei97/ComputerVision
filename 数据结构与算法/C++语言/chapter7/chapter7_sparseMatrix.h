#pragma once
#ifndef chapter7_sparseMatrix_
#define chapter7_sparseMatrix_
#include <iostream>
#include "chapter7_sparseMatrixTerm.h"
#include "chapter7_sparseMatrixArrayList.h"
#include "chapter6_point2D.h"
#include "myExceptions.h"
template<class T>
class sparseMatrix
{
    friend ostream& operator<<<>
        (ostream&, sparseMatrix<T>&); // 用于输出的友元函数,可以访问私有属性
    friend istream& operator>><> // 和<<类似
        (istream&, sparseMatrix<T>&);//输入流同理
public:
    sparseMatrix() { rows = 0; cols = 0; };
    sparseMatrix(const int&, const int&, const int&, _chapter6_point2D<int> * , T*);
    int nonZeroNum() { return terms.size(); };
    int capacity() { return terms.capacity(); };
    sparseMatrix<T>&  operator =(const sparseMatrix<T>& );
    T operator () (const int & , const int &) ; // ()用于访问并返回值
    void transpose(sparseMatrix<T>&); // 稀疏矩阵的转置(不改变内存)
    void t(sparseMatrix<T>&);
    void add(sparseMatrix<T> , sparseMatrix<T>& ); // 定义了稀疏矩阵的+法
    void append(const matrixTerm<T>&); // 追加1个元素
private:
    int rows,   
        cols;   
    sparseMatrixArrayList<matrixTerm<T>> terms; // 使用线性表存储
    // 注：这里使用行主映射来存储
};
template<class T>
sparseMatrix<T> ::sparseMatrix(const int& theRow, const int& theCol, const int& size, _chapter6_point2D<int> * points , T * value)
{
    // 想用的是坐标,所以这个点类应当具体化为坐标类,也就是int类型
    rows = theRow;
    cols = theCol;
    matrixTerm<T> term; // 临时结构体
    for (int i = 0; i < size; i++)
    {
        if (points[i].x >= theRow || points[i].y >= theCol || points[i].x<=0 || points[i].y <=0)
            throw matrixIndexOutOfBounds("some matrix element indexs is out of bounds,please check coordinates!");
        term.row = points[i].x; // int类型才能被row,col接收
        term.col = points[i].y;
        term.value = value[i]; // T类型变为T类型
        terms.push_back(term); // 尾插
    }
}
template<class T>
T sparseMatrix<T> :: operator () (const int& row, const int& col)
{
    if (row <= 0 || col <= 0 || row > rows || col > cols)
        throw matrixIndexOutOfBounds();
    for (typename sparseMatrixArrayList<matrixTerm<T>>::iterator it = terms.begin();
        it != terms.end(); it++)
    {
        if ((*it).col == col && (*it).row == row)
            return (*it).value;
    }
    return 0; // 根据条件返回的话需要返回T而不是T&,否则会报错
}
template<class T>
sparseMatrix<T>& sparseMatrix<T> ::operator =(const sparseMatrix<T>& m)
{
    rows = m.rows;
    cols = m.cols;
    terms = m.terms; // 测试稀疏矩阵线性表类的重载=
    return *this; // 返回自己
}
template<class T>
ostream& operator<<<>(ostream& out, sparseMatrix<T>& x)
{
    out << "rows = " << x.rows << " columns = "
        << x.cols << endl;
    out << "nonzero terms = " << x.terms.size() << endl; // terms是个结构体线性表
    
    //// 使用迭代器遍历元素 ,必须要实例化的迭代器 这里只是为了迭代器
    for (typename sparseMatrixArrayList<matrixTerm<T>>::iterator it = x.terms.begin();
        it != x.terms.end(); it++)
    {
        out << "matrix(" << (*it).row << ',' << (*it).col // *i是个具体的稀疏矩阵结构体元素
            << ") = " << (*it).value << "  ";
        if ( ((int)it+1) % 5 == 0) // matrixTerm有强制转换类型
            out << endl;
    }
    out << endl;
    return out;
}
template<class T>
istream& operator>><>(istream& input, sparseMatrix<T>& x)
{
    int numberOfTerms; // 插入的数量
    cout << "Please enter number of rows  = " << endl;
    input >> x.rows;
    cout << "Please enter number of cols  = " << endl;
    input >> x.cols;
    cout << "Please enter number of terms  = " << endl;
    input>> numberOfTerms;
    x.terms.reSet(numberOfTerms); // 动态调整线性表的size
    matrixTerm<T> mTerm;//临时结构体
    for (int i = 0; i < numberOfTerms; i++)
    {
        cout << "term("<<i+1<<").row = " << endl;
        input >> mTerm.row;
        while (mTerm.row >= x.rows)
        {
            cout << "input row = " << mTerm.row << " is out of x.rows = " << x.rows 
                <<"\nplease re_enter" << endl;
            input >> mTerm.row;
        }
        cout << "term(" << i + 1 << ").col = " << endl;
        input >> mTerm.col;
        while (mTerm.col >= x.cols)
        {
            cout << "input col = " << mTerm.col << " is out of x.cols = " << x.cols
                << "\nplease re_enter" << endl;
            input >> mTerm.col;
        }
        cout << "term(" << i + 1 << ").value = " << endl;
        input >> mTerm.value;
        x.terms.set(i, mTerm); // 注意存储的是结构体节点
    }
    return input;
}
template<class T>
void sparseMatrix<T>::transpose(sparseMatrix<T>& b)
{
    // 转置后的矩阵在b中存放
    b.cols = rows;
    b.rows = cols;
    matrixTerm<T> term;
    for (typename sparseMatrixArrayList<matrixTerm<T>>::iterator it = terms.begin();
        it != terms.end(); it++)
    {
        term.col = (*it).row;
        term.row = (*it).col;
        term.value = (*it).value; // 此种转置方法不改变内存位置
        b.terms.push_back(term);// 但是插入比较耗时,不要使用reSet,否则就变成20个元素了
    }
}
template<class T>
void sparseMatrix<T>::t(sparseMatrix<T>& b)
{
    b.cols = rows;
    b.rows = cols;
    b.terms.reSet(terms.size());

    // 原矩阵行主映射,逐行的从左到右依次映射到element的0,1,2,..listSize-1的位置
    // 转置矩阵行主映射到element,就是按原矩阵的列映射
    // 例如(2,6),(15,3),(26,2),(35,1),(42,2),(47,3),(50,6),(51,9),(50,14),(47,19)
    // 行坐标是从小到大逐个映射的,现在转置后的矩阵也要行主映射映射,就是对现在的列坐标映射
    // (6,3,2,1,2,3,6,9,14,19)的rank名次为->(5,3,1,0,2,4,6,7,8,9)
    // 那么把原来的element[0,1,2,3,4,5,6,7,8,9]=>element[5,3,1,0,2,4,6,7,8,9]即可
    T* ys = new T[terms.size()];
    int idx = 0;
    for (typename sparseMatrixArrayList<matrixTerm<T> >::iterator it = terms.begin();
        it != terms.end(); it++)
    {
        ys[idx++] = (*it).col;
    }
    int* rank = new int[terms.size()]; // 记录名次 对列坐标排名
    for (int i = 0; i < terms.size(); i++)
        rank[i] = 0;
    for (int i =1;i<terms.size();i++)
        for (int j = 0; j < i; j++)
        {
            if (ys[j] <= ys[i]) rank[i]++;
            else rank[j]++;
        }
    delete[] ys;
    //for (int i = 0; i < terms.size(); i++)
    //    cout << "rank["<<i << "] = " << rank[i] << "  ";
    //cout << endl;
    idx = 0;
    matrixTerm<T> mTerm;
    for (typename sparseMatrixArrayList<matrixTerm<T> >::iterator i = terms.begin();
        i != terms.end(); i++)
    {
        mTerm.row = (*i).col;
        mTerm.col = (*i).row;
        mTerm.value = (*i).value;
        b.terms.set(rank[idx++], mTerm);
    }
    delete[] rank;
}
template<class T>
void sparseMatrix<T>::append(const matrixTerm<T>& theTerm)
{
    if (theTerm.col <= 0 || theTerm.row <= 0 || theTerm.col > cols || theTerm.row > rows)
        throw matrixIndexOutOfBounds("the newTerm's col or row is out of bound!");
    terms.push_back(theTerm);
}
template<class T>
void sparseMatrix<T>::add(sparseMatrix<T> b, sparseMatrix<T>& c)
{
    //  Compute c = (*this) + b.
    // 由于b的erase操作,故不能传递引用,否则会改变原有的b
    // 但是最终不耗费内存,因为b的数据量一直在减少
    if (rows != b.rows || cols != b.cols)
        throw matrixSizeMismatch();
    c.rows = rows;
    c.cols = cols;
    c.terms.clear();
    typename sparseMatrixArrayList<matrixTerm<T> >::iterator it = terms.begin();
    typename sparseMatrixArrayList<matrixTerm<T> >::iterator ib = b.terms.begin();
    typename sparseMatrixArrayList<matrixTerm<T> >::iterator itEnd = terms.end();
    typename sparseMatrixArrayList<matrixTerm<T> >::iterator ibEnd = b.terms.end();
    for (; it != itEnd; )
    {
        int bidx = 0;
        for (; ib!= ibEnd; ib++)
        {
            if ((*it).col == (*ib).col && (*it).row == (*ib).row) // 如果有相同位置
            {
                if ((*it).value + (*ib).value != 0)
                {
                    matrixTerm<T> mTerm;
                    mTerm.row = (*it).row;
                    mTerm.col = (*it).col;
                    mTerm.value = (*it).value + (*ib).value;
                    //cout << "(" << mTerm.row << "," << mTerm.col << ")" << endl;
                    //c.terms.push_back(mTerm); // push_back可能使插入的节点并不符合行主映射
                    b.terms.erase(bidx); // 当前的位置可以剔除,下一次b的循环不会再有这个位置
                }
                ib = b.terms.begin(); //将ib回到开头
                ibEnd = b.terms.end(); // erase后end位置也变了
                it++; // it增加也会避免使用t重复的位置
                break; // 跳出当前for循环直接进入下一个it,后面的ib不用再进行遍历因为不会有第2个重复的位置
            }
            bidx++;
        }
        if (ib == ibEnd) // b遍历结束都没有和当前it相同的
        {
            if (it == itEnd) // 这个判断是防止两个矩阵都是相同元素时 引起的bug
                break;
            c.terms.push_back(*it); // it不和任何ib重复
            //cout << "(" << (*it).row << "," << (*it).col << ")" << endl;
            ib = b.terms.begin();// ib回到开头
            it++;
            continue;
        }
    }
    if (!b.terms.empty()) // 如果b还有剩余说明是不和任何t重复的
    {
        //cout << "!b.terms.empty()" << endl;
        ib = b.terms.begin();
        ibEnd = b.terms.end();
        for (; ib != ibEnd; ib++)
            c.terms.push_back(*ib);
    }
    // 书上的代码存在bug,如果两个矩阵都在相同的位置有1个元素,但是内存顺序不一致时会出错
    // 例如A矩阵有(4,5),(5,8),(6,2)三个坐标,且确实按顺序摆放,B是(6,2),(4,5),(5,8),那么相加的结果有重复的
    // 因为两个矩阵都是行主映射的话相加确实应该没有问题,但是假若构造的时候没有按照行主映射就会有问题
    //int cSize = 0;//用来计算插入的位置,每当插入1个就增1
    //while (it != itEnd && ib != ibEnd) // 2个稀疏矩阵的非零元素个数和位置可能不同
    //{
    //    // 如果个数不同,需要在后边插入剩余项,可能是it也可能是ib多出来的
    //    // 继续判断位置,位置相同需要新建1个节点,值相加
    //    // 如果不是相同位置,就要增加1个节点,直接存储it或者ib的节点即可
    //    // 谁先存储取决于位置的前后,小的先插
    //    int tIndex = (*it).row * cols + (*it).col; // 某个节点的实际位置=当前行数*总列数+当前列数
    //    int bIndex = (*ib).row * cols + (*ib).col;// b和*this是同型的,总列数都是cols
    //    //cout << "tindex = " << tIndex << "  bindex = " << bIndex << endl;
    //    if (tIndex < bIndex) // 实际位置考前的先插入,cSize++先使用
    //    {
    //        cout << "it < ib：cSize = " << cSize << endl;
    //        c.terms.insert(cSize++, *it); // 那么插小的t节点
    //        it++; // 1个it节点被使用就到下一个
    //    }
    //    else 
    //    {
    //        if (tIndex == bIndex) // 实际位置相等且值相加不为0的cSize++其次使用
    //        {
    //            if ((*it).value + (*ib).value != 0) 
    //            {
    //                cout << "it = ib：cSize = " << cSize << endl;
    //                matrixTerm<T> mTerm; // 要构建新节点,因为此时插入*it和*ib都不对
    //                mTerm.row = (*it).row; // 因为位置相同,使用(*ib).row也可以
    //                mTerm.col = (*it).col;// 因为位置相同,使用(*ib).col也可以
    //                mTerm.value = (*it).value + (*ib).value; // 值直接相加即可
    //                c.terms.insert(cSize++, mTerm); //
    //            }
    //            it++;
    //            ib++;
    //        }
    //        else
    //        { // cSize++后使用
    //            cout << "it>ib：cSize = " << cSize << endl;
    //            c.terms.insert(cSize++, *ib);
    //            ib++;
    //        }
    //    }
    //}
    //for (; it != itEnd; it++)
    //    c.terms.insert(cSize++, *it);
    //for (; ib != ibEnd; ib++)
    //    c.terms.insert(cSize++, *ib);
}
#endif chapter7_sparseMatrix_
