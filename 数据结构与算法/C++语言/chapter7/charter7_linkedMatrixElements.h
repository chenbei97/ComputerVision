#pragma once
#ifndef charter7_linkedMatrixElements_
#define charter7_linkedMatrixElements_
#include "charter7_linkedMatrixChain.h"
// ���������Ҫʹ�ö�����������洢ÿ�е�Ԫ��,����������������Ԫ����1��������rowLinkedList
// _charter6_chainListWithIteratorExtend<rowLinkedList<T>> headerChain

// ���������������row�Ͱ�������������Ԫ�ص�����,ָ����next��������֮���������
//�������Ԫ������1���ṹ������,������洢��col��value

// �����ṹ���ԭ�����ȥ����output����
template<class T>
struct rowLinkedListElement
{
    int col;
    T value;

    bool operator !=(const rowLinkedListElement<T>& y)
    {
        return (value != y.value); // �ṹ��Ƚ�תΪvalue�Ƚ�
    }
    int getCol() const { return col; } // �����const
    T getValue() const { return value; }
};
// ����Ҫ��<<�����������뱨��û���� "charter6_chainListWithIterator.h"<<��Ӧ��ת��
// ��Ϊ�����<<������ӡ����currentNode->element,��currentNode��chainNode����
// chainNode�и�T element,�����T ��ʵ����rowLinkedListElement����,��ô��ӡelement�ǲ�֪��ʲô��˼��
// ��Ϊelement�Ǹ��ṹ�岻��һ����,���Խṹ�嶨���ʱ��ͱ������<<�ýṹ��ķ���
template<class T> 
ostream& operator<<(ostream& out, const rowLinkedListElement<T>& x)
{
    out  <<"col("<< x.getCol() << ") = " << x.getValue() << " "; 
    return out;
}

// ͷ�ڵ�ṹ��,������������row��row�洢��Ԫ��rowLinkedListElement,������Ԫ������Ӧ������洢
// ͬ����Ҳ�Ǹ��ṹ��,��ӡ�����Ľṹ��ʱҲ���������Ӧ�����ط���
template<class T>
struct rowLinkedList
{
    int row;
    
    linkedMatrixChain<rowLinkedListElement<T> > rowChain;

    bool operator !=(const rowLinkedList<T>& y)
    {
        return (row != y.row); // תΪ�Ƿ���ͬ��
    }
    int getRow() const { return row; }
};
template<class T>
ostream& operator<<(ostream& out,const rowLinkedList<T>& x)
{
    // << x.rowChain ���õľ���out  <<","<< x.getCol() << " ) = " << x.getValue() << endl;
    out << "\nrow(" << x.getRow() << ")��";
    out<<x.rowChain; 
    return out;
}
#endif charter7_linkedMatrixElements_