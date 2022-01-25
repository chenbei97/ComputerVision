#pragma once
#ifndef chapter6_chainListIterator_binSort_
#define chapter6_chainListIterator_binSort_
#include "myExceptions.h"
#include "chapter5_linearList.h"
#include "chapter6_chainNode.h"
#include <ostream>
#include <sstream>
template<class T>
class _chapter6_chainBinSort : public _chapter5_linearList<T>
{
public:
    _chapter6_chainBinSort(int initialCapacity = 10);
    _chapter6_chainBinSort(const _chapter6_chainBinSort<T>&);
    ~_chapter6_chainBinSort();

    bool empty() const { return listSize == 0; }
    int size() const { return listSize; }
    T& get(int theIndex) const;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    void output(ostream& out) const;
    void binSort(int range,bool log =false);
    void binSort(int range, int(*value)(T& x));
protected:
    void checkIndex(int theIndex) const;
    _chapter6_chainNode<T>* firstNode;
    int listSize;        
};
template<class T>

_chapter6_chainBinSort<T>::_chapter6_chainBinSort(int initialCapacity)
{
    if (initialCapacity < 1)
    {
        ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }
    firstNode = NULL;
    listSize = 0;
}

template<class T>
_chapter6_chainBinSort<T>::_chapter6_chainBinSort(const _chapter6_chainBinSort<T>& theList)
{
    listSize = theList.listSize;
    if (listSize == 0)
    {
        firstNode = NULL;
        return;
    }
   
    _chapter6_chainNode<T>* sourceNode = theList.firstNode;
    firstNode = new _chapter6_chainNode<T>(sourceNode->element);
    sourceNode = sourceNode->next;
    _chapter6_chainNode<T>* targetNode = firstNode;
    while (sourceNode != NULL)
    {
        targetNode->next = new _chapter6_chainNode<T>(sourceNode->element);
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
    }
    targetNode->next = NULL; 
}

