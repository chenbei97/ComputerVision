#include <iostream>
#include <Windows.h>
#include "chapter9_factoryMachine.h"
#include "chapter9_factoryEventList.h"
// factoryTask ∈ factoryJob ∈ factoryMachine
using namespace std;
int factoryTimeNow;  // 全局时间变量,当前时间步
int factoryNumMachines;  // 机器数量
int factoryNumJobs;  // 任务数量
factoryEventList* eList; // 事件表数组
factoryMachine* mArray;// 机器编号数组
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
    // 任务分配,测试程序使用P224的案例
    const int nMachines = 3;
    const int nJobs = 4;
    factoryNumMachines = nMachines; // 3台机器,M1,M2,M3
    factoryNumJobs = nJobs;  // 4个任务,J1,J2,J3,J4
    // 创建机器数组和事件表对象
    eList = new factoryEventList(factoryNumMachines); // 具有3个机器的工厂事件
    mArray = new factoryMachine[factoryNumMachines + 1]; // 3个机器的数组对象

    // 设置3个机器基本属性 
    mArray[1].id = 1; mArray[1].changeJobTime = 2; // M1
    mArray[2].id = 2; mArray[2].changeJobTime = 3; // M2
    mArray[3].id = 3; mArray[3].changeJobTime = 1; // M3 
    
     // 创建4个任务
    factoryJob* theJobs = new factoryJob[nJobs+1]; //下标0弃用
    int numTaskOfJob[nJobs+1] = {0,3,2,2,2}; // J1,J2,J3,J4的工序数量依次是3,2,2,2
   // 创建工序二维数组
    factoryTask ** theJobsTasks;
    theJobsTasks = new factoryTask * [nJobs+1]; // 下标0弃用
    for (int i = 1; i <= nJobs; i++)
        theJobsTasks[i] = new factoryTask[numTaskOfJob[i] + 1];
     
    // 指定每道工序花费时间
    theJobsTasks[1][1].time = 2; theJobsTasks[1][2].time = 4; theJobsTasks[1][3].time = 1;
    theJobsTasks[2][1].time = 4; theJobsTasks[2][2].time = 2;
    theJobsTasks[3][1].time = 4; theJobsTasks[3][2].time = 4;
    theJobsTasks[4][1].time = 1; theJobsTasks[4][2].time = 3;
    
    // 指定每道工序执行的机器编号
    theJobsTasks[1][1].machine = 1; theJobsTasks[1][2].machine = 2; theJobsTasks[1][3].machine = 1;
    theJobsTasks[2][1].machine = 3; theJobsTasks[2][2].machine = 1;
    theJobsTasks[3][1].machine = 1; theJobsTasks[3][2].machine = 2;
    theJobsTasks[4][1].machine = 3; theJobsTasks[4][2].machine = 2;

    // 给对应的任务添加工序
    for (int i = 1; i <= nJobs; i++)
        for (int j = 1; j <= numTaskOfJob[i]; j++)
        {
            theJobs[i].id = i;
            theJobs[i].addTask(theJobsTasks[i][j]); // addTask要求是实体不是地址
        }
    //cout << theJobs[1] << endl;
    //theJobs[1].printTasks();

     // 初始时 M1分配任务J1,J3  M2分配任务J2,J4 M3空闲
    // 机器添加任务要求是任务地址而非实体
    mArray[1].jobQueue.push(&theJobs[1]);  // 指定机器1执行任务1
    mArray[1].jobQueue.push(&theJobs[3]); // 任务3等待
    mArray[3].jobQueue.push(&theJobs[2]);// 指定机器2执行任务2
    mArray[3].jobQueue.push(&theJobs[4]);// 任务4等待
    cout << &theJobs[1] << " " << &theJobs[3] << endl;
    mArray[1].printJobs(); cout << "\n";
    cout << &theJobs[2] << " " << &theJobs[4] << endl;
    mArray[2].printJobs(); cout << "\n";
}
factoryJob* changeState(int theMachine)
{
    // 改变机器的工作状态,返回机器上一个执行的任务
    factoryJob* lastJob;
    if (mArray[theMachine].currentJob == NULL) // 当前机器当前没有任务
    {
        lastJob = NULL; // 说明这次事件发生之前也没有过任务
        if (mArray[theMachine].jobQueue.empty()) // 任务表没任务
            eList->setNextEventFinishTime(theMachine); // 下次事件的完成时间点未知,无限等待
        else
        { // 如果任务表有任务
            mArray[theMachine].currentJob =
                mArray[theMachine].jobQueue.front(); // 执行当前任务
            mArray[theMachine].jobQueue.pop(); // 任务表少1个任务
            mArray[theMachine].totalWaitTime+=
                factoryTimeNow - mArray[theMachine].currentJob->arrivalTime; // 机器总的等待时间要累积上,当前时间-当前工作完成后的时间点
            mArray[theMachine].totalNumTasks++; // 完成1道工序
            int t = mArray[theMachine].currentJob->removeNextTask(); // 移除完成的工序并返回该工序完成的时间
            eList->setNextEventFinishTime(theMachine, factoryTimeNow + t); // 下次事件时间节点=当前时间节点+完成本道工序的时间
        }
    }
    else 
    { // 当前机器不处于空闲,下次事件只可能是另1个任务的工序也可能是是当前任务的下1个工序
        lastJob = mArray[theMachine].currentJob; // 上1个工作是当前执行的工作,因为认为现在的工作是执行完的
        mArray[theMachine].currentJob = NULL; // 当前工作执行完清0
        eList->setNextEventFinishTime(theMachine, factoryTimeNow +
            mArray[theMachine].changeJobTime); // 下1次事件是当前时间+当前机器需要的转换时间
    }

    return lastJob;
}
void factory_task_initialization()
{
    for (int machineId = 1; machineId <= factoryNumMachines; machineId++)
        changeState(machineId); // 每个机器的任务初始化
}
bool moveToNextMachine(factoryJob* theJob)
{
    // 任务的下1道工序转换到下个机器,如果没有下1个工序就返回false
    if (theJob->taskQueue.empty())
    {
        cout << "Job " << theJob->id << " has completed at "
            << factoryTimeNow << " Total wait was "
            << (factoryTimeNow - theJob->length) << endl;
        return false;
    }
    else
    {// theJob有next task 找到那个机器
        int theMachine = theJob->taskQueue.front().machine; // 找到下1个工序,在工序表首位
        mArray[theMachine].jobQueue.push(theJob); // 让这个机器的任务表添加这个任务
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
        int nextToFinish = eList->nextEventMachine(); // 下1个事件应该执行的机器
        factoryTimeNow = eList->nextEventTime(nextToFinish); // 下次事件完成的时间点,也是全局时间点
        factoryJob* theJob = changeState(nextToFinish); // 这个机器转换下个任务并返回上个任务
        if (theJob != NULL && !moveToNextMachine(theJob)) // 如果上个任务不为空且任务的下一个工序转换到下个机器不成功
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