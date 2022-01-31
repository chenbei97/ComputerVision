#pragma once
#ifndef chapter9_factoryEventList_
#define chapter9_factoryEventList_
#include "chapter1_illegalParameterValue.h"
// ���ݶ�������������񡢻������¼���
// factoryEventListΪ�¼�������ݶ���
// ���л������������ʱ�䶼�洢��1���¼�����
// 1���¼���Ҫ��2����: ��������������һ������ִ��,�������һ������ִ��
// 1���¼���ʼ�ͽ�����ʱ�̶��ᱻ��¼
// ��1���¼�����1���¼���Ҫȷ�����л������ʱ������С��
// ���ʱ���ֻ�ڻ���������ִ��ʱ������
// ��������ʱ���ʱ�������������,��Ϊ1���ܴ����largeTime
// �¼����ʱ���ʹ��finshTime��������,finshTime[i]��ʾ����i�����ʱ���
// �¼����ʱ�����һֱ��������,����finshTimeʵ�����Ƿ����ĸ��ǲ���
// finshTime[i]�����ǻ���i��������¼����ۻ����ѵ��¼�
// �����ʱ���ۼӵĹ��̲������ڽ���,��Ϊ�¼�ȡ��������,�������и��ֿ���
// ����finshTime[i]�ĸ���ֻ��������ı�,�ṩ��setNextEventFinishTime����
using namespace std;
class factoryEventList
{
public:
    factoryEventList(int theNumMachines, int theLargeTime = 10000);
    int nextEventMachine();
    int nextEventTime(int theMachine);
    void setNextEventFinishTime(int theMachine, int theTime = 10000);
private:
    int* finishTime;   // ���ڸ������л��������ʱ�������
    int numMachines;   // ��������
};
inline factoryEventList::factoryEventList(int theNumMachines, int theLargeTime)
{
    // �����¼��Ի��������ͻ������ʱ���������
    if (theNumMachines < 1)
        throw illegalParameterValue
        ("number of machines must be >= 1");
    numMachines = theNumMachines;
    finishTime = new int[numMachines + 1]; // �±�0����

    for (int i = 1; i <= numMachines; i++)
        finishTime[i] = theLargeTime; 
}

inline int factoryEventList::nextEventMachine()
{
    // ������һ���¼�Ӧ��ȥ����Ļ������
    // ���������������ɵ�ǰ�������Ļ���,��ô��������һ���¼�����״̬
    // Ҳ��������֮ǰ��������Ѿ����ڿ���״̬�Ļ���,������Ϊ�����˳������ʱû�ֵ���
    int p = 1; // ���ٻ᷵�ػ������1,�ʼ���л������ʱ��㶼��largeTime,��ôȡ���1����
    int t = finishTime[1]; // �����и���Ļ������,�Ƚ��¼����ʱ��㼴��,��С��ʱ������ȵ�����¼�
    for (int i = 2; i <= numMachines; i++)
        if (finishTime[i] < t)
        {
            p = i; // �������i��ɵĸ���
            t = finishTime[i];
        }
    return p;
}

inline int factoryEventList::nextEventTime(int theMachine) 
{ 
    // ������1���¼�ִ�еĻ�����ָ�������ʱ���
    return finishTime[theMachine];  // nextEventTime(nextEventMachine())
}

inline void factoryEventList ::setNextEventFinishTime(int theMachine, int theTime)
{
    // �������û�����һ�¼������ʱ���
    finishTime[theMachine] = theTime; 
}
#endif chapter9_factoryEventList_
