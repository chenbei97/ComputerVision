#pragma once
#ifndef chapter9_factoryMachine_
#define chapter9_factoryMachine_
#include "chapter9_arrayQueueSimple.h"
#include "chapter9_factoryJob.h"
using namespace std;
// ���ݶ�������������񡢻������¼���
// factoryMachineΪ���������ݶ���
// ÿ�������ᴦ��3��״̬,ִ������״̬,����״̬��ת������״̬
// ����������ִ�е�����,ʹ��job*ָ��������,��Ϊ����ִ�е�����ᶯ̬�仯
// �����Ų��ᳬ������n,��������1�������jobQueue
// ������Ӧλ�õ�������ʱ����ֻ���û��,���Դ洢�������ָ��
struct factoryMachine
{
    arrayQueueSimple<factoryJob*> jobQueue; // �����,���Կ���ָ������
    int id;
    int changeJobTime;   // ����ת��������Ҫ��ʱ��
    int totalWaitTime;    // �ڸû����ܹ��ȴ���ʱ��=�������ڸû����ȴ���ʱ��
    int totalNumTasks;     // �ڸû���������ܹ�����
    factoryJob* currentJob;   // ��ǰ����ִ�е�����

    factoryMachine()
    {
        totalWaitTime = 0;
        totalNumTasks = 0;
        id = 0;
        changeJobTime = 0;
        currentJob = NULL; // ���л���ת������״̬�Ļ���û������ִ��
    }

    factoryMachine(int theid ,int theChangeJobTime )
    {
        totalWaitTime = 0;
        totalNumTasks = 0;
        id = theid;
        changeJobTime = theChangeJobTime;
        currentJob = NULL; // ���л���ת������״̬�Ļ���û������ִ��
    }
    void printJobs()
    {
        cout << "theMachine" << id << "'s jobList address as follows~\n"<<jobQueue;
    }
};
inline ostream& operator<< (ostream& out, const factoryMachine& theMachine)
{
    if (theMachine.jobQueue.empty() && (theMachine.currentJob == NULL)) // �����û�����ҵ�ǰûִ������
    {
        out << "theMachine"<<theMachine.id<<" don't have jobs~, it's changeJobTime = "<< theMachine.changeJobTime;
        return out;
    }
    out << "theMachine" << theMachine.id << "'s informations as follows~" << endl;
    out << "totalWaitTime = " << theMachine.totalWaitTime << " totalNumTasks = " << theMachine.totalNumTasks << endl;
    out << "theMachine's currentJob as follows~\n"<<*theMachine.currentJob;
    return out;
}
#endif chapter9_factoryMachine_
