#pragma once
#ifndef chapter10_skipList_
#define chapter10_skipList_
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include "chapter10_skipNode.h"
#include "chapter10_dictionary.h"
#include "chapter1_illegalParameterValue.h"
using namespace std;
template<class K, class V>
class skipList : public dictionary<K,V>
{
public:
    skipList(K, int maxPairs = 10000, float prob = 0.5);
    ~skipList();

    bool empty() const { return dSize == 0; }
    int size() const { return dSize; }
    pair<const K, V>* find(const K&) const;
    void erase(const K&);
    void insert(const pair<const K, V>&);
    void output(ostream& out) const;
    friend ostream& operator<<<>(ostream&, const skipList<const K, V>&);
protected:
    float cutOff;          // 用来确定节点属于的链表级数
    int levels;            // 当前最大的非空链表级数
    int dSize;             // 字典元素个数,也就是N
    int maxLevel;          // 最大级数
    K tailKey;             // 有序链表中最大的关键字
    skipNode<K, V>* headerNode;  // 头节点
    skipNode<K, V>* tailNode;    // 尾节点
    skipNode<K, V>** last;       // last[i]为第i级链表的最后1个节点

    int level() const;     // 用于产生级数的随机数
    skipNode<K, V>* search(const K&) const; // 搜索保存最后看到的节点
};

template<class K, class V>
skipList<K, V>::skipList(K largeKey, int maxPairs, float prob)
{
   
    cutOff = prob * RAND_MAX;
    maxLevel = (int)ceil(logf((float)maxPairs) / logf(1 / prob)) - 1; // 最大级数
    levels = 0;  // 目前最大的级数
    dSize = 0;  // 数对个数
    tailKey = largeKey;  // largeKey大于字典任何数对的关键字存储在尾节点

    pair<K, V> tailPair;
    tailPair.first = tailKey; // 尾节点关键字为tailKey
    headerNode = new skipNode<K, V>(tailPair, maxLevel + 1); //头节点存储的next个数为maxLevel+1
    tailNode = new skipNode<K, V>(tailPair, 0); // 尾节点没有next
    last = new skipNode<K, V> *[maxLevel + 1]; // last最多有maxLevel + 1层,last[i]为每层最后1个节点

    // header points to tail at all levels as lists are empty
    for (int i = 0; i <= maxLevel; i++)
        headerNode->next[i] = tailNode; // 让头节点的所有next指针都先指向尾节点
}

template<class K, class V>
skipList<K, V>::~skipList()
{
    skipNode<K, V>* nextNode;
    while (headerNode != tailNode)
    {
        nextNode = headerNode->next[0]; // 删除节点只需要找0级链表
        delete headerNode;
        headerNode = nextNode;
    }
    delete tailNode;
    delete[] last;
}

template<class K, class V>
pair<const K, V>* skipList<K, V>::find(const K& theKey) const
{

    if (theKey >= tailKey) // 如果查找的大于尾节点关键字说明不存在
        return NULL;  

    skipNode<K, V>* beforeNode = headerNode; // 
    for (int i = levels; i >= 0; i--)// 先从级别高的链表查找,遍历每个level,9,8,7,...,0
        while (beforeNode->next[i]->data.first < theKey)
            beforeNode = beforeNode->next[i];

    // 如果找到就返回
    if (beforeNode->next[0]->data.first == theKey)
        return &beforeNode->next[0]->data;

    return NULL;  
}

template<class K, class V>
int skipList<K, V>::level() const
{// 返回1个不大于maxLevel的随机数
    int lev = 0;
    while (rand() <= cutOff)
        lev++;
    return (lev <= maxLevel) ? lev : maxLevel; // 成立返回lev否则返回macLevel
}

template<class K, class V>
skipNode<K, V>* skipList<K, V>::search(const K& theKey) const
{
    // 搜索保存每个节点上最后看到的节点的键
    // 最后一个数组中的级别
    // 返回可能包含theKey的节点
   // 使用键在可能的节点前放置before node
    skipNode<K, V>* beforeNode = headerNode;
    for (int i = levels; i >= 0; i--)
    {
        while (beforeNode->next[i]->data.first < theKey)
            beforeNode = beforeNode->next[i];
        last[i] = beforeNode;  // 最后一级节点
    }
    return beforeNode->next[0];
}

template<class K, class V>
void skipList<K, V>::insert(const pair<const K, V>& thePair)
{
    if (thePair.first >= tailKey) 
    {
        ostringstream s;
        s << "Key = " << thePair.first << " Must be < " << tailKey;
        throw illegalParameterValue(s.str());
    }

    // 看看theKey是否已经存在
    skipNode<K, V>* theNode = search(thePair.first);
    if (theNode->data.first == thePair.first)
    {// 更新数据
        theNode->data.second = thePair.second;
        return;
    }

    // 不存在，确定新节点的级别
    int theLevel = level(); // 新节点的水平
    // 将级别设置为<=level+1
    if (theLevel > levels)
    {
        theLevel = ++levels;
        last[theLevel] = headerNode;
    }

    // 获取并在节点后插入新节点
    skipNode<K, V>* newNode = new skipNode<K, V>(thePair, theLevel + 1);
    for (int i = 0; i <= theLevel; i++)
    {// 插入一级链
        newNode->next[i] = last[i]->next[i];
        last[i]->next[i] = newNode;
    }

    dSize++;
    return;
}

template<class K, class V>
void skipList<K, V>::erase(const K& theKey)
{
    if (theKey >= tailKey) 
        return;
    skipNode<K, V>* theNode = search(theKey);
    if (theNode->data.first != theKey) //不存在
        return;

    // 从跳表删除这个节点
    for (int i = 0; i <= levels &&
        last[i]->next[i] == theNode; i++)
        last[i]->next[i] = theNode->next[i];

    // 更新级别
    while (levels > 0 && headerNode->next[levels] == tailNode)
        levels--;

    delete theNode;
    dSize--;
}

template<class K, class V>
void skipList<K, V>::output(ostream& out) const
{
    for (skipNode<K, V>* currentNode = headerNode->next[0];
        currentNode != tailNode;
        currentNode = currentNode->next[0]) // 打印链表只需要找到0级即可
        out << "("<<currentNode->data.first << ","
        << currentNode->data.second << ")  ";
}

template <class K, class V>
ostream& operator<<<>(ostream& out, const skipList<K, V>& x)
{
    x.output(out); return out;
}
#endif // !chapter10_skipList_
