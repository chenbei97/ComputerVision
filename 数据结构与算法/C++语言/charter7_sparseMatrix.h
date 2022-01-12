#pragma once
#ifndef charter7_sparseMatrix_
#define charter7_sparseMatrix_
#include <iostream>
#include "charter7_sparseMatrixTerm.h"
#include "charter7_sparseMatrixArrayList.h"
#include "charter6_point2D.h"
#include "myExceptions.h"
template<class T>
class sparseMatrix
{
    friend ostream& operator<<<>
        (ostream&, sparseMatrix<T>&); // �����������Ԫ����,���Է���˽������
    friend istream& operator>><> // ��<<����
        (istream&, sparseMatrix<T>&);//������ͬ��
public:
    sparseMatrix() { rows = 0; cols = 0; };
    sparseMatrix(const int&, const int&, const int&, _charter6_point2D<int> * , T*);
    int nonZeroNum() { return terms.size(); };
    int capacity() { return terms.capacity(); };
    sparseMatrix<T>&  operator =(const sparseMatrix<T>& );
    T operator () (const int & , const int &) ; // ()���ڷ��ʲ�����ֵ
    void transpose(sparseMatrix<T>&); // ϡ������ת��(���ı��ڴ�)
    void t(sparseMatrix<T>&);
    void add(sparseMatrix<T> , sparseMatrix<T>& ); // ������ϡ������+��
    void append(const matrixTerm<T>&); // ׷��1��Ԫ��
private:
    int rows,   
        cols;   
    sparseMatrixArrayList<matrixTerm<T>> terms; // ʹ�����Ա�洢
    // ע������ʹ������ӳ�����洢
};
template<class T>
sparseMatrix<T> ::sparseMatrix(const int& theRow, const int& theCol, const int& size, _charter6_point2D<int> * points , T * value)
{
    // ���õ�������,�����������Ӧ�����廯Ϊ������,Ҳ����int����
    rows = theRow;
    cols = theCol;
    matrixTerm<T> term; // ��ʱ�ṹ��
    for (int i = 0; i < size; i++)
    {
        if (points[i].x >= theRow || points[i].y >= theCol || points[i].x<=0 || points[i].y <=0)
            throw matrixIndexOutOfBounds("some matrix element indexs is out of bounds,please check coordinates!");
        term.row = points[i].x; // int���Ͳ��ܱ�row,col����
        term.col = points[i].y;
        term.value = value[i]; // T���ͱ�ΪT����
        terms.push_back(term); // β��
    }
}
template<class T>
T sparseMatrix<T> :: operator () (const int& row, const int& col)
{
    if (row <= 0 || col <= 0 || row >= rows || col >= cols)
        throw matrixIndexOutOfBounds();
    for (typename sparseMatrixArrayList<matrixTerm<T>>::iterator it = terms.begin();
        it != terms.end(); it++)
    {
        if ((*it).col == col && (*it).row == row)
            return (*it).value;
    }
    return 0; // �����������صĻ���Ҫ����T������T&,����ᱨ��
}
template<class T>
sparseMatrix<T>& sparseMatrix<T> ::operator =(const sparseMatrix<T>& m)
{
    rows = m.rows;
    cols = m.cols;
    terms = m.terms; // ����ϡ��������Ա��������=
    return *this; // �����Լ�
}
template<class T>
ostream& operator<<<>(ostream& out, sparseMatrix<T>& x)
{
    out << "rows = " << x.rows << " columns = "
        << x.cols << endl;
    out << "nonzero terms = " << x.terms.size() << endl; // terms�Ǹ��ṹ�����Ա�
    
    //// ʹ�õ���������Ԫ�� ,����Ҫʵ�����ĵ����� ����ֻ��Ϊ�˵�����
    for (typename sparseMatrixArrayList<matrixTerm<T>>::iterator it = x.terms.begin();
        it != x.terms.end(); it++)
    {
        out << "matrix(" << (*it).row << ',' << (*it).col // *i�Ǹ������ϡ�����ṹ��Ԫ��
            << ") = " << (*it).value << "  ";
        if ( ((int)it+1) % 5 == 0) // matrixTerm��ǿ��ת������
            out << endl;
    }
    out << endl;
    return out;
}
template<class T>
istream& operator>><>(istream& input, sparseMatrix<T>& x)
{
    int numberOfTerms; // ���������
    cout << "Please enter number of rows  = " << endl;
    input >> x.rows;
    cout << "Please enter number of cols  = " << endl;
    input >> x.cols;
    cout << "Please enter number of terms  = " << endl;
    input>> numberOfTerms;
    x.terms.reSet(numberOfTerms); // ��̬�������Ա��size
    matrixTerm<T> mTerm;//��ʱ�ṹ��
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
        x.terms.set(i, mTerm); // ע��洢���ǽṹ��ڵ�
    }
    return input;
}
template<class T>
void sparseMatrix<T>::transpose(sparseMatrix<T>& b)
{
    // ת�ú�ľ�����b�д��
    b.cols = rows;
    b.rows = cols;
    matrixTerm<T> term;
    for (typename sparseMatrixArrayList<matrixTerm<T>>::iterator it = terms.begin();
        it != terms.end(); it++)
    {
        term.col = (*it).row;
        term.row = (*it).col;
        term.value = (*it).value; // ����ת�÷������ı��ڴ�λ��
        b.terms.push_back(term);// ���ǲ���ȽϺ�ʱ,��Ҫʹ��reSet,����ͱ��20��Ԫ����
    }
}
template<class T>
void sparseMatrix<T>::t(sparseMatrix<T>& b)
{
    b.cols = rows;
    b.rows = cols;
    b.terms.reSet(terms.size());

    // ԭ��������ӳ��,���еĴ���������ӳ�䵽element��0,1,2,..listSize-1��λ��
    // ת�þ�������ӳ�䵽element,���ǰ�ԭ�������ӳ��
    // ����(2,6),(15,3),(26,2),(35,1),(42,2),(47,3),(50,6),(51,9),(50,14),(47,19)
    // �������Ǵ�С�������ӳ���,����ת�ú�ľ���ҲҪ����ӳ��ӳ��,���Ƕ����ڵ�������ӳ��
    // (6,3,2,1,2,3,6,9,14,19)��rank����Ϊ->(5,3,1,0,2,4,6,7,8,9)
    // ��ô��ԭ����element[0,1,2,3,4,5,6,7,8,9]=>element[5,3,1,0,2,4,6,7,8,9]����
    T* ys = new T[terms.size()];
    int idx = 0;
    for (typename sparseMatrixArrayList<matrixTerm<T> >::iterator it = terms.begin();
        it != terms.end(); it++)
    {
        ys[idx++] = (*it).col;
    }
    int* rank = new int[terms.size()]; // ��¼���� ������������
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
    if (theTerm.col <= 0 || theTerm.row <= 0 || theTerm.col >= cols || theTerm.row >= rows)
        throw matrixIndexOutOfBounds("the newTerm's col or row is out of bound!");
    terms.push_back(theTerm);
}
template<class T>
void sparseMatrix<T>::add(sparseMatrix<T> b, sparseMatrix<T>& c)
{
    //  Compute c = (*this) + b.
    // ����b��erase����,�ʲ��ܴ�������,�����ı�ԭ�е�b
    // �������ղ��ķ��ڴ�,��Ϊb��������һֱ�ڼ���
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
            if ((*it).col == (*ib).col && (*it).row == (*ib).row) // �������ͬλ��
            {
                if ((*it).value + (*ib).value != 0)
                {
                    matrixTerm<T> mTerm;
                    mTerm.row = (*it).row;
                    mTerm.col = (*it).col;
                    mTerm.value = (*it).value + (*ib).value;
                    //cout << "(" << mTerm.row << "," << mTerm.col << ")" << endl;
                    //c.terms.push_back(mTerm); // push_back����ʹ����Ľڵ㲢����������ӳ��
                    b.terms.erase(bidx); // ��ǰ��λ�ÿ����޳�,��һ��b��ѭ�������������λ��
                }
                ib = b.terms.begin(); //��ib�ص���ͷ
                ibEnd = b.terms.end(); // erase��endλ��Ҳ����
                it++; // it����Ҳ�����ʹ��t�ظ���λ��
                break; // ������ǰforѭ��ֱ�ӽ�����һ��it,�����ib�����ٽ��б�����Ϊ�����е�2���ظ���λ��
            }
            bidx++;
        }
        if (ib == ibEnd) // b����������û�к͵�ǰit��ͬ��
        {
            if (it == itEnd) // ����ж��Ƿ�ֹ������������ͬԪ��ʱ �����bug
                break;
            c.terms.push_back(*it); // it�����κ�ib�ظ�
            //cout << "(" << (*it).row << "," << (*it).col << ")" << endl;
            ib = b.terms.begin();// ib�ص���ͷ
            it++;
            continue;
        }
    }
    if (!b.terms.empty()) // ���b����ʣ��˵���ǲ����κ�t�ظ���
    {
        //cout << "!b.terms.empty()" << endl;
        ib = b.terms.begin();
        ibEnd = b.terms.end();
        for (; ib != ibEnd; ib++)
            c.terms.push_back(*ib);
    }
    // ���ϵĴ������bug,���������������ͬ��λ����1��Ԫ��,�����ڴ�˳��һ��ʱ�����
    // ����A������(4,5),(5,8),(6,2)��������,��ȷʵ��˳��ڷ�,B��(6,2),(4,5),(5,8),��ô��ӵĽ�����ظ���
    // ��Ϊ��������������ӳ��Ļ����ȷʵӦ��û������,���Ǽ��������ʱ��û�а�������ӳ��ͻ�������
    //int cSize = 0;//������������λ��,ÿ������1������1
    //while (it != itEnd && ib != ibEnd) // 2��ϡ�����ķ���Ԫ�ظ�����λ�ÿ��ܲ�ͬ
    //{
    //    // ���������ͬ,��Ҫ�ں�߲���ʣ����,������itҲ������ib�������
    //    // �����ж�λ��,λ����ͬ��Ҫ�½�1���ڵ�,ֵ���
    //    // ���������ͬλ��,��Ҫ����1���ڵ�,ֱ�Ӵ洢it����ib�Ľڵ㼴��
    //    // ˭�ȴ洢ȡ����λ�õ�ǰ��,С���Ȳ�
    //    int tIndex = (*it).row * cols + (*it).col; // ĳ���ڵ��ʵ��λ��=��ǰ����*������+��ǰ����
    //    int bIndex = (*ib).row * cols + (*ib).col;// b��*this��ͬ�͵�,����������cols
    //    //cout << "tindex = " << tIndex << "  bindex = " << bIndex << endl;
    //    if (tIndex < bIndex) // ʵ��λ�ÿ�ǰ���Ȳ���,cSize++��ʹ��
    //    {
    //        cout << "it < ib��cSize = " << cSize << endl;
    //        c.terms.insert(cSize++, *it); // ��ô��С��t�ڵ�
    //        it++; // 1��it�ڵ㱻ʹ�þ͵���һ��
    //    }
    //    else 
    //    {
    //        if (tIndex == bIndex) // ʵ��λ�������ֵ��Ӳ�Ϊ0��cSize++���ʹ��
    //        {
    //            if ((*it).value + (*ib).value != 0) 
    //            {
    //                cout << "it = ib��cSize = " << cSize << endl;
    //                matrixTerm<T> mTerm; // Ҫ�����½ڵ�,��Ϊ��ʱ����*it��*ib������
    //                mTerm.row = (*it).row; // ��Ϊλ����ͬ,ʹ��(*ib).rowҲ����
    //                mTerm.col = (*it).col;// ��Ϊλ����ͬ,ʹ��(*ib).colҲ����
    //                mTerm.value = (*it).value + (*ib).value; // ֱֵ����Ӽ���
    //                c.terms.insert(cSize++, mTerm); //
    //            }
    //            it++;
    //            ib++;
    //        }
    //        else
    //        { // cSize++��ʹ��
    //            cout << "it>ib��cSize = " << cSize << endl;
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
#endif  sparseMatrix_
