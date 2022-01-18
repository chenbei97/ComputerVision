#include "charter6_chainListIterator_binSort.h"
#include "charter6_studentRecord2.h"
void _charter6_StudentRecord2_binSort_testCode()
{
    typedef _charter6_studentRecord2 stu;
    typedef _charter6_chainBinSort<stu> chain;
    stu s;
    chain theChain;
    int aidx = 97; // �ַ�a��ASCII��λ��
    for (int i = 1; i <= 20; i++)
    {
        s.score = i / 2; // ��0�ֺ�10�ָ���1��,��������2��
        s.name = new string(1, aidx++); // ��������
        theChain.insert(0, s); // �����Ԫ�ؾ���stu
    }
    // �ٶ����1��0�ֵ�����֤
    s.score = 0;
    s.name = new string(1, 'u');
    theChain.insert(20, s);
    //cout << "The unsorted chain is" << endl;
    //cout << "  " << theChain << endl;
    // theChain.binSort(10,true); // ��ӡtest log��Ϣ
    //theChain.binSort(10);// ����ӡtest log��Ϣ
    //cout << "The sorted chain is" << endl;
    //cout << "  " << theChain << endl;
    stu s1;
    s1.score = 0;
    s1.name = new string (1,'v');
    theChain.binSort(10, s1);
    cout << "The sorted chain is" << endl;
    cout << "  " << theChain << endl;
}