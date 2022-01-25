#include "charter9_linkedQueue.h"
#include <iostream>
using namespace std;
void _charter9_linkedQueue()
{
	linkedQueue<int> q;
	if (q.empty())
		cout << "The queue is empty" << endl;
	else
		cout << "The queue is not empty" << endl;
	for (int i = 0; i < 25; i++)
		q.push(i + 1);
	cout << "The queue size is " << q.size() << endl;
	q.output(cout);
	while (!q.empty())
		q.pop();
	q.output(cout);
	cout << q << endl;
	try { q.pop(); }
	catch (queueEmpty message)
	{
		cout << "Last pop failed " << endl;
		message.outputMessage();
	}

}