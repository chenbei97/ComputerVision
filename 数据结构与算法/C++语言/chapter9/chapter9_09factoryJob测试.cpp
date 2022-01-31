#include <iostream>
#include "chapter9_factoryJob.h"
#include "chapter9_arrayQueueSimple.h"
using namespace std;
void _chapter9_factoryJob()
{
	factoryJob Job1;
	cout << Job1 << endl;
	Job1.id = 1;

	factoryTask task1(1, 1), task2(2, 2), task3(3, 3);
	Job1.addTask(task1.machine,task1.time);
	cout << "print factoryJob --------------------------------------" << endl;
	cout << Job1 << endl;
	Job1.addTask(task2); Job1.addTask(task3);
	Job1.printTasks(); // 打印任务的工序
	cout << Job1 << endl; // arrivalTime是事件决定的,所以保持0

	Job1.removeNextTask(); // task1被移除
	cout << Job1 << endl; 
	Job1.printTasks();

	cout << "print arrayQueue<factoryJob> --------------------------------------" << endl;
	arrayQueueSimple<factoryJob> theJobs;
	theJobs.push(Job1);
	cout << theJobs << endl;
	factoryJob* Job2 = new factoryJob(2); factoryJob* Job3 = new factoryJob(3);
	Job2->addTask(task3);  // job2只有task3
	Job3->addTask(task3); Job3->addTask(task2);
	Job3->removeNextTask(); // job3只有task2
	theJobs.push(*Job2); theJobs.push(*Job3); 
	cout << theJobs << endl; // job2's length应该是3,job3's length应该是2

	factoryJob* Jobs = new factoryJob[3]; // job数组
	Jobs[0] = Job1; Jobs[1] = *Job2; Jobs[2] = *Job3;

	cout << "print arrayQueue<factoryJob*> --------------------------------------" << endl;
	arrayQueueSimple<factoryJob*> theJ;
	theJ.push(Job2); theJ.push(Job3); theJ.push(Jobs); 
	cout << Job2 << " " << Job3 << " " << Jobs << endl;
	cout << theJ << endl; // theJ存储的就是上边指针指向的地址
	cout << *theJ.front() << endl; // 就是*Job2
	cout << *theJ.back() << endl; // 是*Jobs=*(&Jobs[0]),就是Jobs[0]=Job1
}