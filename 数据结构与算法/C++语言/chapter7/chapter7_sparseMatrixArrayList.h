#pragma once
#ifndef chapter7_sparseMatrixArrayList_
#define chapter7_sparseMatrixArrayList_
#include "chapter5_linearList.h"
#include "myExceptions.h"
#include <iterator>
#include <sstream>
template<class T>
class sparseMatrixArrayList : public   _chapter5_linearList<T>
{
public:
    sparseMatrixArrayList(int initialCapacity = 10);
    sparseMatrixArrayList(const sparseMatrixArrayList<T>&);
    ~sparseMatrixArrayList() { if (element != NULL) element = NULL; delete[] element; }
    bool empty() const { return listSize == 0; }
    int size() const { return listSize; }
    int capacity() const { return arrayLength; }
    sparseMatrixArrayList<T>& operator = (const sparseMatrixArrayList<T>&);
    T& get(int ) const;
    int indexOf(const T& ) const;
    void erase(int );
    void insert(int , const T&);
    void output(ostream&) const;

    // 对稀疏矩阵类线性表新增加的新方法
    void reSet(int);
    void set(int, const T&);
    void clear() { listSize = 0; }
    void push_back(const T&);

    // 完整的线性表具有迭代器的功能
    class iterator;
    iterator begin() { return iterator(element); } // element指向线性表开头
    iterator end() { return iterator(element + listSize); }// 指向线性表结尾
    class iterator
    {
    public:
        typedef std :: bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef std:: ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;
        iterator(T* thePosition = 0) { index = 0; position = thePosition; }//位置是指针类型 唯一的构造函数
        // 迭代器有解引用功能需要重载,得到迭代器指向的结构体元素
        T& operator*() const { return *position; }
        T* operator->() const { return &*position; }
        operator int() const { return index; }; // 得到指向的整数索引位置

        iterator& operator++()   //++operator 
        {
            ++position; index++; return *this;//先＋后返回
        }
        iterator operator++(int) // operator++
        {
            iterator old = *this; // 表达式的值还是之前的
            ++position; // 后+
            index++;
            return old;
        }
        iterator& operator--()   // --operator
        {
            --position; index--; return *this;
        }
        iterator operator--(int) // operator--
        {
            iterator old = *this;
            --position;
            index--;
            return old;
        }

        // !=重载
        bool operator!=(const iterator right) const
        {
            return position != right.position; // 迭代器是否相等转为位置是否相等
        }
        bool operator==(const iterator right) const
        {
            return position == right.position;
        }
    protected:
        T* position; // 位置指针 私有属性
        int index;
    };  

protected:
    void checkIndex(int theIndex) const;
    void changeLength1D(T*& pa, int oldLength, int newLength); // 指针的引用
    T* element;            
    int arrayLength;       
    int listSize;
};
template<class T>
sparseMatrixArrayList<T>& sparseMatrixArrayList<T>::operator=(const sparseMatrixArrayList<T>& theList)
{
    //sparseMatrixArrayList<T> newList(theList); // 不要利用复制构造,会使用新内存
    arrayLength = theList.arrayLength;
    listSize = theList.listSize;
    element = theList.element; // 是引用
    return *this; // 返回自己
}
template<class T>
sparseMatrixArrayList<T>::sparseMatrixArrayList(int initialCapacity)
{
    if (initialCapacity < 1)
    {
        ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }
    element = new T[initialCapacity];
    arrayLength= initialCapacity;
    listSize = 0;
}
template<class T>
sparseMatrixArrayList<T>::sparseMatrixArrayList(const sparseMatrixArrayList<T>& theList)
{
    arrayLength = theList.arrayLength;
    listSize = theList.listSize;
    element = new T[arrayLength];
    copy(theList.element, theList.element + listSize, element);
}
template<class T>
void sparseMatrixArrayList<T>::reSet(int theSize)
{
    if (theSize < 0)
    {
        ostringstream s;
        s << "Requested size = " << theSize << " Must be >= 0";
        throw illegalParameterValue(s.str());
    }

    if (theSize > arrayLength) // 需求比容量大,不调用changeLength1D,直接new即可
    {
        delete element;
        element = new T[theSize];
        arrayLength = listSize;
    }
    listSize = theSize;
}

