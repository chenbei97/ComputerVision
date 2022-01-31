#pragma once
#ifndef chapter9_factoryMachine_
#define chapter9_factoryMachine_
#include "chapter9_arrayQueueSimple.h"
#include "chapter9_factoryJob.h"
using namespace std;
// 数据对象包括工序、任务、机器和事件表
// factoryMachine为机器的数据对象
// 每个机器会处于3个状态,执行任务状态,空闲状态和转换任务状态
// 机器有正在执行的任务,使用job*指针来描述,因为正在执行的任务会动态变化
// 任务编号不会超过总数n,机器会有1个任务表jobQueue
// 任务表对应位置的任务随时会出现或者没有,所以存储的任务的指针
struct factoryMachine
{
    arrayQueueSimple<factoryJob*> jobQueue; // 任务表,可以看成指针数组
    int id;
    int changeJobTime;   // 机器转换任务需要的时间
    int totalWaitTime;    // 在该机器总共等待的时间=各任务在该机器等待的时间
    int totalNumTasks;     // 在该机器处理的总工序数
    factoryJob* currentJob;   // 当前正在执行的任务

    factoryMachine()
    {
        totalWaitTime = 0;
        totalNumTasks = 0;
        id = 0;
        changeJobTime = 0;
        currentJob = NULL; // 空闲或者转换任务状态的机器没有任务执行
    }

    factoryMachine(int theid ,int theChangeJobTime )
    {
        totalWaitTime = 0;
        totalNumTasks = 0;
        id = theid;
        changeJobTime = theChangeJobTime;
        currentJob = NULL; // 空闲或者转换任务状态的机器没有任务执行
    }
    void printJobs()
    {
        cout << "theMachine" << id << "'s jobList address as follows~\n"<<jobQueue;
    }
};
inline ostream& operator<< (ostream& out, const factoryMachine& theMachine)
{
    if (theMachine.jobQueue.empty() && (theMachine.currentJob == NULL)) // 任务表没任务且当前没执行任务
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
