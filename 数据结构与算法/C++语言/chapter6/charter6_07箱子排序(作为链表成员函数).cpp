#include "charter6_chainListIterator_binSort.h"
#include "charter6_studentRecord2.h"
void _charter6_StudentRecord2_binSort_testCode()
{
    typedef _charter6_studentRecord2 stu;
    typedef _charter6_chainBinSort<stu> chain;
    stu s;
    chain theChain;
    int aidx = 97; // 字符a的ASCII码位置
    for (int i = 1; i <= 20; i++)
    {
        s.score = i / 2; // 得0分和10分各有1个,其它都是2个
        s.name = new string(1, aidx++); // 用于命名
        theChain.insert(0, s); // 插入的元素就是stu
    }
    // 再多插入1个0分的以验证
    s.score = 0;
    s.name = new string(1, 'u');
    theChain.insert(20, s);
    //cout << "The unsorted chain is" << endl;
    //cout << "  " << theChain << endl;
    // theChain.binSort(10,true); // 打印test log信息
    //theChain.binSort(10);// 不打印test log信息
    //cout << "The sorted chain is" << endl;
    //cout << "  " << theChain << endl;
    stu s1;
    s1.score = 0;
    s1.name = new string (1,'v');
    theChain.binSort(10, s1);
    cout << "The sorted chain is" << endl;
    cout << "  " << theChain << endl;
}