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
    pairNode<K, V>* firstNode;  // 字典链表头节点
    int dSize;                 // 字典键值对个数
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
    返回匹配的键值对指针, 如果没有返回NULL,和chainList的indexOf函数相似
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
        currentNode->element.first != theKey) // 不为空且不等于要找的关键字
        currentNode = currentNode->next;
  
    if (currentNode != NULL && currentNode->element.first == theKey)
        return &currentNode->element; // 找到匹配的关键字就返回匹配的键值对地址

    return NULL;
}

template<class K, class V>
void dictionaryChain<K, V>::insert(const pair<const K, V>& thePair)
{
    // 插入键值对,如果key已存在则覆盖它
    pairNode<K, V>* p = firstNode,
        * tp = NULL; // tp记录p的前1个位置

    // 这里要求first是int,double,char这样的类型才可能进行<,>运算
    // 外部测试代码的键需要是double、int(最好)、char等
    while (p != NULL && p->element.first < thePair.first) // p移动到插入位置之前
    {
        tp = p; // tp = p(old)
        p = p->next; // p(old) -> p(new) 
        // tp -> thePair(p) 是最后1次运行的指向,p指向thePair.first的位置
    }

    // 如果p不是NULL说明不是首次插入,且插入位置有匹配,覆写原来的关键字节点
    if (p != NULL && p->element.first == thePair.first)
    {
        p->element.second = thePair.second; // value被覆盖
        return;
    }

    // 如果没有匹配的关键字,说明要创建新节点,新节点的next应当就是现在的p指针指向的地址
    pairNode<K, V>* newNode = new pairNode<K, V>(thePair, p); // 以p指针构建,那么newNode->next=p

    // 如果tp是NULL,因为tp=p,说明oldp还是NULL,是第1个节点,NULL->next其实还是NULL
    // 如果不是说明p是尾部节点,而tp记录了这个p,所以让tp->next=newNode
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
        // 如果tp是NULL,说明oldp是NULL, 然后oldp更新为它指向的下1个newp
        if (tp == NULL) firstNode = p->next;  // 让首节点等于删除的节点p原本指向的下一个即可
        else tp->next = p->next; // oldp->next = p->next,删除的是p,下一个p->next要和前1个连上
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

