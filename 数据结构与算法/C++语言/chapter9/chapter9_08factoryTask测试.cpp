#include <iostream>
#include "chapter9_factoryTask.h"
#include "chapter9_arrayQueueSimple.h"
using namespace std;
void _chapter9_factoryTask()
{
	factoryTask theTask1;
	theTask1.machine = 1;
	theTask1.time = 4;
	cout << "task1 => " << theTask1 <<" &task1 =>" <<&theTask1<< endl;
	factoryTask* theTask2;
	
	theTask2 = new factoryTask(2,3); // ����new���ǵ��ýṹ�幹�캯��
	cout <<"task2 => "<< *theTask2 <<" &task2 => "<<theTask2<< endl;
	
	factoryTask* Task12 = new factoryTask[2];
	Task12[0] = theTask1;
	Task12[1] = *theTask2;
	cout << "&task1_2[0] => " << &Task12[0] << " &task1_2[1] => " << &Task12[1] << endl;
	arrayQueueSimple<factoryTask> qt1;
	qt1.push(Task12[0]); qt1.push(Task12[1]); // task1�ȱ�push,Ϊfront
	cout <<"task1_2 => " << qt1 << endl;

	arrayQueueSimple<factoryTask*> qt2;
	qt2.push(theTask2); qt2.push(Task12);  // 1����task2�ĵ�ַ,1���Ǵ��task1,task2����ĵ�ַ
	cout << "&task1_2 => " << qt2 << endl; // ��ӡ��Ҳ�ǵ�ַ
	cout << "task2 => " << *qt2.front() << endl;  // theTask2=front()
	cout << "task1 => " << qt2.back()[0] << endl; // qt2.back()[0]��Task12[0],Ҳ����task1,
	cout << "task2 => " << qt2.back()[1] << endl; // qt2.back()[1]=Task12[1]=task2
	cout << "&task1 => " << qt2.back() << endl; // qt2.back()=Task12=&Task12[0]��&task1,��ΪTask12��new������
	cout << "task1 => " << *qt2.back() << endl; // *qt2.back()=*Task12=Task12[0] = task1
	delete [] Task12;
	delete theTask2;
}