template<class T>
T& sparseMatrixArrayList<T>::get(int theIndex) const
{
    checkIndex(theIndex);
    return element[theIndex];
}

template<class T>
void sparseMatrixArrayList<T>::set(int theIndex, const T& newValue)
{
    checkIndex(theIndex);
    // element[theIndex]是T类型的
    element[theIndex] = newValue; //注意存储的是value,不显式调用也会隐式调用
}

template<class T>
int sparseMatrixArrayList<T>::indexOf(const T& theElement) const
{
    // listSize是取不到的,find要求第2个参数是实际位置listSize-1的后一位成立
    // 返回的位置要减去element这个占据的位置才是实际位置 并强转为int型
    int theIndex = (int)(find(element, element + listSize, theElement)- element);
    if (theIndex == listSize)
        return -1;
    else return theIndex;
}

template<class T>
void sparseMatrixArrayList<T>::erase(int theIndex)
{
    checkIndex(theIndex);
    copy(element + theIndex + 1, element + listSize,
        element + theIndex); 
    // 整体移动theIndex+1(包含)到listSize(不包含)的元素
    // 复制到element+theIndex的位置,其实就是覆盖操作
    // copy是整体向左复制,所以标准点为element+theIndex
    // --listSize已经-1,某位的元素位置有内存但是空的析构掉
    element[--listSize].~T(); 
}

template<class T>
void sparseMatrixArrayList<T>::push_back(const T& theElement)
{
    if (listSize == arrayLength)
    {
        changeLength1D(element, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }
    T value = theElement;
    element[listSize] = theElement;
    listSize++;
}

template<class T>
void sparseMatrixArrayList<T>::insert(int theIndex, const T& theElement)
{
    if (theIndex < 0 || theIndex > listSize)
    {
        ostringstream s;
        s << "index = " << theIndex << " size = " << listSize << "  inde should be in [0,size)";
        throw illegalIndex(s.str());
    }
    // 如果容量已满,需要拓展容量,拓展倍数为2
    if (listSize == arrayLength)
    {
        // 传入的参数必须是指针的引用,保证还是element指向了一个新开辟的内存地址
        // 原来的内存地址在changeLength1D中已经delete [] 
        changeLength1D(element, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }
    // 拓展容量后把原来的元素整体右移1个单位
    // 整体向右复制,使用copy要求标准点是左端,即复制到element+theIndex+1(包含)
    // 也可以使用copy_backward,标准点是右侧,element+listSize+1(不包含)
    copy_backward(element + theIndex, element + listSize,
        element + listSize + 1);
    // element[theIndex]是T类型的
    element[theIndex] = theElement; // 存储的是value,不显式调用也会隐式调用
    listSize++;
}

template<class T>
void sparseMatrixArrayList<T>::changeLength1D(T*& pa, int oldLength, int newLength)
{
    if (newLength < 0)
        throw illegalParameterValue("new length must be >=0");
    T* temp = new T[newLength];
    int number = std::min(oldLength, newLength);//比较拓展前后的宽度
    std::copy(pa, pa + number, temp);//拓展的实际位置是number-1
    delete[] pa;
    pa = temp;//要拓展的内存指针指向temp,所以temp指向的内存没有成为野指针
}

template<class T>
void sparseMatrixArrayList<T>::checkIndex(int theIndex) const
{
    if (theIndex < 0 || theIndex >= listSize)
    {
        ostringstream s;
        s << "index = " << theIndex << " size = " << listSize<<"  index should be in[0,size)!";
        throw illegalIndex(s.str());
    }
}

template<class T>
void sparseMatrixArrayList<T>::output(ostream& out) const
{
    copy(element, element + listSize, ostream_iterator<T>(cout, "  "));
}

template <class T>
ostream& operator<<(ostream& out, const sparseMatrixArrayList<T>& x)
{
    x.output(out); return out;
}

#endif // chapter7_sparseMatrixArrayList_

