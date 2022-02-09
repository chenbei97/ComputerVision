#pragma once
#ifndef chapter11_abstractBinaryTree_
#define chapter11_abstractBinaryTree_
#include <functional>
using namespace std;
template<class T>
class abstractBinaryTree
{
public:
    virtual ~abstractBinaryTree() {}
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    // ���������Ĳ�����һ�ֺ�������
    // ��������Ĵ������ΪT*����,����void
    virtual void preOrder(void (*) (T*)) = 0;
    virtual void inOrder(void (*) (T*)) = 0;
    virtual void postOrder(void (*) (T*)) = 0;
    virtual void levelOrder(void (*) (T*)) = 0;
};
#endif // !chapter11_abstractBinaryTree_
