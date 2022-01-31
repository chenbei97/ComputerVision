#include <iostream>
#include "chapter9_factoryMachine.h"
void _chapter9_factoryMachine()
{
	// create 3 machines
	factoryMachine m1;
	cout << m1 << endl;
	m1.changeJobTime = 3;
	m1.id = 1; // (id, changeJobTime)=(1,3)
	factoryMachine m2(2, 2); // (id, changeJobTime)=(2,2)
	cout << m2 << endl;
	factoryMachine m3(3, 1); // (id, changeJobTime)=(3,1)

	// create 10 tasks
	const int nTasks = 10;
	factoryTask** tasks = new factoryTask*[nTasks+1];
	for (int i = 1; i <= nTasks; i++)
		// machine={1,2,3,1,2,3,1,2,3,1},time={1,2,2,3,3,4,4,5,5,6}
		// (1,1),(2,2),(3,2),(1,3),(2,3) || (3,4),(1,4),(2,5),(3,5),(1,6)  10 tasks
		if (i % 3 != 0 )
			tasks[i] = new factoryTask(i % 3,i/2+1); 
		else
			tasks[i] = new factoryTask(3, i / 2 + 1);
	cout << *tasks[nTasks] << endl; // task10

	// create 3 jobs (3,3,4)
	const int nJobs = 3;
	factoryJob* jobs = new factoryJob[nJobs + 1];
	jobs[1].id = 1; jobs[2].id = 2; jobs[3].id = 3;
	for (int i = 1; i <= nTasks; i++)
	{
		if (i <= 3)
			jobs[1].addTask(*tasks[i]); // job1 add 3 tasks
		else if (i >= 7)
			jobs[3].addTask(*tasks[i]); // job3 add 4 tasks
		else
			jobs[2].addTask(*tasks[i]); // job2 add 3 tasks
	}
	cout << jobs[3] << endl;  // (1,4),(2,5),(3,5),(1,6)

	m1.currentJob = &jobs[1];
	m2.currentJob = &jobs[2];
	m3.currentJob = &jobs[3];
	cout << "machine3 is \n"<<m3 << endl;
	m3.printJobs();
	cout << "\n" ;
	m3.jobQueue.push(&jobs[2]); m3.jobQueue.push(&jobs[1]);
	m3.printJobs();
}