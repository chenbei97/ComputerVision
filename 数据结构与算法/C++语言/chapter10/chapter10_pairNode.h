#pragma once
#ifndef chapter10_pairNode_
#define chapter10_pairNode_
using namespace std;
template <class K, class V>
struct pairNode
{
    typedef pair<const K, V> pairType; // ʹ�ñ�������pair<const K, V>����
    pairType element; // ��ֵ��pair����
    pairNode<K, V>* next; // �����ָ��

    pairNode(const pairType& thePair) :element(thePair) {}; // element��Ա����
    pairNode(const pairType& thePair, pairNode<K, V>* theNext) // element��next��ͬ����
        :element(thePair) {next = theNext;}
    // element��Աû�н�����ֵ,��element=thePair,����ֱ��������:�����ƹ���
};
#endif chapter10_pairNode_
