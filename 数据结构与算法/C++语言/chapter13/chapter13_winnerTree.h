#pragma once
#ifndef chapter13_winnerTree_
#define chapter13_winnerTree_
#include <iostream>
#include "chapter1_illegalParameterValue.h"
#include "chapter13_abstractWinnerTree.h"
using namespace std;
template<class T> 
class winnerTree : public abstractWinnerTree<T>
{
public:
    winnerTree(T* thePlayer, int theNumberOfPlayers);
    ~winnerTree() { delete[] tree; }
    void initialize(T*, int);
    int winner() const;
    int winner(int i) const;
    void replay(int thePlayer);
    void output(ostream& out) const;
    friend ostream& operator<<<>(ostream&, const winnerTree<T>&);
private:
    /*
        参赛选手分数：player,player[i]为第i个参赛选手的分数,1≤i≤numberOfPlayers
        s：最底层最左端的内部节点(最低级别的赢者)编号,它应当等于2^|log2(n-1)|,不一定是n-1,
        n-s：最底层内部节点的个数,既然最底层最左的编号是s,在s之后都是最底层的内部节点,故共n-s个
        lowExt：最底层的外部节点个数,外部节点是最底层内部节点的子节点,所以个数为2(n-s)
        tree：存储赢者树,tree[p]为外部节点player[i]的父节点,编号p与player中选手的索引存在关系
              { (i+offset)/2  i≤lowExt
        p = {
              { (i-lowExt+n-1)/2 i>lowExt
        offset：2 * s - 1 = 2^log(n-1) - 1
    */
    int lowExt;           // 为最底层内部节点个数n-s的两倍,即2(n-s)
    int offset;          
    int* tree;            
    int numberOfPlayers;
    T* player;           
    void play(int p, int leftChild, int rightChild);
};
template<class T>
int winnerTree<T>::winner() const {
        return tree[1]; // 返回真正的赢者
}
template<class T>
int winnerTree<T>::winner(int i) const {
    // tree存储的是每个节点的赢者,tree[1]为最顶层的赢者,tree[numberOfPlayers-1]为最底层的赢者
    // i的范围是1,2,...numberOfPlayers-1(下标0弃用)
    return (i < numberOfPlayers) ? tree[i] : 0; // 返回指定名次的赢者
}
template<class T>
winnerTree<T>::winnerTree(T* thePlayer, int theNumberOfPlayers)
{
    tree = NULL;
    initialize(thePlayer, theNumberOfPlayers);//构造函数调用的是初始化函数
}
template<class T>
void winnerTree<T>::initialize(T* thePlayer, int theNumberOfPlayers) {
    int n = theNumberOfPlayers;
    if (n < 2)
        throw illegalParameterValue("must have at least 2 players");

    player = thePlayer;
    numberOfPlayers = n;
    delete[] tree;
    tree = new int[n];

    // s = 2^log (n-1)
    int i, s;
    for (s = 1; 2 * s <= n - 1; s += s);
    lowExt = 2 * (n - s);
    offset = 2 * s - 1;

    // 为最低级别的外部节点设置
    for (i = 2; i <= lowExt; i += 2)
        play((offset + i) / 2, i - 1, i);

    // 处理剩余的外部节点
    if (n % 2 == 1)
    {// 奇数n的特例，让内部和外部节点比赛
        play(n / 2, tree[n - 1], lowExt + 1);
        i = lowExt + 3;
    }
    else i = lowExt + 2;

    // i是剩下的最左边的外部节点
    for (; i <= n; i += 2)
        play((i - lowExt + n - 1) / 2, i - 1, i);
}
template<class T>
void winnerTree<T>::replay(int thePlayer) {
    int n = numberOfPlayers;
    if (thePlayer <= 0 || thePlayer > n)
        throw illegalParameterValue("Player index is illegal");

    int matchNode,       // node where next match is to be played
        leftChild,       // left child of matchNode
        rightChild;      // right child of matchNode

    // find first match node and its children
    if (thePlayer <= lowExt)
    {// begin at lowest level
        matchNode = (offset + thePlayer) / 2;
        leftChild = 2 * matchNode - offset;
        rightChild = leftChild + 1;
    }
    else
    {
        matchNode = (thePlayer - lowExt + n - 1) / 2;
        if (2 * matchNode == n - 1)
        {
            leftChild = tree[2 * matchNode];
            rightChild = thePlayer;
        }
        else
        {
            leftChild = 2 * matchNode - n + 1 + lowExt;
            rightChild = leftChild + 1;
        }
    }

    tree[matchNode] = (player[leftChild] <= player[rightChild])
        ? leftChild : rightChild;

    // special case for second match
    if (matchNode == n - 1 && n % 2 == 1)
    {
        matchNode /= 2;   // move to parent
        tree[matchNode] = (player[tree[n - 1]] <=
            player[lowExt + 1]) ?
            tree[n - 1] : lowExt + 1;
    }

    // play remaining matches
    matchNode /= 2;  // move to parent
    for (; matchNode >= 1; matchNode /= 2)
        tree[matchNode] = (player[tree[2 * matchNode]] <=
            player[tree[2 * matchNode + 1]]) ?
        tree[2 * matchNode] : tree[2 * matchNode + 1];
}
template<class T>
void winnerTree<T>::play(int p, int leftChild, int rightChild) {
    // 比赛从tree[p]开始
    tree[p] = (player[leftChild] <= player[rightChild]) ?
        leftChild : rightChild;

    // 如果找到合适的孩子，可能会有更多匹配
    while (p % 2 == 1 && p > 1)
    {
        tree[p / 2] = (player[tree[p - 1]] <= player[tree[p]]) ? // 左孩子
            tree[p - 1] : tree[p];
        p /= 2;  // 回到父节点
    }
}
template<class T>
void winnerTree<T>::output(ostream&out)const {
    out << "number of players  = " << numberOfPlayers
        << " lowExt = " << lowExt
        << " offset = " << offset << endl;
    out << "complete winner tree pointers are" << endl;
    for (int i = 1; i < numberOfPlayers; i++)
        out << tree[i] << ' ';
    out << endl;
}
template<class T>
ostream& operator<<<> (ostream& out, const winnerTree<T>& x) {
    x.output(out);
    return out;
}
#endif // !chapter13_winnerTree_
