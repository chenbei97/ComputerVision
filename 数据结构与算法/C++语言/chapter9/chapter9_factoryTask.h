#pragma once
#ifndef chapter9_factoryTask_
#define chapter9_factoryTask_
// 数据对象包括工序、任务、机器和事件表
// factoryTask为工序的数据对象
using namespace std;
struct factoryTask
{
    int machine; // 机器M1,M2...是整型编号
    int time;
    // 每个任务工序都需要指定运行机器和完成时间
    factoryTask(int theMachine = 0, int theTime = 0)
    {
        machine = theMachine;
        time = theTime;
    }
};
inline ostream& operator << (ostream& out, const factoryTask& theTask) // 避免重定义使用inline
{
    // theTask是不会变的,可以加const
    out << "(" << theTask.machine << "," << theTask.time << ")"; // 告诉queue怎么打印这种数据类型
    return out;
}
#endif chapter9_factoryTask_
