#pragma once
#ifndef chapter7_tridiagonalMatrixRowMapping_
#define chapter7_tridiagonalMatrixRowMapping_
#include "myExceptions.h"
using namespace std;
template<class T>
class tridiagonalMatrixRow
{
public:
    tridiagonalMatrixRow(int theN = 10);
    tridiagonalMatrixRow(T const * , const int&); // 常量指针,++a可以,*a=3不可以
    ~tridiagonalMatrixRow() { if (element != NULL) element = NULL; delete[] element; }//改成这样就不会出错了
    T get(int, int) const;
    void set(int, int, const T&); 
    friend ostream& operator<<<>(ostream&, const tridiagonalMatrixRow<T>&);
private:
    int n;
    T* element;
};

template<class T>
tridiagonalMatrixRow<T>::tridiagonalMatrixRow(int theN)
{
    if (theN < 1)
        throw illegalParameterValue("Matrix size must be > 0");
    n = theN;
    element = new T[3 * n - 2];
}

template<class T>
tridiagonalMatrixRow<T>::tridiagonalMatrixRow( T const *  data, const int& theN)
{// 常量指针 可以改变指向不能改变值
    if (theN < 1)
        throw illegalParameterValue("Matrix size must be > 0");
    n = theN;
    element = new T[3*(size_t)n-2];
    copy(data, data + 3* (size_t)n-1, element); // 是末位元素的后1个位置
}

template <class T>
T tridiagonalMatrixRow<T>::get(int i, int j) const
{
    /*
    注意，某个坐标(xi,xi)总是下边和右边有1个元素，也就是如果访问某个坐标(xi,y)，xi和y的差只有0,1或者-1。
​	    如果xi-y=0，说明是对角元素，那么访问A(xi,xi)只需要确定x的位置i，1≤i≤n。
                因为主对角坐标(i,i)和element的k坐标总是满足k=3i-3的关系,即A(i,i)=element(3i-3)，因为对角元素之间总是差2个元素。
​		        根据A(1,1)=element[0],A(2,2)=element[3],A(3,3)=element[6],..，可总结出关系为A(i,i)=element[3i-3]。这个关系的前提是行主映射。
​		如果xi-y=1，说明访问的是A(xi-1,xi-1)的下方元素，即element[3(i-1)-3+2]，+2是隔了1个元素。这里要注意，行索引大于列索引说明是低对角线，可以向上找A(xi-1,xi-1)的下方，
                也可以找当前行A(xi,yi)的左边元素，即element[3i-3-1]。可以发现3i-3-1其实就是3(i-1)-3+2=3i-4，位置没有变化。
​		如果xi-y=-1，说明访问的是A(xi,xi)的右方元素，即element[3i-3+1]，+1是当前行下一列。或者A(xi+1,xi+1)的上方元素，即element[3(i+1)-3-2]，即element[3i-2]，结果也是一样的。
    总结：
        ①A(i,i)对应element[3i-3]
​		②A(i,j),i-j=1,在A(i,i)左边或者A(i-1,i-1)的下边,但都对应的是element[3i-4]
​		③A(i,j),i-j=-1在A(i,i)右边或者A(i+1,i+1)的上边,但都对应的是element[3i-2]
    */
    if (i < 1 || j < 1 || i > n || j > n)
        throw matrixIndexOutOfBounds();
    switch (i - j)
    {
    case 0:
        return element[3 * i - 3] ; 
    case 1:
        return element[3 * i - 4]; 
    case -1:
        return element[3 * i - 2]; 
    default:
        return 0;
    }
}

template<class T>
void tridiagonalMatrixRow<T>::set(int i, int j, const T& newValue)
{
    if (i < 1 || j < 1 || i > n || j > n) 
        throw matrixIndexOutOfBounds();
    switch (i - j)
    {
    case 0:
        element[3 * i - 3] = newValue; break;
    case 1:
        element[3 * i - 4] = newValue; break;
    case -1:
        element[3 * i - 2] = newValue; break;
    default:
        if (newValue != 0)
            throw illegalParameterValue
            ("nontridiagonal elements must be zero");
    }
}

template<class T>
ostream& operator<<<>(ostream& out, const tridiagonalMatrixRow<T>& m)
{
    // A(i,i)对应element[3i-3]
    // A(i,j),i-j=1,在A(i,i)左边或者A(i-1,i-1)的下边,但都对应的是element[3i-4]
    // A(i,j),i-j=-1在A(i,i)右边或者A(i+1,i+1)的上边,但都对应的是element[3i-2]
    for (int i = 1; i <= m.n; i++)
    {
        for (int j = 1; j <=m.n; j++)
        {
            switch (i-j)
            {
            case 0:
                cout << m.element[3 * i - 3] << "  "; break;
            case 1:
                cout << m.element[3 * i - 4] << "  "; break;
            case -1:
                cout << m.element[3 * i - 2] << "  "; break;
            default: 
                cout << 0 << "  "; break;
            }
        }
        out << endl;
    }
    return out;
}
#endif chapter7_tridiagonalMatrixRowMapping