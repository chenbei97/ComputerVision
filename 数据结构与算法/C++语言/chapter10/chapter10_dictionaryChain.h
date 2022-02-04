#pragma once
#ifndef chapter10_dictionaryChain_
#define chapter10_dictionaryChain_
#include <ostream>
#include "chapter10_dictionary.h"
#include "chapter10_pairNode.h"
using namespace std;
template<class K, class V>
class dictionaryChain : public dictionary<K, V>
{
public:
    dictionaryChain() { firstNode = NULL; dSize = 0; }
    ~dictionaryChain();
    bool empty() const { return dSize == 0; }
    int size() const { return dSize; }
    pair<const K, V>* find(const K&) const;
    void erase(const K&);
    void insert(const pair<const K, V>&);
    void output(ostream& out) const;
    friend ostream& operator<<<> (ostream&, const dictionaryChain<K, V> &);
protected:
    pairNode<K, V>* firstNode;  // �ֵ�����ͷ�ڵ�
    int dSize;                 // �ֵ��ֵ�Ը���
};

template<class K, class V>
dictionaryChain<K, V>::~dictionaryChain()
{
    while (firstNode != NULL)
    {
        pairNode<K, V>* nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template<class K, class V>
pair<const K, V>* dictionaryChain<K, V>::find(const K& theKey) const
{
    /*
    ����ƥ��ļ�ֵ��ָ��, ���û�з���NULL,��chainList��indexOf��������
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
    */
    pairNode<K, V>* currentNode = firstNode;
    while (currentNode != NULL &&
        currentNode->element.first != theKey) // ��Ϊ���Ҳ�����Ҫ�ҵĹؼ���
        currentNode = currentNode->next;
  
    if (currentNode != NULL && currentNode->element.first == theKey)
        return &currentNode->element; // �ҵ�ƥ��Ĺؼ��־ͷ���ƥ��ļ�ֵ�Ե�ַ

    return NULL;
}

template<class K, class V>
void dictionaryChain<K, V>::insert(const pair<const K, V>& thePair)
{
    // �����ֵ��,���key�Ѵ����򸲸���
    pairNode<K, V>* p = firstNode,
        * tp = NULL; // tp��¼p��ǰ1��λ��

    // ����Ҫ��first��int,double,char���������Ͳſ��ܽ���<,>����
    // �ⲿ���Դ���ļ���Ҫ��double��int(���)��char��
    while (p != NULL && p->element.first < thePair.first) // p�ƶ�������λ��֮ǰ
    {
        tp = p; // tp = p(old)
        p = p->next; // p(old) -> p(new) 
        // tp -> thePair(p) �����1�����е�ָ��,pָ��thePair.first��λ��
    }

    // ���p����NULL˵�������״β���,�Ҳ���λ����ƥ��,��дԭ���Ĺؼ��ֽڵ�
    if (p != NULL && p->element.first == thePair.first)
    {
        p->element.second = thePair.second; // value������
        return;
    }

    // ���û��ƥ��Ĺؼ���,˵��Ҫ�����½ڵ�,�½ڵ��nextӦ���������ڵ�pָ��ָ��ĵ�ַ
    pairNode<K, V>* newNode = new pairNode<K, V>(thePair, p); // ��pָ�빹��,��ônewNode->next=p

    // ���tp��NULL,��Ϊtp=p,˵��oldp����NULL,�ǵ�1���ڵ�,NULL->next��ʵ����NULL
    // �������˵��p��β���ڵ�,��tp��¼�����p,������tp->next=newNode
    // tp(oldp) ->newNode(newp)
    if (tp == NULL) firstNode = newNode;
    else tp->next = newNode;

    dSize++;
    return;
}

template<class K, class V>
void dictionaryChain<K, V>::erase(const K& theKey)
{
    pairNode<K, V>* p = firstNode,
        * tp = NULL; 

    while (p != NULL && p->element.first < theKey)
    {
        tp = p;
        p = p->next;
    }

    if (p != NULL && p->element.first == theKey)
    {
        // ���tp��NULL,˵��oldp��NULL, Ȼ��oldp����Ϊ��ָ�����1��newp
        if (tp == NULL) firstNode = p->next;  // ���׽ڵ����ɾ���Ľڵ�pԭ��ָ�����һ������
        else tp->next = p->next; // oldp->next = p->next,ɾ������p,��һ��p->nextҪ��ǰ1������
        delete p;
        dSize--;
    }
}

template<class K, class V>
void dictionaryChain<K, V>::output(ostream& out) const
{
    out << "(key,value) as follows : \n";
    for (pairNode<K, V>* currentNode = firstNode;
        currentNode != NULL;
        currentNode = currentNode->next)
        out << "("<<currentNode->element.first << ","
        << currentNode->element.second << ")  ";
}

template <class K, class V>
ostream& operator<<<>(ostream& out, const dictionaryChain<K, V>& x)
{
    x.output(out); return out;
}

#endif // !chapter10_dictionaryChain_

