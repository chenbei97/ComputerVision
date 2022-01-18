#pragma once
#include "charter5_linearList.h"
#include <sstream>
// ���Ա�ľ�������������ֱ��ʵ��,���ӵĺ������ļ�ʵ��
template<class T>
class _charter5_arrayList : public _charter5_linearList<T>
{
public:
    // ʱ�临�Ӷ�ΪO(1),�Զ���ʱʱ�临�Ӷ�ΪO(initialCapacity)
    _charter5_arrayList(int initialCapacity = 10); // Ĭ�Ϲ���

    // ʱ�临�Ӷ�ΪO(n)
    _charter5_arrayList(const _charter5_arrayList<T>&); // ���ƹ���,�� _charter5_arrayList<T>���忴��1����������

    ~_charter5_arrayList() { delete[] element; }//��������

    // ��������麯��ʵ��
    // ʱ�临�Ӷ�ΪO(1)
    bool empty() const { return listSize == 0; }// ��ʾ�����Ա���������thisָ��Ϊconst,���ܸ������������Ա,���const��ǰ��ʾ����ֵ��const

     // ʱ�临�Ӷ�ΪO(1)
    int size() const { return listSize; }// Ԫ�ظ���

    // ʱ�临�Ӷ�Ϊ��(1)
    T& get(int theIndex) const;

    // ʱ�临�Ӷ�ΪO(max{listSize,1})=>O(listSize)
    int indexOf(const T& theElement) const; // ���ܸı����ԱҲ���ܸı�ʵ����Ԫ��,ǰ����������ʵ��������������

    // û�д�Ԫ��������(1),�еĻ�Ϊ��(listSize-theIndex),ÿһ��Ԫ�ص��ƶ���ҪO(1),�ϼ�O(listSize-theIndex)
    void erase(int theIndex);

    // �Ƿ��׳��쳣��(1),�������ǰ����ռ����ͻ����鳤�ȼӱ�,Ϊ��(arrayLength)=��(listSize)
    // �ƶ�����Ԫ�ئ�(listSize-theIndex),�ܵ�ʱ�临�Ӷ�O(listSize)
    void insert(int theIndex, const T& theElement);

    // ʱ�临�Ӷ�ΪO(listSize)
    void output(std::ostream& out) const;

    // ��������
    // ʱ�临�Ӷ�ΪO(1)
    int capacity() const { return arrayLength; }

protected:
    // ȷ��һ��Ԫ����0~listSize-1�е�����,ע�ⲻ��arrayLength
    // ʱ�临�Ӷ�Ϊ��(1)
    void checkIndex(int theIndex) const; // ���ɸ������Ա�ĳ�Ա����

    // ʱ�临�Ӷ�Ϊ��(n)
    void changeLength1D(T*& pa, int oldLength, int newLength); // ������������ʱ�ӱ�

    int arrayLength; // ���Ա��������listSize
    int listSize; // ���Ա��Ԫ�ظ���
    T* element;
    // �洢���Ա�Ԫ�ص�һά����,��Ϊ�Ƕ�̬���������������������delete[]
};
