#include <iostream>
#include "chapter9_factoryEventList.h"
void _chapter9_factoryEventList()
{
	const int nMachines = 3;
	factoryEventList theEvent(3);
	theEvent.setNextEventFinishTime(1, 3); // M1 nextTime=3
	theEvent.setNextEventFinishTime(2, 1); // M2 nextTime=1
	theEvent.setNextEventFinishTime(2, 2); // M3 nextTime=2
	cout << "next machine 1 next event finish time is " << theEvent.nextEventTime(1) << endl;
	cout << "the machine to process next event is " << theEvent.nextEventMachine() << endl;
}