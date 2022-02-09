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
    int height() const { return height(root); }// 外部访问调用是内部的height函数

    void preOrder(void(*theVisit)(binaryTreeNode<E>*));// 公有前序遍历
    void inOrder(void(*theVisit)(binaryTreeNode<E>*));// 公有中序遍历
    void erase();
    void postOrder(void(*theVisit)(binaryTreeNode<E>*));// 公有后序遍历
    void levelOrder(void(*theVisit)(binaryTreeNode<E>*)); // 公有层次遍历

    void makeTree(const E& element,linkedBinaryTree<E>&left, linkedBinaryTree<E>&right);

    // 如果外部没有提供visit函数,默认可以使用output来输出
    void preOrderOutput() { preOrder(output); cout << endl; }
    void inOrderOutput() { inOrder(output); cout << endl; }
    void postOrderOutput() { postOrder(output); cout << endl; }
    void levelOrderOutput() { levelOrder(output); cout << endl; }


    // 其他函数,暂时不进行测试和说明
    E* rootElement() const;
    linkedBinaryTree<E>& removeLeftSubtree();
    linkedBinaryTree<E>& removeRightSubtree();
protected:
    binaryTreeNode<E>* root; // 根节点指针
    int treeSize; // 节点个数
    static int testStatic ; // 用于测试static变量的
    /*
    指向函数的指针,返回值类型为void,参数类型为binaryTreeNode *
    声明为静态时因为该指针属于二叉树类,而不是二叉树对象,也就是说在其他文件可以改变这个类的成员函数
    被赋值后该函数指针应该可以持续存在,无论是哪种遍历方式都可以调用visit函数,且是同一个visit版本
    */
    static void (*visit)(binaryTreeNode<E>*); 
    
    static void pre_order(binaryTreeNode<E>* t); // 私有前序遍历
    static void in_order(binaryTreeNode<E>* t); // 私有中序遍历
    static void post_order(binaryTreeNode<E>* t); // 私有后序遍历
    static void dispose(binaryTreeNode<E>* t); // 可传入公有后序遍历作为visit删除节点

    static void output(binaryTreeNode<E>* t);
    static int height(binaryTreeNode<E>* t);

    // 其它函数和变量
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
// 存在编译器内部的错误,给出了显示声明
// 这个应该是让visit后面的参数类型与visit一致
// 例如想要使用string,必须有string的显式声明否则报错
// 原作者还声明了booster、pair<const int, char> >等类型,这里注释掉暂时用不到
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
    // 公有前序遍历,外部的theVisit给visit函数赋值
    visit = theVisit; pre_order(root); // 调用私有前序遍历
}
template<class E>
void linkedBinaryTree<E>::inOrder(void(*theVisit)(binaryTreeNode<E>*))
{
    // 公有中序遍历,外部的theVisit给visit函数赋值
    visit = theVisit; in_order(root); // 调用私有中序遍历
}
template<class E>
void linkedBinaryTree<E>::postOrder(void(*theVisit)(binaryTreeNode<E>*))
{
    // 公有后序遍历,外部的theVisit给visit函数赋值
    visit = theVisit; post_order(root); // 调用私有后序遍历
}
template <class E>
void linkedBinaryTree<E>::levelOrder(void(*theVisit)(binaryTreeNode<E>*))
{
    arrayQueueSimple<binaryTreeNode<E>*> q;
    binaryTreeNode<E>* t = root;
    while (t != NULL)
    {
        theVisit(t);  // 没有使用visit,直接用传递的函数
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
    // 私有前序遍历
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
    // 私有中序遍历
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
    // 私有后序遍历
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
    postOrder(dispose); // 调用公有后序遍历,dispose函数作为visit
    root = NULL; // 遍历过程就删除了每个节点
    treeSize = 0;
}
template<class E>
void  linkedBinaryTree<E>::dispose(binaryTreeNode<E>* t) 
{ 
    // 删除1个节点,可以作为visit被公有后序遍历调用,遍历的过程中删除所有节点
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
    // 递归得到高度
    int hl = height(t->leftChild);  // 左子树的高度
    int hr = height(t->rightChild); // 右子树的高度
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
    // 给定1个全局根节点和左子树与右子树进行构造
    // 全局根节点以element构造,全局根节点的2个子树指向2棵传入的二叉树根节点来构造
    // 这样比较灵活
    root = new binaryTreeNode<E>(element, left.root, right.root); 
    treeSize = left.treeSize + right.treeSize + 1; // 全局节点数目=根节点+左右子树节点总数

    // 这2个根节点实际上是全局根节点的左右子树
    // 因为3个域的树节点构造函数实现没有将左右子树置空,所以需要额外操作
    //root->leftChild = left.root = NULL;
    //root->rightChild = right.root = NULL;
    left.root = right.root = NULL;  // 阻止访问左右孩子根节点
    left.treeSize = right.treeSize = 0;
}

// 其他函数
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
