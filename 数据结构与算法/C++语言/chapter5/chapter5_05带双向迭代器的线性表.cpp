#include "chapter5_arrayListBidirectIterator.h"
#include <iostream>
#include <sstream>
#include <numeric> // ���� reverse
#include <algorithm>
using namespace std;
void _chapter5_arrayList_with_bidirectionalIterator()
{
    _chapter5_arrayListWithIterator<int> y(2); // ����2
    y.insert(0, 2);
    y.insert(1, 6);//��ʱ����Ϊ2
    y.insert(0, 1);//һ�����������ٲ�ͻᱶ��
    printf("the capacity = %d\n", y.capacity()); // the capacity = 4
    y.insert(2, 4);
    y.insert(3, 5); // �ٴα��� the capacity = 8
    y.insert(2, 3);
    printf("the capacity = %d\n", y.capacity()); // the capacity = 8
    cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
    ostringstream s;
    y.output(s);
    cout << "Size of y = " << y.size() << endl;

    // ���Ե�������ʹ��
    cout << "����operator++��++operator" << endl;
    cout << "����operator++" << endl;
    for (_chapter5_arrayListWithIterator<int>::_chapter5_iterator i = y.begin();
        i != y.end(); i++) // ����ǰ++���Ǻ�++i���Ѿ�������Ӱ����
        cout << *i << "  "; 
    cout << endl;
    cout << "����++operator" << endl;
    for (_chapter5_arrayListWithIterator<int>::_chapter5_iterator i = y.begin();
        i != y.end(); ++i)// ����ǰ++���Ǻ�++i���Ѿ�������Ӱ����
        cout << *i << "  ";
    cout << endl;

    cout << "����operator--��--operator" << endl;
    // ʹ��--��Ҫ�Ӻ���ǰ,����y.end()�����Ԫ��λ�õĺ�1��,����Խ�����Ա��ʽӦ�����Ѿ��仯,ʹ��ǰ-
    for (_chapter5_arrayListWithIterator<int>::_chapter5_iterator i = y.end();
        i != y.begin(); cout << *(--i) << "  "); // ���ǰ����������ж��ϾͲ���������
    cout << endl;
    for (_chapter5_arrayListWithIterator<int>::_chapter5_iterator i = y.end();
        i != y.begin();)//��䲻�����ж��Ͼͼ���,i--��--iû������
    {
        // ��i--����i--������
        --i; cout << *i << "  "; *i += 1;
    }
    cout << endl;
    y.output(s);

    //����һЩSTL���㷨
    reverse(y.begin(), y.end());
    cout << "The reversed list is " << y << endl; // ֱ�Ӵ�ӡҲ����
    int sum = accumulate(y.begin(), y.end(), 1); // ���1����������ʼֵ
    cout << "The sum of the elements is " << sum << endl;
}