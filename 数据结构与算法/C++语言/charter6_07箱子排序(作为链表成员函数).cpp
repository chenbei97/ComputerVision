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
        s.score = i / 2;
        s.name = new string(1, aidx++); // 用于命名
        theChain.insert(0, s);
    }
    cout << "The unsorted chain is" << endl;
    cout << "  " << theChain << endl;
    theChain.binSort(10);
    cout << "The sorted chain is" << endl;
    cout << "  " << theChain << endl;
}