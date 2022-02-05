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
    float cutOff;          // ����ȷ���ڵ����ڵ�������
    int levels;            // ��ǰ���ķǿ�������
    int dSize;             // �ֵ�Ԫ�ظ���,Ҳ����N
    int maxLevel;          // �����
    K tailKey;             // �������������Ĺؼ���
    skipNode<K, V>* headerNode;  // ͷ�ڵ�
    skipNode<K, V>* tailNode;    // β�ڵ�
    skipNode<K, V>** last;       // last[i]Ϊ��i����������1���ڵ�

    int level() const;     // ���ڲ��������������
    skipNode<K, V>* search(const K&) const; // ����������󿴵��Ľڵ�
};

template<class K, class V>
skipList<K, V>::skipList(K largeKey, int maxPairs, float prob)
{
   
    cutOff = prob * RAND_MAX;
    maxLevel = (int)ceil(logf((float)maxPairs) / logf(1 / prob)) - 1; // �����
    levels = 0;  // Ŀǰ���ļ���
    dSize = 0;  // ���Ը���
    tailKey = largeKey;  // largeKey�����ֵ��κ����ԵĹؼ��ִ洢��β�ڵ�

    pair<K, V> tailPair;
    tailPair.first = tailKey; // β�ڵ�ؼ���ΪtailKey
    headerNode = new skipNode<K, V>(tailPair, maxLevel + 1); //ͷ�ڵ�洢��next����ΪmaxLevel+1
    tailNode = new skipNode<K, V>(tailPair, 0); // β�ڵ�û��next
    last = new skipNode<K, V> *[maxLevel + 1]; // last�����maxLevel + 1��,last[i]Ϊÿ�����1���ڵ�

    // header points to tail at all levels as lists are empty
    for (int i = 0; i <= maxLevel; i++)
        headerNode->next[i] = tailNode; // ��ͷ�ڵ������nextָ�붼��ָ��β�ڵ�
}

template<class K, class V>
skipList<K, V>::~skipList()
{
    skipNode<K, V>* nextNode;
    while (headerNode != tailNode)
    {
        nextNode = headerNode->next[0]; // ɾ���ڵ�ֻ��Ҫ��0������
        delete headerNode;
        headerNode = nextNode;
    }
    delete tailNode;
    delete[] last;
}

template<class K, class V>
pair<const K, V>* skipList<K, V>::find(const K& theKey) const
{

    if (theKey >= tailKey) // ������ҵĴ���β�ڵ�ؼ���˵��������
        return NULL;  

    skipNode<K, V>* beforeNode = headerNode; // 
    for (int i = levels; i >= 0; i--)// �ȴӼ���ߵ��������,����ÿ��level,9,8,7,...,0
        while (beforeNode->next[i]->data.first < theKey)
            beforeNode = beforeNode->next[i];

    // ����ҵ��ͷ���
    if (beforeNode->next[0]->data.first == theKey)
        return &beforeNode->next[0]->data;

    return NULL;  
}

template<class K, class V>
int skipList<K, V>::level() const
{// ����1��������maxLevel�������
    int lev = 0;
    while (rand() <= cutOff)
        lev++;
    return (lev <= maxLevel) ? lev : maxLevel; // ��������lev���򷵻�macLevel
}

template<class K, class V>
skipNode<K, V>* skipList<K, V>::search(const K& theKey) const
{
    // ��������ÿ���ڵ�����󿴵��Ľڵ�ļ�
    // ���һ�������еļ���
    // ���ؿ��ܰ���theKey�Ľڵ�
   // ʹ�ü��ڿ��ܵĽڵ�ǰ����before node
    skipNode<K, V>* beforeNode = headerNode;
    for (int i = levels; i >= 0; i--)
    {
        while (beforeNode->next[i]->data.first < theKey)
            beforeNode = beforeNode->next[i];
        last[i] = beforeNode;  // ���һ���ڵ�
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

    // ����theKey�Ƿ��Ѿ�����
    skipNode<K, V>* theNode = search(thePair.first);
    if (theNode->data.first == thePair.first)
    {// ��������
        theNode->data.second = thePair.second;
        return;
    }

    // �����ڣ�ȷ���½ڵ�ļ���
    int theLevel = level(); // �½ڵ��ˮƽ
    // ����������Ϊ<=level+1
    if (theLevel > levels)
    {
        theLevel = ++levels;
        last[theLevel] = headerNode;
    }

    // ��ȡ���ڽڵ������½ڵ�
    skipNode<K, V>* newNode = new skipNode<K, V>(thePair, theLevel + 1);
    for (int i = 0; i <= theLevel; i++)
    {// ����һ����
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
    if (theNode->data.first != theKey) //������
        return;

    // ������ɾ������ڵ�
    for (int i = 0; i <= levels &&
        last[i]->next[i] == theNode; i++)
        last[i]->next[i] = theNode->next[i];

    // ���¼���
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
        currentNode = currentNode->next[0]) // ��ӡ����ֻ��Ҫ�ҵ�0������
        out << "("<<currentNode->data.first << ","
        << currentNode->data.second << ")  ";
}

template <class K, class V>
ostream& operator<<<>(ostream& out, const skipList<K, V>& x)
{
    x.output(out); return out;
}
#endif // !chapter10_skipList_
