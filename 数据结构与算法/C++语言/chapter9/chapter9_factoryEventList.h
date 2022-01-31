#pragma once
#ifndef chapter9_factoryEventList_
#define chapter9_factoryEventList_
#include "chapter1_illegalParameterValue.h"
// 数据对象包括工序、任务、机器和事件表
// factoryEventList为事件表的数据对象
// 所有机器的任务完成时间都存储在1个事件表里
// 1个事件主要是2件事: 机器的任务表的下一个任务执行,任务的下一个工序执行
// 1个事件开始和结束的时刻都会被记录
// 从1个事件到下1个事件就要确定所有机器完成时间点的最小者
// 完成时间点只在机器有任务执行时有意义
// 机器空闲时完成时间点趋近于无穷,设为1个很大的数largeTime
// 事件完成时间点使用finshTime变量描述,finshTime[i]表示机器i的完成时间点
// 事件完成时间点是一直在增长的,数组finshTime实际上是反复的覆盖操作
// finshTime[i]最终是机器i完成所有事件后累积花费的事件
// 但这个时间累加的过程不在类内进行,因为事件取决于任务,而任务有各种可能
// 所以finshTime[i]的更新只能在类外改变,提供了setNextEventFinishTime函数
using namespace std;
class factoryEventList
{
public:
    factoryEventList(int theNumMachines, int theLargeTime = 10000);
    int nextEventMachine();
    int nextEventTime(int theMachine);
    void setNextEventFinishTime(int theMachine, int theTime = 10000);
private:
    int* finishTime;   // 用于更新所有机器的完成时间点数组
    int numMachines;   // 机器数量
};
inline factoryEventList::factoryEventList(int theNumMachines, int theLargeTime)
{
    // 工厂事件以机器数量和机器完成时间点来构造
    if (theNumMachines < 1)
        throw illegalParameterValue
        ("number of machines must be >= 1");
    numMachines = theNumMachines;
    finishTime = new int[numMachines + 1]; // 下标0弃用

    for (int i = 1; i <= numMachines; i++)
        finishTime[i] = theLargeTime; 
}

inline int factoryEventList::nextEventMachine()
{
    // 返回下一个事件应该去处理的机器编号
    // 这个机器可以是完成当前任务最快的机器,那么它处于下一个事件可用状态
    // 也可能是在之前任务完成已经处于空闲状态的机器,但是因为工序的顺序性暂时没轮到它
    int p = 1; // 至少会返回机器编号1,最开始所有机器完成时间点都是largeTime,那么取编号1即可
    int t = finishTime[1]; // 可能有更快的机器编号,比较事件完成时间点即可,更小的时间点是先到达的事件
    for (int i = 2; i <= numMachines; i++)
        if (finishTime[i] < t)
        {
            p = i; // 机器编号i完成的更快
            t = finishTime[i];
        }
    return p;
}

inline int factoryEventList::nextEventTime(int theMachine) 
{ 
    // 返回下1个事件执行的机器所指定的完成时间点
    return finishTime[theMachine];  // nextEventTime(nextEventMachine())
}

inline void factoryEventList ::setNextEventFinishTime(int theMachine, int theTime)
{
    // 用于设置机器下一事件的完成时间点
    finishTime[theMachine] = theTime; 
}
#endif chapter9_factoryEventList_
