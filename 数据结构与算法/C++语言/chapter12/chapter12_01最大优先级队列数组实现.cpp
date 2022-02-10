#include "chapter12_maxPriorityQueue.h"
void _chapter12_maxPriorityQueue_byNoSortedArray()
{
	maxPriorityQueue<int> q(4);
	try
	{
		cout << q.top() << endl;
	}
	catch (queueEmpty e)
	{
		e.outputMessage();
	}
	q.push(weightNode<int>(60, 0.6));
	q.push(weightNode<int>(70, 0.7));
	q.push(weightNode<int>(80, 0.8));
	q.push(weightNode<int>(90, 0.9));
	cout << q.getCapacity() << endl;
	q.push(weightNode<int>(100, 1.0));
	cout << q.getCapacity() << endl;
	cout << q.top() << endl;
	cout << q << endl;
	
	q.pop(); q.pop(); q.pop(); q.pop(); q.pop();
	cout << q << endl;
	int size = q.size();
	cout <<size<<endl;
	srand((unsigned)time(NULL));
	for (int i = 0 ; i <10;i++)
		q.push(weightNode<int>(rand(), (double)rand() / (RAND_MAX + 1.0)));
	cout << q << endl;
}