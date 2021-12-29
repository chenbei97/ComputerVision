#include "charter6_chainListWithIterator.h"
#include <numeric>
void _charter6_chainListWithIterator_testCode()
{
	_charter6_chainListWithIterator<int> y;
	y.insert(0, 2);
	y.insert(1, 6);
	y.insert(0, 1);
	y.insert(2, 4);
	y.insert(3, 5);
	y.insert(2, 3);
	cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
	cout << "Size of y = " << y.size() << endl;
	cout << " y list is " << y << endl; // ²âÊÔÖØÔØ<<
	cout << "²âÊÔi++" << endl;
	for (_charter6_chainListWithIterator<int>::_charter6_iterator i = y.begin();
		i != y.end(); i++)
		cout << *i << "  ";
	cout << endl;
	cout << "²âÊÔ++i" << endl;
	for (_charter6_chainListWithIterator<int>::_charter6_iterator i = y.begin();
		i != y.end(); ++i)
	{
		cout << *i << "  ";
		*i += 1;
	}
	cout << endl;

	int sum = accumulate(y.begin(), y.end(), 0);
	cout << "The sum of the elements is " << sum << endl;

}