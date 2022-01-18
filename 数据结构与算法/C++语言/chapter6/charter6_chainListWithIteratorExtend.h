#pragma once
// ��չ�ĳ�����ľ�����ʵ��: �̳б�������,�̳��Ѿ�ʵ�ֺõ�chainListWithIterator��
// ����clear��push_back�ķ���ʵ��,push_back��Ҫ1��˽�г�ԱlastNodeָ��β�ڵ�
// β��ʱ��Ͳ�����ʹ��insert����,ֱ��ʹ��push_back����,�ٶȺܿ�
// ����insert��erase������ı�β�ڵ�,������2������Ҫ��д���Ӷ�lastNode�ĸ���
// �������໹�������zero����,ͷ�ڵ�ָ����Լ�listSize=0
#include <iostream>
#include <sstream>
#include <string>
#include "myExceptions.h"
#include "charter6_chainNode.h"
#include "charter6_linearListExtend.h" // �̳���չ
#include "charter6_chainListWithIterator.h" // �����Ѿ�ʵ�ֵ�chain�޸�2�����������ӳ�Ա����
template<class T>
class _charter6_chainListWithIteratorExtend : public _charter6_chainListWithIterator<T>, _charter6_linearListExtend<T>
{
public:
    // ���캯����ͬ����ͨ����,��Ҫ�̳�_charter6_chainListWithIterator
    // ע����μ̳е��β�,ǰ����Ҫһ��
    _charter6_chainListWithIteratorExtend(int initialCapacity = 10)  : 
        _charter6_chainListWithIterator<T>(initialCapacity) {} 
    _charter6_chainListWithIteratorExtend(const _charter6_chainListWithIteratorExtend<T>& theList) : 
        _charter6_chainListWithIterator<T>(theList) {}
    
    // ����̳и����ͬ�������ᱻ����,empty,size,get,indexOf,output���ᱻ����,this->�޷����ø���
    // ���캯����û�и��ǵķ���checkIndex��<<���أ�û�и��ǵ���_charter6_iterator����ͨ��ԱfirstNode��listSize��ֱ�Ӽ̳пɱ�this����
    // �������д����,erase,insertֱ����д����
    // ���������д����ֱ��ʹ�ø���ķ���,��Ҫ class :: method�ĸ�ʽ���ø��෽��
    bool empty() const { return this->listSize == 0; }// ʹ�ü̳�,�Լ�дthis->empy()�Ǵ����,���ǿ���ʹ��return this->listSize == 0��_charter6_chainListWithIterator<T>::empty();
    int size() const { return this->listSize; } // �Լ�д�Ļ�Ҫ�ǵ÷���this->listSize������listSize���򱨴�ʶ�� ,Ҳ����return _charter6_chainListWithIterator<T>::listSize; 
    T& get(int theIndex) const
    {
        return _charter6_chainListWithIterator<T>::get(theIndex); // ʹ�ü̳е��÷���
    }
    int indexOf(const T& theElement) const
    {
        return _charter6_chainListWithIterator<T>::indexOf(theElement);
    }
    void output(ostream& out) const
    {
        _charter6_chainListWithIterator<T>::output(out);
    }
    void clear()
    {
        // �����������Ĵ���һ��
        while (this->firstNode != NULL)
        {
            _charter6_chainNode<T>* nextNode = this->firstNode->next;
            delete this->firstNode;
            this->firstNode = nextNode;
        }
        this->listSize = 0;
    }   // ��Ҫʵ��
    void erase(int theIndex); // ����ʵ��
    void insert(int theIndex, const T& theElement); // ����ʵ��
    void push_back(const T& theElement);
    void zero()
    {
        this->firstNode = NULL; this->listSize = 0;
    }
protected:
    _charter6_chainNode<T>* lastNode;  // β�ڵ�ָ��
};

