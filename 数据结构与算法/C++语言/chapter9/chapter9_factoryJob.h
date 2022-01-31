#pragma once
// ���ݶ�������������񡢻������¼���
// factoryJobΪ��������ݶ���
// ÿ�������ж������,������Ҫ1�������洢�������
// ��Ϊ������밴��˳��ִ��,����Ĺ��������,����ʹ��queue�洢
// ÿ����������ʳ��˹������ݶ���Ҫ��������,��������ɵ�ʱ������񳤶�
// ������ɵ�ʱ��,��Ϊ�������ݶ��󻨷ѵ�ʱ��ʹ�õ�������,��������Ҳ������
// ���񳤶�,Ӧ������ÿ������Ӧ������ʱ����ܺ�
// 1�����������ж������,����Ҫ��������
#ifndef chapter9_factoryJob_
#define chapter9_factoryJob_
#include "chapter9_factoryTask.h"
#include "chapter9_arrayQueueSimple.h"
using namespace std;
struct factoryJob
{
    arrayQueueSimple<factoryTask> taskQueue;   // �������
    int length;               // ���񳤶�
    int arrivalTime;   // �������ʱ��
    int id;                   // ������

    factoryJob(int theId = 0) // ��Ź��캯��,����ȫ����ʼΪ0
    {
        id = theId;
        length = 0; 
        arrivalTime = 0;
    }

    void addTask(int theMachine, int theTime) // �����������µĹ���
    {
        factoryTask theTask(theMachine, theTime); // �µĹ���Ҫ֪������̨����ִ���Լ�����ʱ��
        taskQueue.push(theTask); // ����ֻ���ڶ���β�����,������queue������
        // Ϊ�˼�����ĸ�����,addTaskֻ�ڳ�ʼ������ʱʹ��
        // ������˼ȶ��Ĺ���Ҫ���,��������ִ��ʱ��ʱ����µĹ���
        // ���������������ָ��ӵ����
    }

    void addTask(const factoryTask theTask) // overload
    {
        taskQueue.push(theTask);
    }

    int removeNextTask() // ����Ҳ���Ƴ���1������(ע�ⲻ���Ƴ����1������)
    {
        int theTime = taskQueue.front().time; // ��1��������ڶ��еĵ�1��
        taskQueue.pop();
        length += theTime; // ���񳤶Ȼ�仯
        return theTime;
    }

    void printTasks() 
    {
        cout << "job" << id << "'s tasks as follows~" << endl;
        cout << "(machine,time) => "<< taskQueue << endl; // taskQueue������ӡ����Ϊconst factoryJob & theJob �޷���ӡ
    }
};
inline std:: ostream& operator << (std::ostream& out, const factoryJob & theJob) // �����ض���ʹ��inline
{
    // �˺��������õ�����ӡfactoryJob��ν��� ��cout<<factoryJob<<endl;
    if (theJob.length == 0)
    {
        out << "job" << theJob.id << " don't have tasks";
        return out;
    }
    // theTask�������Լ�const,����theJob����addTask�ᷢ���仯,����ʹ��const�޶�
    out << "job" << theJob.id << "'s informations �� \n"; // ����queue��ô��ӡ������������
    out << "length = " << theJob.length << "\n";
    out << "arrivalTime = " << theJob.arrivalTime << "\n";
    return out;
}
#endif chapter9_factoryJob_
