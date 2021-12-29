#pragma once
#include "charter5_linearList.h"
#include "charter6_chainNode.h"
#include "myExceptions.h"
#include <sstream>
#include <ostream>
template<class T>
class _charter6_chainListCircular
{
public:
    _charter6_chainListCircular();
    int size() const { return listSize; }
    int indexOf(const T& theElement) const;
    void insert(int theIndex, const T& theElement);
    void output(ostream& out) const;

protected:
    void checkIndex(int theIndex) const;
    _charter6_chainNode<T>* headerNode;  // ͷ�ڵ�
    int listSize;            
};

template<class T>
_charter6_chainListCircular <T>::_charter6_chainListCircular()
{
    headerNode = new _charter6_chainNode<T>(); // Ĭ�Ϲ�������1��ͷ�ڵ�

    headerNode->next = headerNode;//ͷ�ڵ��ʼ���󶨵���Ϣ��������
    listSize = 0;
}

template<class T>
void _charter6_chainListCircular<T>::checkIndex(int theIndex) const
{
    if (theIndex < 0 || theIndex >= listSize)
    {
        ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }

}

template<class T>
int _charter6_chainListCircular<T>::indexOf(const T& theElement) const
{
    headerNode->element = theElement; // �Ѳ��ҵ�Ԫ�ظ�ֵ��ͷ�ڵ��Ԫ��

    _charter6_chainNode<T>* currentNode = headerNode->next;
    int index = 0;  
    while (currentNode->element != theElement)//�����ٱȽ�currentNode!=NULL ֻ�Ƚ�Ԫ��
    {
        currentNode = currentNode->next;
        index++;
    }

    if (currentNode == headerNode) // ֻ��Ҫ�ж��Ƿ��ֻص�ͷ�ڵ㼴��
        return -1;
    else
        return index;
}

template<class T>
void _charter6_chainListCircular<T>::insert(int theIndex, const T& theElement)
{
    if (theIndex < 0 || theIndex > listSize)
    {
        ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }

    _charter6_chainNode<T>* p = headerNode; // ͷ�ڵ��ָ��
    for (int i = 0; i < theIndex; i++)
        p = p->next; // ��Ϊ����Ϊ��ִ��theIndex�ξͿ��Զ�����theIndex-1��

    p->next = new _charter6_chainNode<T>(theElement, p->next);

    listSize++;
}

template<class T>
void _charter6_chainListCircular<T>::output(ostream& out) const
{
    for (_charter6_chainNode<T>* currentNode = headerNode->next;
        currentNode != headerNode; // ��ǰ�ڵ�û���ٴη���ͷ�ڵ�Ļ���ִ��
        currentNode = currentNode->next)
        out << currentNode->element << "  ";
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const _charter6_chainListCircular<T>& x)
{
    x.output(out); return out;
}