// erase��������ʵ��
template<class T>
void _charter6_chainListWithIteratorExtend<T>::erase(int theIndex)
{
    this->checkIndex(theIndex); // ���õ��Ǽ̳еķ���
    _charter6_chainNode<T>* deleteNode;
    if (theIndex == 0)
    {
        deleteNode = this->firstNode;
        this->firstNode = this->firstNode->next;
    }
    else
    {  
        _charter6_chainNode<T>* p = this->firstNode;
        for (int i = 0; i < theIndex - 1; i++)
            p = p->next;

        deleteNode = p->next;
        p->next = p->next->next; 
        if (deleteNode == lastNode) // ���ӵĴ����޸�:���indexɾ������β�ڵ���Ҫ���·�����Ҫ
            lastNode = p; // ˵�����ڵ�p(index-1)��β�ڵ���,���¼���
    }
    this->listSize--;
    delete deleteNode;
}

// insert��������ʵ��
template<class T>
void _charter6_chainListWithIteratorExtend<T>::insert(int theIndex, const T& theElement)
{
    if (theIndex < 0 || theIndex > this->listSize)
    {
        ostringstream s;
        s << "index = " << theIndex << " size = " << this->listSize;
        throw illegalIndex(s.str());
    }

    if (theIndex == 0)
    {
        this->firstNode = new _charter6_chainNode<T>(theElement, this->firstNode);
        // ��erase��ͬ,����Ĳ���β�ڵ�Ͳ�Ӱ��,insertһ����Ӱ��β�ڵ�
        if (this->listSize == 0)
            lastNode = this->firstNode; // ���һ��ʼû�нڵ�,����Ľڵ����ͷ�ڵ�Ҳ��β�ڵ�
        // ���һ��ʼ��ͷ�ڵ�,�Ҳ���Ľڵ���ͷ�ڵ�֮ǰ,û��Ӱ��
        // ��Ϊ�����2��Ԫ�رض��Ѿ������˵�1��Ԫ��,��ʱ��lastNode���Ѿ�ָ����ͷ�ڵ�(Ҳ�������ڵĵ�2���ڵ�)
    }
    else
    { // ���һ��ʼ��ͷ�ڵ�,���ǲ���Ľڵ�����ͷ�ڵ�֮��,�ͻ���Ӱ��
        // ��Ϊβ�ڵ㲻����ǰ��ͷ�ڵ���,�����´����Ľڵ�
        _charter6_chainNode<T>* p = this->firstNode;
        for (int i = 0; i < theIndex - 1; i++)
            p = p->next;
        p->next = new _charter6_chainNode<T>(theElement, p->next);//�´�����index�ڵ����Ϣ����1��index-1(p)�洢�������β��theIndex=listSize��pִ����listSize-1��,p�󶨵���Ϣ����listSizeλ�õĽڵ�
        if (this->listSize == theIndex)//����ڵ㲻��β��,β�ڵ㱾��û�иı�û��Ӱ�� lastNode��Ȼָ����ԭ����β�ڵ�
            lastNode = p->next; // �����β��,˵��p���µ�β�ڵ����һ��(theIndex=listSize-1λ��),p->next����β�ڵ��ַ(theIndex=listSizeλ��)
    }
    this->listSize++;
}

// push_back��ʵ��
template<class T>
void _charter6_chainListWithIteratorExtend<T>::push_back(const T& theElement)
{
    // ����1��ָ��NULL���½ڵ��ָ��
    _charter6_chainNode<T>* newNode = new _charter6_chainNode<T>(theElement, NULL);
    if (this->firstNode == NULL) // ͷ�ڵ㲻����˵���ǿյ�����,ͷβ��ͬ��newNodeһ��
        this->firstNode = lastNode = newNode;
    else
    {  // ��Ϊ������
        lastNode->next = newNode;// lastNode�󶨵���һ�ڵ�ָ��ָ�����
        lastNode = newNode; // lastNode����
    }
    this->listSize++;
}
