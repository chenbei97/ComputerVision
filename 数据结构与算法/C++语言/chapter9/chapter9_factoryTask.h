#pragma once
#ifndef chapter9_factoryTask_
#define chapter9_factoryTask_
// ���ݶ�������������񡢻������¼���
// factoryTaskΪ��������ݶ���
using namespace std;
struct factoryTask
{
    int machine; // ����M1,M2...�����ͱ��
    int time;
    // ÿ����������Ҫָ�����л��������ʱ��
    factoryTask(int theMachine = 0, int theTime = 0)
    {
        machine = theMachine;
        time = theTime;
    }
};
inline ostream& operator << (ostream& out, const factoryTask& theTask) // �����ض���ʹ��inline
{
    // theTask�ǲ�����,���Լ�const
    out << "(" << theTask.machine << "," << theTask.time << ")"; // ����queue��ô��ӡ������������
    return out;
}
#endif chapter9_factoryTask_
