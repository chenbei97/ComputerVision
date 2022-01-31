#include <iostream>
#include <Windows.h>
#include "chapter9_factoryMachine.h"
#include "chapter9_factoryEventList.h"
// factoryTask �� factoryJob �� factoryMachine
using namespace std;
int factoryTimeNow;  // ȫ��ʱ�����,��ǰʱ�䲽
int factoryNumMachines;  // ��������
int factoryNumJobs;  // ��������
factoryEventList* eList; // �¼�������
factoryMachine* mArray;// �����������
void factory_task_allocation();
factoryJob* changeState(int theMachine);
void factory_task_initialization();
bool moveToNextMachine(factoryJob* theJob);
void factory_task_execution();
void factory_task_costTime();
void _chapter9_factory_simulation()
{
	cout << "Factory tasks are being assigned..." << endl;
    try 
    {
        factory_task_allocation();
        cout << "Factory task initializing..." << endl;
        factory_task_initialization();
        cout << "Factory task in progress..." << endl;
        factory_task_execution();
        cout << "All factory tasks are completed..." << endl;
        factory_task_costTime();
    }
	catch (bad_alloc)
    {
        cerr << " out of memory ~ " << endl;
        exit(1);
    }
}
void factory_task_allocation()
{
    // �������,���Գ���ʹ��P224�İ���
    const int nMachines = 3;
    const int nJobs = 4;
    factoryNumMachines = nMachines; // 3̨����,M1,M2,M3
    factoryNumJobs = nJobs;  // 4������,J1,J2,J3,J4
    // ��������������¼������
    eList = new factoryEventList(factoryNumMachines); // ����3�������Ĺ����¼�
    mArray = new factoryMachine[factoryNumMachines + 1]; // 3���������������

    // ����3�������������� 
    mArray[1].id = 1; mArray[1].changeJobTime = 2; // M1
    mArray[2].id = 2; mArray[2].changeJobTime = 3; // M2
    mArray[3].id = 3; mArray[3].changeJobTime = 1; // M3 
    
     // ����4������
    factoryJob* theJobs = new factoryJob[nJobs+1]; //�±�0����
    int numTaskOfJob[nJobs+1] = {0,3,2,2,2}; // J1,J2,J3,J4�Ĺ�������������3,2,2,2
   // ���������ά����
    factoryTask ** theJobsTasks;
    theJobsTasks = new factoryTask * [nJobs+1]; // �±�0����
    for (int i = 1; i <= nJobs; i++)
        theJobsTasks[i] = new factoryTask[numTaskOfJob[i] + 1];
     
    // ָ��ÿ�����򻨷�ʱ��
    theJobsTasks[1][1].time = 2; theJobsTasks[1][2].time = 4; theJobsTasks[1][3].time = 1;
    theJobsTasks[2][1].time = 4; theJobsTasks[2][2].time = 2;
    theJobsTasks[3][1].time = 4; theJobsTasks[3][2].time = 4;
    theJobsTasks[4][1].time = 1; theJobsTasks[4][2].time = 3;
    
    // ָ��ÿ������ִ�еĻ������
    theJobsTasks[1][1].machine = 1; theJobsTasks[1][2].machine = 2; theJobsTasks[1][3].machine = 1;
    theJobsTasks[2][1].machine = 3; theJobsTasks[2][2].machine = 1;
    theJobsTasks[3][1].machine = 1; theJobsTasks[3][2].machine = 2;
    theJobsTasks[4][1].machine = 3; theJobsTasks[4][2].machine = 2;

    // ����Ӧ��������ӹ���
    for (int i = 1; i <= nJobs; i++)
        for (int j = 1; j <= numTaskOfJob[i]; j++)
        {
            theJobs[i].id = i;
            theJobs[i].addTask(theJobsTasks[i][j]); // addTaskҪ����ʵ�岻�ǵ�ַ
        }
    //cout << theJobs[1] << endl;
    //theJobs[1].printTasks();

     // ��ʼʱ M1��������J1,J3  M2��������J2,J4 M3����
    // �����������Ҫ���������ַ����ʵ��
    mArray[1].jobQueue.push(&theJobs[1]);  // ָ������1ִ������1
    mArray[1].jobQueue.push(&theJobs[3]); // ����3�ȴ�
    mArray[3].jobQueue.push(&theJobs[2]);// ָ������2ִ������2
    mArray[3].jobQueue.push(&theJobs[4]);// ����4�ȴ�
    cout << &theJobs[1] << " " << &theJobs[3] << endl;
    mArray[1].printJobs(); cout << "\n";
    cout << &theJobs[2] << " " << &theJobs[4] << endl;
    mArray[2].printJobs(); cout << "\n";
}
factoryJob* changeState(int theMachine)
{
    // �ı�����Ĺ���״̬,���ػ�����һ��ִ�е�����
    factoryJob* lastJob;
    if (mArray[theMachine].currentJob == NULL) // ��ǰ������ǰû������
    {
        lastJob = NULL; // ˵������¼�����֮ǰҲû�й�����
        if (mArray[theMachine].jobQueue.empty()) // �����û����
            eList->setNextEventFinishTime(theMachine); // �´��¼������ʱ���δ֪,���޵ȴ�
        else
        { // ��������������
            mArray[theMachine].currentJob =
                mArray[theMachine].jobQueue.front(); // ִ�е�ǰ����
            mArray[theMachine].jobQueue.pop(); // �������1������
            mArray[theMachine].totalWaitTime+=
                factoryTimeNow - mArray[theMachine].currentJob->arrivalTime; // �����ܵĵȴ�ʱ��Ҫ�ۻ���,��ǰʱ��-��ǰ������ɺ��ʱ���
            mArray[theMachine].totalNumTasks++; // ���1������
            int t = mArray[theMachine].currentJob->removeNextTask(); // �Ƴ���ɵĹ��򲢷��ظù�����ɵ�ʱ��
            eList->setNextEventFinishTime(theMachine, factoryTimeNow + t); // �´��¼�ʱ��ڵ�=��ǰʱ��ڵ�+��ɱ��������ʱ��
        }
    }
    else 
    { // ��ǰ���������ڿ���,�´��¼�ֻ��������1������Ĺ���Ҳ�������ǵ�ǰ�������1������
        lastJob = mArray[theMachine].currentJob; // ��1�������ǵ�ǰִ�еĹ���,��Ϊ��Ϊ���ڵĹ�����ִ�����
        mArray[theMachine].currentJob = NULL; // ��ǰ����ִ������0
        eList->setNextEventFinishTime(theMachine, factoryTimeNow +
            mArray[theMachine].changeJobTime); // ��1���¼��ǵ�ǰʱ��+��ǰ������Ҫ��ת��ʱ��
    }

    return lastJob;
}
void factory_task_initialization()
{
    for (int machineId = 1; machineId <= factoryNumMachines; machineId++)
        changeState(machineId); // ÿ�������������ʼ��
}
bool moveToNextMachine(factoryJob* theJob)
{
    // �������1������ת�����¸�����,���û����1������ͷ���false
    if (theJob->taskQueue.empty())
    {
        cout << "Job " << theJob->id << " has completed at "
            << factoryTimeNow << " Total wait was "
            << (factoryTimeNow - theJob->length) << endl;
        return false;
    }
    else
    {// theJob��next task �ҵ��Ǹ�����
        int theMachine = theJob->taskQueue.front().machine; // �ҵ���1������,�ڹ������λ
        mArray[theMachine].jobQueue.push(theJob); // ��������������������������
        theJob->arrivalTime = factoryTimeNow;
        if (eList->nextEventTime(theMachine) == 10000)
            changeState(theMachine);
        return true;
    }
}
void factory_task_execution()
{
    while (factoryNumJobs > 0)
    {
        int nextToFinish = eList->nextEventMachine(); // ��1���¼�Ӧ��ִ�еĻ���
        factoryTimeNow = eList->nextEventTime(nextToFinish); // �´��¼���ɵ�ʱ���,Ҳ��ȫ��ʱ���
        factoryJob* theJob = changeState(nextToFinish); // �������ת���¸����񲢷����ϸ�����
        if (theJob != NULL && !moveToNextMachine(theJob)) // ����ϸ�����Ϊ�����������һ������ת�����¸��������ɹ�
            factoryNumJobs--;
    }
}
void factory_task_costTime()
{
    cout << "Finish time = " << factoryTimeNow << endl;
    for (int p = 1; p <= factoryNumMachines; p++)
    {
        cout << "Machine " << p << " completed "
            << mArray[p].totalNumTasks << " tasks" << endl;
        cout << "The total wait time was "
            << mArray[p].totalWaitTime << endl;
        cout << endl;
    }
}