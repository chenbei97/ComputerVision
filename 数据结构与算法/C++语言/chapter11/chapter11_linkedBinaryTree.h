#pragma once
#ifndef chapter11_linkedBinaryTree_
#define chapter11_linkedBinaryTree_
using namespace std;
#include <iostream>
#include <string>
#include "chapter11_abstractBinaryTree.h"
#include "chapter11_binaryTreeNode.h"
#include "chapter11_booster.h"
#include "chapter9_arrayQueueSimple.h"
#include "chapter11_emptyTree.h"
template<class E>
class linkedBinaryTree : public abstractBinaryTree<binaryTreeNode<E> >
{
public:
    linkedBinaryTree() { root = NULL; treeSize = 0; }
    ~linkedBinaryTree() { erase(); }
    bool empty() const { return treeSize == 0; }
    int size() const { return treeSize; }
    static void printTestStatic() { cout << "the testStatic is " << testStatic<<"\n"; }
    int height() const { return height(root); }// �ⲿ���ʵ������ڲ���height����

    void preOrder(void(*theVisit)(binaryTreeNode<E>*));// ����ǰ�����
    void inOrder(void(*theVisit)(binaryTreeNode<E>*));// �����������
    void erase();
    void postOrder(void(*theVisit)(binaryTreeNode<E>*));// ���к������
    void levelOrder(void(*theVisit)(binaryTreeNode<E>*)); // ���в�α���

    void makeTree(const E& element,linkedBinaryTree<E>&left, linkedBinaryTree<E>&right);

    // ����ⲿû���ṩvisit����,Ĭ�Ͽ���ʹ��output�����
    void preOrderOutput() { preOrder(output); cout << endl; }
    void inOrderOutput() { inOrder(output); cout << endl; }
    void postOrderOutput() { postOrder(output); cout << endl; }
    void levelOrderOutput() { levelOrder(output); cout << endl; }


    // ��������,��ʱ�����в��Ժ�˵��
    E* rootElement() const;
    linkedBinaryTree<E>& removeLeftSubtree();
    linkedBinaryTree<E>& removeRightSubtree();
protected:
    binaryTreeNode<E>* root; // ���ڵ�ָ��
    int treeSize; // �ڵ����
    static int testStatic ; // ���ڲ���static������
    /*
    ָ������ָ��,����ֵ����Ϊvoid,��������ΪbinaryTreeNode *
    ����Ϊ��̬ʱ��Ϊ��ָ�����ڶ�������,�����Ƕ���������,Ҳ����˵�������ļ����Ըı������ĳ�Ա����
    ����ֵ��ú���ָ��Ӧ�ÿ��Գ�������,���������ֱ�����ʽ�����Ե���visit����,����ͬһ��visit�汾
    */
    static void (*visit)(binaryTreeNode<E>*); 
    
    static void pre_order(binaryTreeNode<E>* t); // ˽��ǰ�����
    static void in_order(binaryTreeNode<E>* t); // ˽���������
    static void post_order(binaryTreeNode<E>* t); // ˽�к������
    static void dispose(binaryTreeNode<E>* t); // �ɴ��빫�к��������Ϊvisitɾ���ڵ�

    static void output(binaryTreeNode<E>* t);
    static int height(binaryTreeNode<E>* t);

    // ���������ͱ���
    static int count;         // used to count nodes in a subtree
    static void addToCount(binaryTreeNode<E>* t)
    {
        count++;
    }
    static void countNodes(binaryTreeNode<E>* t)
    {
        visit = addToCount;
        count = 0;
        preOrder(t);
    }
    
};
// ���ڱ������ڲ��Ĵ���,��������ʾ����
// ���Ӧ������visit����Ĳ���������visitһ��
// ������Ҫʹ��string,������string����ʽ�������򱨴�
// ԭ���߻�������booster��pair<const int, char> >������,����ע�͵���ʱ�ò���
void (*linkedBinaryTree<int>::visit)(binaryTreeNode<int>*);
void (*linkedBinaryTree<string>::visit)(binaryTreeNode<string>*);
void (*linkedBinaryTree<char>::visit)(binaryTreeNode<char>*);
void (*linkedBinaryTree<double>::visit)(binaryTreeNode<double>*);
//void (*linkedBinaryTree<booster>::visit)(binaryTreeNode<booster>*);
//void (*linkedBinaryTree<pair<int, int> >::visit)(binaryTreeNode<pair<int, int> >*);
//void (*linkedBinaryTree<pair<const int, char> >::visit)(binaryTreeNode<pair<const int, char> >*);
//void (*linkedBinaryTree<pair<const int, int> >::visit)(binaryTreeNode<pair<const int, int> >*);

