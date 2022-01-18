#include "charter6_chainListWithIteratorExtend.h"
#include <numeric>
void _charter6_chainListWithIteratorExtend_testCode()
{
	// ����insert��size��output�����������
	_charter6_chainListWithIteratorExtend<int> y;
	cout << y.empty() << endl;
	y.insert(0, 2);
	cout << y.empty() << endl;
	y.insert(1, 6);
	y.insert(0, 1);
	y.insert(2, 4);
	y.insert(3, 5);
	y.insert(2, 3);
	y.output(cout);
	cout << endl;
	cout << "Size of y = " << y.size() << endl;
	cout << y << endl; // ����������͸����ԱfirstNode,listSizeһ�����̳�����û�и���

	// ����erase
	y.erase(5);
	cout << y << endl;

	// ���Ե�������ǰ++�ͺ�++
	for (_charter6_chainListWithIteratorExtend<int>::_charter6_iterator i = y.begin(); // ��Ҳ��ֱ�Ӽ̳�
		i != y.end(); i++)
		cout << *i << "  ";
	cout << endl;
	for (_charter6_chainListWithIteratorExtend<int>::_charter6_iterator i = y.begin();
		i != y.end(); ++i)
	{
		cout << *i << "  ";
		*i += 1;
	}
	cout << endl;

	int sum = accumulate(y.begin(), y.end(), 0);
	cout << "The sum of the elements is " << sum << endl;

	y.clear();
	y.push_back(1);
	y.push_back(2);
	y.push_back(3);
	cout << "Size of y = " << y.size() << endl;
	cout << y << endl;
	y.insert(3, 4);
	y.insert(0, 0);
	cout << "List y should be 0 1 2 3 4" << endl;
	cout << "Size of y = " << y.size() << endl;
	cout << y << endl;

	y.erase(4);
	y.erase(0);
	y.push_back(6);
	cout << "List y should be 1 2 3 6" << endl;
	cout << "Size of y = " << y.size() << endl;
	cout << y << endl;
}