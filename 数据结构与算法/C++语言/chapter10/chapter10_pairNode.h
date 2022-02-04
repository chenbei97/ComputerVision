#pragma once
#ifndef chapter10_pairNode_
#define chapter10_pairNode_
using namespace std;
template <class K, class V>
struct pairNode
{
    typedef pair<const K, V> pairType; // 使用别名代替pair<const K, V>对象
    pairType element; // 键值对pair对象
    pairNode<K, V>* next; // 自身的指针

    pairNode(const pairType& thePair) :element(thePair) {}; // element成员构造
    pairNode(const pairType& thePair, pairNode<K, V>* theNext) // element和next共同构造
        :element(thePair) {next = theNext;}
    // element成员没有借助赋值,即element=thePair,而是直接作用域:来复制构造
};
#endif chapter10_pairNode_
