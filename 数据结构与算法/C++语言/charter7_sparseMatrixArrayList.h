#pragma once
#ifndef charter7_sparseMatrixArrayList_
#define charter7_sparseMatrixArrayList_
#include "charter5_linearList.h"
#include "myExceptions.h"
#include <iterator>
#include <sstream>
template<class T>
class sparseMatrixArrayList : public   _charter5_linearList<T>
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

    // ��ϡ����������Ա������ӵ��·���
    void reSet(int);
    void set(int, const T&);
    void clear() { listSize = 0; }
    void push_back(const T&);

    // ���������Ա���е������Ĺ���
    class iterator;
    iterator begin() { return iterator(element); } // elementָ�����Ա�ͷ
    iterator end() { return iterator(element + listSize); }// ָ�����Ա��β
    class iterator
    {
    public:
        typedef std :: bidirectional_iterator_tag iterator_category;
        typedef T value_type;
        typedef std:: ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;
        iterator(T* thePosition = 0) { index = 0; position = thePosition; }//λ����ָ������ Ψһ�Ĺ��캯��
        // �������н����ù�����Ҫ����,�õ�������ָ��Ľṹ��Ԫ��
        T& operator*() const { return *position; }
        T* operator->() const { return &*position; }
        operator int() const { return index; }; // �õ�ָ�����������λ��

        iterator& operator++()   //++operator 
        {
            ++position; index++; return *this;//�ȣ��󷵻�
        }
        iterator operator++(int) // operator++
        {
            iterator old = *this; // ���ʽ��ֵ����֮ǰ��
            ++position; // ��+
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

        // !=����
        bool operator!=(const iterator right) const
        {
            return position != right.position; // �������Ƿ����תΪλ���Ƿ����
        }
        bool operator==(const iterator right) const
        {
            return position == right.position;
        }
    protected:
        T* position; // λ��ָ�� ˽������
        int index;
    };  

protected:
    void checkIndex(int theIndex) const;
    void changeLength1D(T*& pa, int oldLength, int newLength); // ָ�������
    T* element;            
    int arrayLength;       
    int listSize;
};
template<class T>
sparseMatrixArrayList<T>& sparseMatrixArrayList<T>::operator=(const sparseMatrixArrayList<T>& theList)
{
    //sparseMatrixArrayList<T> newList(theList); // ��Ҫ���ø��ƹ���,��ʹ�����ڴ�
    arrayLength = theList.arrayLength;
    listSize = theList.listSize;
    element = theList.element; // ������
    return *this; // �����Լ�
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

    if (theSize > arrayLength) // �����������,������changeLength1D,ֱ��new����
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
    // element[theIndex]��T���͵�
    element[theIndex] = newValue; //ע��洢����value,����ʽ����Ҳ����ʽ����
}

template<class T>
int sparseMatrixArrayList<T>::indexOf(const T& theElement) const
{
    // listSize��ȡ������,findҪ���2��������ʵ��λ��listSize-1�ĺ�һλ����
    // ���ص�λ��Ҫ��ȥelement���ռ�ݵ�λ�ò���ʵ��λ�� ��ǿתΪint��
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
    // �����ƶ�theIndex+1(����)��listSize(������)��Ԫ��
    // ���Ƶ�element+theIndex��λ��,��ʵ���Ǹ��ǲ���
    // copy������������,���Ա�׼��Ϊelement+theIndex
    // --listSize�Ѿ�-1,ĳλ��Ԫ��λ�����ڴ浫�ǿյ�������
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
    // �����������,��Ҫ��չ����,��չ����Ϊ2
    if (listSize == arrayLength)
    {
        // ����Ĳ���������ָ�������,��֤����elementָ����һ���¿��ٵ��ڴ��ַ
        // ԭ�����ڴ��ַ��changeLength1D���Ѿ�delete [] 
        changeLength1D(element, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }
    // ��չ�������ԭ����Ԫ����������1����λ
    // �������Ҹ���,ʹ��copyҪ���׼�������,�����Ƶ�element+theIndex+1(����)
    // Ҳ����ʹ��copy_backward,��׼�����Ҳ�,element+listSize+1(������)
    copy_backward(element + theIndex, element + listSize,
        element + listSize + 1);
    // element[theIndex]��T���͵�
    element[theIndex] = theElement; // �洢����value,����ʽ����Ҳ����ʽ����
    listSize++;
}

template<class T>
void sparseMatrixArrayList<T>::changeLength1D(T*& pa, int oldLength, int newLength)
{
    if (newLength < 0)
        throw illegalParameterValue("new length must be >=0");
    T* temp = new T[newLength];
    int number = std::min(oldLength, newLength);//�Ƚ���չǰ��Ŀ��
    std::copy(pa, pa + number, temp);//��չ��ʵ��λ����number-1
    delete[] pa;
    pa = temp;//Ҫ��չ���ڴ�ָ��ָ��temp,����tempָ����ڴ�û�г�ΪҰָ��
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

#endif // charter7_sparseMatrixArrayList_

