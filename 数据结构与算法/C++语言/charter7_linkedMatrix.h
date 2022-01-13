#pragma once
#ifndef linkedMatrix_
#define linkedMatrix_
#include <iostream>
#include "charter7_linkedMatrixElements.h"
#include "myExceptions.h"
// ���ԭ�����ȥ����>>������,ֱ�Ӷ�����һ���������캯��
template<typename T>
class linkedMatrix
{
    friend ostream& operator<<<> (ostream&, linkedMatrix<T>&);
public:
    linkedMatrix() { rows = 0; cols = 0; };
    linkedMatrix(const int&, const int&,linkedMatrixChain<rowLinkedList<T>>&) ;
    ~linkedMatrix() {};
    T operator() (const int & , const int &) ;
    void transpose(linkedMatrix<T>& b);
    void output();
private:
    int rows,      
        cols;      
    linkedMatrixChain<rowLinkedList<T> > headerChain;
    // headerChain[i]Ϊ������ṹ��,headerChain[i].rowChain[j]Ϊ������Ԫ�ؽṹ��
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
    typename linkedMatrixChain<rowLinkedList<T> >:: iterator it = headerChain.begin();
    typename linkedMatrixChain<rowLinkedList<T> >:: iterator itEnd = headerChain.end();
    while (it != itEnd)
    {
        int r = it->getRow();
        if (row != r) //û������������Ԫ��
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
            if (rt == rtEnd) // ������û����
                return 0;
        }
    }
    if (it == itEnd)// û���ҵ����з���0
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
    // ת�õľ������b���
    b.headerChain.clear(); 
    b.rows = cols;
    b.cols = rows;
    linkedMatrixChain<rowLinkedListElement<T> >* bin; // 1��ָ�����������͵�ָ��,Ԫ���ǽṹ��
    bin = new linkedMatrixChain<rowLinkedListElement<T> >[cols + 1]; // ���б���cols��Ԫ��
    typename linkedMatrixChain<rowLinkedList<T> >::iterator // ���������������ĵ�����
        ih = headerChain.begin(),
        ihEnd = headerChain.end(); // ���ڱ�����������ÿ��������

    while (ih != ihEnd) // ������
    {
        int r = ih->getRow(); //ÿ��������������row
        typename linkedMatrixChain<rowLinkedListElement<T> >::iterator // ���嵱ǰ������ĵ�����
            ir = ih->rowChain.begin(), 
            irEnd = ih->rowChain.end();
        rowLinkedListElement<T> x; // ���ڴ�ŵ�ǰ�����������Ԫ��
        x.col = r; // ת�õĵ�1�����Ƚ������е�����
        while (ir != irEnd) // ������ǰ�������ÿ��
        {
            x.value = ir->getValue(); // ir�ǵ�ǰ�е�Ԫ��ֵ
            bin[ir->col].push_back(x); // ѭ��������bin[col]��洢*thisÿ�е�����Ԫ��.��Ԫ���Ѿ�����������
            // bin[ir->col]�ʼ���Ǹ������������ͷ�ڵ�,������Ҫ���洢�ĵ�ַ,����Ԫ���Ѿ��Զ�����
            ir++;  
        }
        ih++; 
    }

    rowLinkedList<T> h;
    for (int c = 1; c <= cols; c++)
        if (!bin[c].empty()) // �е��п��ܶ���0Ԫ�����ж�
        {
            // h���費ͬ��ֵȻ��b.headerChain ��Ӽ���
            h.row = c;
            h.rowChain = bin[c]; // �������ó���
            b.headerChain.push_back(h);
            bin[c].zero(); // ȡ����1����h��ɾ��
        }
    h.rowChain.zero();   // h�����˾�û����
    delete[] bin;
    /*
    ���� *this = [ [0,0,1,2,4,0]
                            [0,5,9,6,10,0]
                            [0,13,17,9,3,0]]
    rows = 3, cols = 6 , bin[6+1] (ֻ�õ�1,2,3,4,5,6)
    ��ôbin�Ľ������
    bin[1]��bin[6]û��Ԫ��,bin[0]���ò�����,��Ҳ��Ϊ��bin�������cols+1���ڴ�
    bin[2]��                           (col=2,value=5),(col=3,value=13)
    bin[3]��(col=1,value=1),(col=2,value=9),(col=3,value=17)
    bin[4]��(col=1,value=2),(col=2,value=6),(col=3,value=9)
    bin[5]��(col=1,value=4),(col=2,value=10),(col=3,value=13)
    ת����Ҫ����3���£�
        �� �Ѵ洢��ÿ��Ԫ�ص�����ֵҪ�޸�,Ҳ����x.col = r
        �� b��˽������cols��rows���� ,b.rows = cols && b.cols = rows
        �� �õ�ת�ú��ͷ�ڵ�,ǡ����*this�ĵ�1�е����з�0Ԫ�صĵ�ַ(ԭ����ÿ�е��׸���0Ԫ�ص�ַ),Ҳ����bin[col]
        �� �洢�������ͷ���������ֵҲҪ�޸�,�� h.row = c && h.rowChain = bin[c]
    c = 1,2,3,4,5,6 (only 2,3,4,5 not empty)
    h.row = 2,3,4,5, h.rowChain = bin[2],bin[3],bin[4],bin[5],�൱�ڰѵ�1�е����з�0Ԫ�ص�ַ����b��ͷ�ڵ�����
*/

}

#endif linkedMatrix_