template<class E>
void linkedBinaryTree<E>::preOrder(void(*theVisit)(binaryTreeNode<E>*))
{
    // ����ǰ�����,�ⲿ��theVisit��visit������ֵ
    visit = theVisit; pre_order(root); // ����˽��ǰ�����
}
template<class E>
void linkedBinaryTree<E>::inOrder(void(*theVisit)(binaryTreeNode<E>*))
{
    // �����������,�ⲿ��theVisit��visit������ֵ
    visit = theVisit; in_order(root); // ����˽���������
}
template<class E>
void linkedBinaryTree<E>::postOrder(void(*theVisit)(binaryTreeNode<E>*))
{
    // ���к������,�ⲿ��theVisit��visit������ֵ
    visit = theVisit; post_order(root); // ����˽�к������
}
template <class E>
void linkedBinaryTree<E>::levelOrder(void(*theVisit)(binaryTreeNode<E>*))
{
    arrayQueueSimple<binaryTreeNode<E>*> q;
    binaryTreeNode<E>* t = root;
    while (t != NULL)
    {
        theVisit(t);  // û��ʹ��visit,ֱ���ô��ݵĺ���
        if (t->leftChild != NULL)
            q.push(t->leftChild);
        if (t->rightChild != NULL)
            q.push(t->rightChild);

        try { t = q.front(); }
        catch (queueEmpty) { return; }
        q.pop();
    }
}

template<class E>
void linkedBinaryTree<E>::pre_order(binaryTreeNode<E>* t)
{
    // ˽��ǰ�����
    if (t != NULL)
    {
        linkedBinaryTree<E>::visit(t);
        pre_order(t->leftChild);
        pre_order(t->rightChild);
    }
}
template<class E>
void linkedBinaryTree<E>::in_order(binaryTreeNode<E>* t)
{
    // ˽���������
    if (t != NULL)
    {
        in_order(t->leftChild);
        linkedBinaryTree<E>::visit(t);
        in_order(t->rightChild);
    }
}
template<class E>
void linkedBinaryTree<E>::post_order(binaryTreeNode<E>* t)
{
    // ˽�к������
    if (t != NULL)
    {
        post_order(t->leftChild);
        post_order(t->rightChild);
        linkedBinaryTree<E>::visit(t); 
    }
}

template<class E>
void linkedBinaryTree<E>::erase()
{
    postOrder(dispose); // ���ù��к������,dispose������Ϊvisit
    root = NULL; // �������̾�ɾ����ÿ���ڵ�
    treeSize = 0;
}
template<class E>
void  linkedBinaryTree<E>::dispose(binaryTreeNode<E>* t) 
{ 
    // ɾ��1���ڵ�,������Ϊvisit�����к����������,�����Ĺ�����ɾ�����нڵ�
    delete t;
}
template<class E>
void linkedBinaryTree<E>::output(binaryTreeNode<E>* t)
{
    cout << t->data << "  ";
}
template <class E>
int linkedBinaryTree<E>::height(binaryTreeNode<E>* t)
{
    if (t == NULL)
        return 0;
    // �ݹ�õ��߶�
    int hl = height(t->leftChild);  // �������ĸ߶�
    int hr = height(t->rightChild); // �������ĸ߶�
    //cout << hl << "  " << hr << endl;
    if (hl > hr)
        return ++hl;
    else
        return ++hr;
}

template<class E>
void linkedBinaryTree<E>::makeTree(const E& element,
    linkedBinaryTree<E>& left, linkedBinaryTree<E>& right)
{
    // ����1��ȫ�ָ��ڵ�������������������й���
    // ȫ�ָ��ڵ���element����,ȫ�ָ��ڵ��2������ָ��2�ô���Ķ��������ڵ�������
    // �����Ƚ����
    root = new binaryTreeNode<E>(element, left.root, right.root); 
    treeSize = left.treeSize + right.treeSize + 1; // ȫ�ֽڵ���Ŀ=���ڵ�+���������ڵ�����

    // ��2�����ڵ�ʵ������ȫ�ָ��ڵ����������
    // ��Ϊ3��������ڵ㹹�캯��ʵ��û�н����������ÿ�,������Ҫ�������
    //root->leftChild = left.root = NULL;
    //root->rightChild = right.root = NULL;
    left.root = right.root = NULL;  // ��ֹ�������Һ��Ӹ��ڵ�
    left.treeSize = right.treeSize = 0;
}

// ��������
template<class E>
E* linkedBinaryTree<E>::rootElement() const
{// Return NULL if no root. Otherwise, return pointer to root element.
    if (treeSize == 0)
        return NULL;  // no root
    else
        return &root->element;
}
template<class E>
linkedBinaryTree<E>& linkedBinaryTree<E>::removeLeftSubtree()
{// Remove and return the left subtree.
   // check if empty
    if (treeSize == 0)
        throw emptyTree();

    // detach left subtree and save in leftSubtree
    linkedBinaryTree<E> leftSubtree;
    leftSubtree.root = root->leftChild;
    count = 0;
    leftSubtree.treeSize = countNodes(leftSubtree.root);
    root->leftChild = NULL;
    treeSize -= leftSubtree.treeSize;

    return leftSubtree;
}
template<class E>
linkedBinaryTree<E>& linkedBinaryTree<E>::removeRightSubtree()
{// Remove and return the right subtree.
   // check if empty
    if (treeSize == 0)
        throw emptyTree();

    // detach right subtree and save in rightSubtree
    linkedBinaryTree<E> rightSubtree;
    rightSubtree.root = root->rightChild;
    count = 0;
    rightSubtree.treeSize = countNodes(rightSubtree.root);
    root->rightChild = NULL;
    treeSize -= rightSubtree.treeSize;

    return rightSubtree;
}
#endif // !chapter11_linkedBinaryTree_
