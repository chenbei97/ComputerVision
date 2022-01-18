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
    _charter6_chainNode<T>* headerNode;  // ͷ�ڵ�,����firstNode
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

    _charter6_chainNode<T>* currentNode = headerNode->next; // ע��ָ��ָ��Ĳ���ͷ�ڵ�����׽ڵ�
    int index = 0;  
    while (currentNode->element != theElement)//�����ٱȽ�currentNode!=NULL ֻ�Ƚ�Ԫ��,���׽ڵ㿪ʼ�жϵ�
    {
        currentNode = currentNode->next; // index���������listSize-1�жϲ���,��һ����listSize
        index++; // ��ʱcurrentNode = headerNone���ǿ��Լ����жϵ�,��headerNone�Ѿ���ֵ����theElement,������Ⱥ��˳�ѭ��
    }

    if (currentNode == headerNode) // ֻ��Ҫ�ж��Ƿ��ֻص�ͷ�ڵ㼴�� while�˳�ѭ��ʱ�ض���headerNone
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

    _charter6_chainNode<T>* p = headerNode; // ͷ�ڵ��ָ������ʵ��ͷ�ڵ�,���׽ڵ㲻���
    for (int i = 0; i < theIndex; i++)
        p = p->next; 
    p->next = new _charter6_chainNode<T>(theElement, p->next); 
    // �����ͷ�岻��ִ��for,���������½ڵ�,����½ڵ�ָ����ͷ�ڵ�,���õ�ǰ��ͷָ��ָ���½ڵ㼴��
    // �������ͷ��,p�����ƶ�theIndex��ָ�����λ�õ�ǰ1��,��Ϊͷ�ڵ㲻���׽ڵ�
    // ��pָ�����һ��Ҳ���ǵ�theIndex���ڵ㹹���µ�,�ٸ���pָ������½ڵ�,�������ͬ��
    // �ر����β��,theIndex=listSizeʱ,pָ��ľ���listSize-1,����ڵ���ͷ��ʱ�Ѿ�ָ����ͷ�ڵ�
    // �������½ڵ�Ҳ�������Ϣ,��ʱp����ָ���½ڵ�,�½ڵ�ָ��headerNode
    
    /*
    ����ѭ���ڵ�,���ط��ǲ���ͷ��,����p->next����,headerNode��ʼ��ָ������Լ�������NULL
    �Ƚ�ԭ���Ĵ���ʵ��
    if (theIndex == 0)
        this->firstNode = new _charter6_chainNode<T>(theElement, firstNode); ��
    else
    {
        _charter6_chainNode<T>* p = firstNode; ��
        for (int i = 0; i < theIndex - 1; i++) ��
                p = p->next; ��
        p->next = new _charter6_chainNode<T>(theElement, p->next); ��
    }
    �� ���д����ԭ������ȫһ��û�б仯
            �����ͷ��,������½ڵ���ԭ����firstNode(���캯�����Ѿ�ָ��NULL)����Ϣ�����,�ٸ����׽ڵ�ָ������ڵ�
           ͷ��Ĺ�����charter6_chainListWithIterator.h�Ѿ���ϸ˵��
           
    �� ���������ͷ��,����1���׽ڵ�ָ��,���ָ���ܻ����е�����Ľڵ��ǰ1��λ��
    �� theIndexȡֵ��ΧΪ[1,listSize] �����Ѿ���1���ڵ��Ҹýڵ��next�ڢ���׼������(β�ڵ�ָ��NULL)
         1. ȡ1,�ܲ�ִ��,��ǰ��p����ָ��firstNode(0),������λ�õ�ǰ1��
         2. ȡ2,��ִ��1��,��ǰpָ��λ��1,�ǲ���λ�õ�ǰ1��
         3. ȡindex,��ִ��index-1��,pָ��λ��index-1,�ǲ���λ�õ�ǰ1��
         4. ȡlistSize-1,��ִ��listSize-2��,pָ��λ��listSize-2
            �ǲ���λ��listSize-1(β�ڵ�)��ǰ1��(Ҳ��β�ڵ��ǰ1��,������2��)
         5. ȡlistSize,��ִ��listSize-1��,pָ��λ��listSize-1,��˵������Ľڵ���β��(����)
    ��  �Ե�ǰpָ��Ľڵ���Ϣ(����λ�õ���1��)�������½ڵ�(��1�����в���λ������ڵ���Ϣ)
          �����������2������,��һ���ڵ��nextָ���µĽڵ�,ͬʱ�µĽڵ��������ԭ������Ϣ(�����ʱ��ͱ�����ԭ�ڵ����Ϣ)
          1. ȡ1,��1�ڵ���Ϣ�������½ڵ��ƶ���2�Žڵ�(�����ƶ�),���ڵ�1�ڵ�(����p)ָ�����½ڵ�(2�Žڵ�)�ĵ�ַ
          2. ȡ2,ͬ��p�ƶ���2�Žڵ�(λ��1),��������Ϣ(��1����NULL)�����½ڵ�,�ٸ���pָ������½ڵ�
          3. ȡindex,pָ��index-1,��index(p->next)�����½ڵ�(������p->next->next��Ϣ),����pָ���½ڵ㼴��
          4. ȡlistSize-1,��listSize-1�Ľڵ�(listSize-2 ->next)�����½ڵ�(������listSize-1����Ϣ),����p->nextָ�򹹽����½ڵ�
          5. ȡlistSize,��listSize-1��next(��NULL)�����½ڵ�,p->next��listSize-1ָ����NULL�½ڵ�
*/
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
