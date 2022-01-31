#pragma once
// 数据对象包括工序、任务、机器和事件表
// factoryJob为任务的数据对象
// 每个任务有多个工序,所以需要1个容器存储这个工序
// 因为工序必须按照顺序执行,先入的工序先完成,所以使用queue存储
// 每个任务的性质除了工序数据对象还要有任务编号,该任务完成的时间和任务长度
// 任务完成的时间,因为工序数据对象花费的时间使用的是整型,所以这里也是整型
// 任务长度,应当等于每个工序应当花费时间的总和
// 1个工厂可能有多个任务,所以要有任务编号
#ifndef chapter9_factoryJob_
#define chapter9_factoryJob_
#include "chapter9_factoryTask.h"
#include "chapter9_arrayQueueSimple.h"
using namespace std;
struct factoryJob
{
    arrayQueueSimple<factoryTask> taskQueue;   // 任务工序表
    int length;               // 任务长度
    int arrivalTime;   // 任务完成时间
    int id;                   // 任务编号

    factoryJob(int theId = 0) // 编号构造函数,属性全部初始为0
    {
        id = theId;
        length = 0; 
        arrivalTime = 0;
    }

    void addTask(int theMachine, int theTime) // 任务可以添加新的工序
    {
        factoryTask theTask(theMachine, theTime); // 新的工序要知道在哪台机器执行以及花费时间
        taskQueue.push(theTask); // 工序只能在队列尾部添加,所以用queue来描述
        // 为了简化问题的复杂性,addTask只在初始化任务时使用
        // 任务除了既定的工序要完成,还可以在执行时临时添加新的工序
        // 本案例不考虑这种复杂的情况
    }

    void addTask(const factoryTask theTask) // overload
    {
        taskQueue.push(theTask);
    }

    int removeNextTask() // 任务也可移除下1个工序(注意不是移除最后1个工序)
    {
        int theTime = taskQueue.front().time; // 下1个工序就在队列的第1个
        taskQueue.pop();
        length += theTime; // 任务长度会变化
        return theTime;
    }

    void printTasks() 
    {
        cout << "job" << id << "'s tasks as follows~" << endl;
        cout << "(machine,time) => "<< taskQueue << endl; // taskQueue单独打印是因为const factoryJob & theJob 无法打印
    }
};
inline std:: ostream& operator << (std::ostream& out, const factoryJob & theJob) // 避免重定义使用inline
{
    // 此函数是设置单独打印factoryJob如何进行 即cout<<factoryJob<<endl;
    if (theJob.length == 0)
    {
        out << "job" << theJob.id << " don't have tasks";
        return out;
    }
    // theTask不会变可以加const,但是theJob可以addTask会发生变化,不能使用const限定
    out << "job" << theJob.id << "'s informations ↓ \n"; // 告诉queue怎么打印这种数据类型
    out << "length = " << theJob.length << "\n";
    out << "arrivalTime = " << theJob.arrivalTime << "\n";
    return out;
}
#endif chapter9_factoryJob_
