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
        ����ѡ�ַ�����player,player[i]Ϊ��i������ѡ�ֵķ���,1��i��numberOfPlayers
        s����ײ�����˵��ڲ��ڵ�(��ͼ����Ӯ��)���,��Ӧ������2^|log2(n-1)|,��һ����n-1,
        n-s����ײ��ڲ��ڵ�ĸ���,��Ȼ��ײ�����ı����s,��s֮������ײ���ڲ��ڵ�,�ʹ�n-s��
        lowExt����ײ���ⲿ�ڵ����,�ⲿ�ڵ�����ײ��ڲ��ڵ���ӽڵ�,���Ը���Ϊ2(n-s)
        tree���洢Ӯ����,tree[p]Ϊ�ⲿ�ڵ�player[i]�ĸ��ڵ�,���p��player��ѡ�ֵ��������ڹ�ϵ
              { (i+offset)/2  i��lowExt
        p = {
              { (i-lowExt+n-1)/2 i>lowExt
        offset��2 * s - 1 = 2^log(n-1) - 1
    */
    int lowExt;           // Ϊ��ײ��ڲ��ڵ����n-s������,��2(n-s)
    int offset;          
    int* tree;            
    int numberOfPlayers;
    T* player;           
    void play(int p, int leftChild, int rightChild);
};
template<class T>
int winnerTree<T>::winner() const {
        return tree[1]; // ����������Ӯ��
}
template<class T>
int winnerTree<T>::winner(int i) const {
    // tree�洢����ÿ���ڵ��Ӯ��,tree[1]Ϊ����Ӯ��,tree[numberOfPlayers-1]Ϊ��ײ��Ӯ��
    // i�ķ�Χ��1,2,...numberOfPlayers-1(�±�0����)
    return (i < numberOfPlayers) ? tree[i] : 0; // ����ָ�����ε�Ӯ��
}
template<class T>
winnerTree<T>::winnerTree(T* thePlayer, int theNumberOfPlayers)
{
    tree = NULL;
    initialize(thePlayer, theNumberOfPlayers);//���캯�����õ��ǳ�ʼ������
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

    // Ϊ��ͼ�����ⲿ�ڵ�����
    for (i = 2; i <= lowExt; i += 2)
        play((offset + i) / 2, i - 1, i);

    // ����ʣ����ⲿ�ڵ�
    if (n % 2 == 1)
    {// ����n�����������ڲ����ⲿ�ڵ����
        play(n / 2, tree[n - 1], lowExt + 1);
        i = lowExt + 3;
    }
    else i = lowExt + 2;

    // i��ʣ�µ�����ߵ��ⲿ�ڵ�
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
    // ������tree[p]��ʼ
    tree[p] = (player[leftChild] <= player[rightChild]) ?
        leftChild : rightChild;

    // ����ҵ����ʵĺ��ӣ����ܻ��и���ƥ��
    while (p % 2 == 1 && p > 1)
    {
        tree[p / 2] = (player[tree[p - 1]] <= player[tree[p]]) ? // ����
            tree[p - 1] : tree[p];
        p /= 2;  // �ص����ڵ�
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