template<class T>
_chapter6_chainBinSort<T>::~_chapter6_chainBinSort()
{
    _chapter6_chainNode<T>* nextNode;
    while (firstNode != NULL)
    {
        nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template<class T>
void _chapter6_chainBinSort<T>::checkIndex(int theIndex) const
{
    if (theIndex < 0 || theIndex >= listSize)
    {
        ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }

}

template<class T>
T& _chapter6_chainBinSort<T>::get(int theIndex) const
{
    checkIndex(theIndex);
    _chapter6_chainNode<T>* currentNode = firstNode;
    for (int i = 0; i < theIndex; i++)
        currentNode = currentNode->next;
    return currentNode->element;
}

template<class T>
int _chapter6_chainBinSort<T>::indexOf(const T& theElement) const
{
    _chapter6_chainNode<T>* currentNode = firstNode;
    int index = 0;  
    while (currentNode != NULL &&
        currentNode->element != theElement)
    {
        currentNode = currentNode->next;
        index++;
    }
    if (currentNode == NULL)
        return -1;
    else
        return index;
}

template<class T>
void _chapter6_chainBinSort<T>::erase(int theIndex)
{
    checkIndex(theIndex);
    _chapter6_chainNode<T>* deleteNode;
    if (theIndex == 0)
    {
        deleteNode = firstNode;
        firstNode = firstNode->next;
    }
    else
    { 
        _chapter6_chainNode<T>* p = firstNode;
        for (int i = 0; i < theIndex - 1; i++)
            p = p->next;
        deleteNode = p->next;
        p->next = p->next->next; 
    }
    listSize--;
    delete deleteNode;
}

template<class T>
void _chapter6_chainBinSort<T>::insert(int theIndex, const T& theElement)
{
    if (theIndex < 0 || theIndex > listSize)
    {
        ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }
    // theChain.insert(0, s);  �����Ԫ��s����stu����
    if (theIndex == 0) 
    {
        firstNode = new _chapter6_chainNode<T>(theElement, firstNode);
        // std::cout << firstNode->element<<std::endl; //��ӡ�˲������Ϣ
        // ����ʹ��printf,��ΪT������stu����,�������Ѿ�������<<�����
    }
    else
    {  
        _chapter6_chainNode<T>* p = firstNode;
        for (int i = 0; i < theIndex - 1; i++)
            p = p->next;
        p->next = new _chapter6_chainNode<T>(theElement, p->next);
    }
    listSize++;
}

template<class T>
void _chapter6_chainBinSort<T>::output(ostream& out) const
{
    for (_chapter6_chainNode<T>* currentNode = firstNode;
        currentNode != NULL;
        currentNode = currentNode->next)
        out << currentNode->element << "  ";
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const _chapter6_chainBinSort<T>& x)
{
    x.output(out); return out;
}

template<class T>
void _chapter6_chainBinSort<T>::binSort(int range,bool log)
{
    // bottom,top�ǽڵ��������͵�ָ��,ÿ��Ԫ��ָ��ͬ����
    // bottomָ�������׽ڵ�(ͬ�ֶε�1����),topָ��β�ڵ�(ͬ�ֶ����1����)
    // �����y������ָ����1�ֶε�bottom,Ȼ��������next������һ�ֶε�top,����൱�ڰ��������Ӵ�������
    // ���yӦ����top[10],����10�ֵ����1��ѧ��,y�Ǹ�ճ�ϼ��𵽴�������
    // ����y���û���ñ���y->next��ΪҰָ�뻹Ҫָ��NULL,y������top[10],delete top����Ȼɾ����y
    cout << "-------" << endl;
    _chapter6_chainNode<T>** bottom, ** top; // ָ��ָ�����鱾���ָ��
    bottom = new _chapter6_chainNode<T>*[range + 1]; // ���Կ���_charter6_chainNode<T> *bottom[range+1];
    top = new _chapter6_chainNode<T>*[range + 1]; // Ϊ��Ҫnew?��Ϊֻ����ʱ������߻�ɾ��
    for (int b = 0; b <= range; b++) // ÿ��������λ�������������Ѿ���ʼ��ΪNULL
        bottom[b] = NULL; 
    // ���Լ�����,��������β�ڵ�ָ��NULL
    char name[] = { 'a','b','c','d','e',   'f','g','h','i','j',   'k','l','m','n','o',    'p','q','r','s','t',  'u' };
    int idx = 0;
    if (log == true)
        cout << "��ʼ��ѧ�����벻ͬ�����ӷ��ࣺ" << endl;
    for (; firstNode != NULL; firstNode = firstNode->next) 
    { // 20��ѧ����ʼ����
        // ����firstNode->element�Ǹ�stu����
        int theBin = firstNode->element; // ������Ϊ������int(),���԰�stu����ǿתΪint����,���ص���ʵ��stu�ķ���
        // printf("bin = %d", theBin); //10,9,8,...,0  �õ�ÿ��ѧ���ķ���
        if (bottom[theBin] == NULL) // �������û���ù�(�ս���ѭ��ʱ��ִ��if���ڲ����)
        {
            bottom[theBin] = top[theBin] = firstNode; // �����ӵĿ�ͷ����theBin�ֶγ��ֵĵ�1��ѧ��firstNode
            // �·�������˵��bottom[theBin]��firstNode->next�˿̾���1������
            // bottom[theBin]->next����ָ����1��ѧ��,�ر���������ͷֵ�ָ��ΪNULL,��Ϊ�ⲿ���Գ�����0��ѧ�����������
            if (log == true)
                cout << "name = "<<name[idx]<<" box["<<theBin<<"] not use  bottom[" << theBin << "][0] = "<<firstNode <<
                "\n\tbottom[" << theBin << "]->next = "<< bottom[theBin]->next<<" firstNode->next = "<<firstNode->next<<endl;
        }
        else
        {
            // firstNode��bin�ֶεĵ�2��ѧ��(����еĻ�),top[theBin]��bin�ֶεĵ�1��ѧ��
            if (log == true)
                cout << "name = " << name[idx] << " box["<<theBin<<"] is use =  bottm["<<theBin<<"][1] = " << firstNode << endl;
            
            // top[theBin]����1��ѧ�� cout << top[" << theBin << "] = " << top[theBin] << endl; 
            top[theBin]->next = firstNode; // ��1��ѧ��ָ���2��ѧ��,ͬһ�ֶε�ѧ�����д���
            top[theBin] = firstNode;// ����top[theBin]�ӵ�1��ѧ����Ϊ���ڵ�2��ѧ��
            // �������ֶλ��кܶ�ѧ��,��˲���top[theBin]���ǵ��ڸ÷ֶε����һ��ѧ��
        }
        idx++;
    }
    // ��������������������ÿ�����Ӷ�������ÿ��ѧ��,����Ҫ�������ߵ��ó���
    _chapter6_chainNode<T>* y = NULL; // 1��ָ��NULL��ָ��
    if (log == true)
        cout << "��ʼ��ѧ���ӵͷֵ��߷���������ȡ����" << endl;
    int theBin = 0;
    for (theBin = 0; theBin <= range; theBin++) // ��������С�������ÿ����������
        if (bottom[theBin] != NULL) // �������û���ù�����1������,�ù��ĵ�ַ������NULL
        { 
            if (y == NULL) // ��1���ù�����ͷ������ӻ�ִ��if���,��ֻ��ִ��1��
            {
                if (log == true)
                {
                    // �·����firstNodeΪNULL,������Ϊ����ѭ��firstNode=NULLʱ����
                    // bottom[theBin]->next��NULL,������Ϊ�ⲿ���Գ���0��ѧ����β�ڵ��Ψһһ��,����һ������NULL
                    // ����Ϊ�˲����Ƿ�bottom[theBin]�Ѿ��Զ���������1��ѧ��(����еĻ�),�ⲿ������������1��0��ѧ��u
                    // ��ʱbottom[theBin]->next�����ǿ�,���ǵ�2��0��ѧ���ĵ�ַ,�������1��������NULL��
                    cout  << "\tbottom["<< theBin<<"]->next = " << bottom[theBin]->next
                    << "\n\tbottom["<<theBin<<"]->next->next = " << bottom[theBin]->next->next << endl;
                    cout << "bottom["<< theBin<<"] = " << bottom[theBin] << endl;
                }
                firstNode = bottom[theBin]; // ���׽ڵ���ڷ�����͵��Ǹ����ӵĵ�һ��ѧ����ַ(β�ڵ�)
                if (log == true)
                    cout << "\tfirstNode = " << firstNode << endl;
            }
            else
            {     
                if (log == true)
                {
                    // �·�bottom[theBin]���ϱ�ÿ������box not use �ĵ�ַ��Ӧ,����ÿ���������ӵĵ�1��ѧ��
                    // ��next����һ��ѧ������Ϣ,��next����ͬ�ֶ�(��Ϊ���Գ����г���10��ֻ��1�����������ζ���2��)
                    cout <<"\tbottom[" << theBin << "]->next = " << bottom[theBin]->next
                    << "\n\tbottom[" << theBin << "]->next->next = " << bottom[theBin]->next->next << endl;
                }
                y->next = bottom[theBin];// ��ͷ������ҵ��˾Ͳ�����ִ��if,������yָ��ǰ���ӵĵ�1��ѧ��
                if (log == true)
                {
                    cout << "top[" << theBin - 1 << "]  = " << y << endl;
                    cout << "top[" << theBin - 1 << "]->next  = " << y->next << " = bottom["<<theBin<<"] = "
                         << bottom[theBin] << endl;//��ǰ�ֶεĵ�1��Ԫ��
                }
            }
            // ע��ִ��˳��,��ִ��y->next = bottom[theBin]��ִ��y=top[theBin](��ִ��)
            y = top[theBin]; // top[theBin]�Ѿ�ָ��ͬ�ֶε����1��ѧ��,��y������
            /*
                1. theBin=0��1��ѭ��, if��firstNodeָ����0�ֵĵ�1��ѧ��(ջ��)
                    Ȼ�����y=top[theBin],y����0��ѧ��2;����ѭ��
                2.theBin=1��2��ѭ��, ִ��else,��y��nextָ��1�ֵĵ�1��ѧ��;Ȼ��y=top[theBin],y��0�ֱ��1��ѧ��2;����ѭ��
                3.�Դ�����,���Կ���bottom��top���ô������ڴ洢ÿ�����ӵ�ͷ�ڵ��β�ڵ�ĵ�ַ,��11��ֵ
                   y������ʱ��ճ�ϼ����Ϸֶ����1�����·ֶε�1��������,y=>NULL=>top[0]=>bottom[0]=>top[1]=>bottom[1]=>...=>top[9]
                4.theBin=10��11��ѭ��,y=top[9],ִ��else,y->next=bottom[10](���1���ֶ�),Ȼ��y=top[10]forѭ�����׽���
            */
        }
    theBin = 10; // �ָ���10, ���������������theBin = 11��
    if (log == true)
        cout << "top[" << theBin << "] = " << top[theBin] << endl; // ע�⵽top[10]��bottom[10]�����Ϊֻ��1��Ԫ��
    // ����for������y = top[10]
    if (y != NULL)
        y->next = NULL; // �ÿձ����ΪҰָ��

    delete[] bottom;
    delete[] top; // y = top[10] delete top <=> delete y
}

// Ψһ�Ĳ�ͬ�ǰ�int theBin = firstNode->element; �����int theBin = value(firstNode->element);
template<class T>
void _chapter6_chainBinSort<T>::binSort(int range, int(*value)(T& x))
{
    _chapter6_chainNode<T>** bottom, ** top;
    bottom = new _chapter6_chainNode<T>*[range + 1];
    top = new _chapter6_chainNode<T>*[range + 1];
    for (int b = 0; b <= range; b++)
        bottom[b] = NULL;

    for (; firstNode != NULL; firstNode = firstNode->next)
    {
        // ��ǰ: int theBin = firstNode->element; 
        cout << "value = " <<value << endl;
        int theBin = value(firstNode->element); // Ψһ�Ĳ�ͬ����value��ߵ�
        if (bottom[theBin] == NULL) 
            bottom[theBin] = top[theBin] = firstNode;
        else
        {
            top[theBin]->next = firstNode;
            top[theBin] = firstNode;
        }
    }

    _chapter6_chainNode<T>* y = NULL;
    for (int theBin = 0; theBin <= range; theBin++)
        if (bottom[theBin] != NULL)
        {
            if (y == NULL) 
                firstNode = bottom[theBin];
            else 
                y->next = bottom[theBin];
            y = top[theBin];
        }
    if (y != NULL)
        y->next = NULL;

    delete[] bottom;
    delete[] top;
}
#endif chapter6_chainListIterator_binSort_
