#include "chapter5_arrayListBidirectIterator.h"
#include <iostream>
#include <sstream>
#include <numeric> // 包含 reverse
#include <algorithm>
using namespace std;
void _chapter5_arrayList_with_bidirectionalIterator()
{
    _chapter5_arrayListWithIterator<int> y(2); // 容量2
    y.insert(0, 2);
    y.insert(1, 6);//此时容量为2
    y.insert(0, 1);//一旦容量满了再插就会倍增
    printf("the capacity = %d\n", y.capacity()); // the capacity = 4
    y.insert(2, 4);
    y.insert(3, 5); // 再次倍增 the capacity = 8
    y.insert(2, 3);
    printf("the capacity = %d\n", y.capacity()); // the capacity = 8
    cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
    ostringstream s;
    y.output(s);
    cout << "Size of y = " << y.size() << endl;

    // 测试迭代器的使用
    cout << "测试operator++和++operator" << endl;
    cout << "测试operator++" << endl;
    for (_chapter5_arrayListWithIterator<int>::_chapter5_iterator i = y.begin();
        i != y.end(); i++) // 无论前++还是后++i都已经自增不影响结果
        cout << *i << "  "; 
    cout << endl;
    cout << "测试++operator" << endl;
    for (_chapter5_arrayListWithIterator<int>::_chapter5_iterator i = y.begin();
        i != y.end(); ++i)// 无论前++还是后++i都已经自增不影响结果
        cout << *i << "  ";
    cout << endl;

    cout << "测试operator--和--operator" << endl;
    // 使用--需要从后往前,但是y.end()是最后元素位置的后1个,不能越界所以表达式应该是已经变化,使用前-
    for (_chapter5_arrayListWithIterator<int>::_chapter5_iterator i = y.end();
        i != y.begin(); cout << *(--i) << "  "); // 但是把语句放在了判断上就产生了区别
    cout << endl;
    for (_chapter5_arrayListWithIterator<int>::_chapter5_iterator i = y.end();
        i != y.begin();)//语句不放在判断上就简单了,i--和--i没有区别
    {
        // 先i--还是i--都可以
        --i; cout << *i << "  "; *i += 1;
    }
    cout << endl;
    y.output(s);

    //测试一些STL的算法
    reverse(y.begin(), y.end());
    cout << "The reversed list is " << y << endl; // 直接打印也可以
    int sum = accumulate(y.begin(), y.end(), 1); // 最后1个参数是起始值
    cout << "The sum of the elements is " << sum << endl;
}