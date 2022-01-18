#include "charter5_vectorList.h"
#include <numeric>
#include <algorithm>
using namespace std;
void _charter5_vector_test();
void _charter5_linearList_by_vector()
{
	// �����������ʽ��в���,���ڶ�charter5_vectorList.h��vector��ʹ�ý��н���
	_charter5_vector_test();
	
	// ��ʵ�ֵ�vectorList���в���
	_charter5_linearList<double>* x = new _charter5_vectorList<double>(20); // ����ָ�����ָ������ָ��
	// ����xû������ķ���,��������x->capacity();
	_charter5_vectorList<int> y(2), z; // ֱ�Ӵ���ʵ��,�������capacity()����
	cout << "y.capacity() = " << y.capacity() << endl;
	cout << "Initial size of x, y, and z = "
		<< x->size() << ", " // size�ǹ��еķ���
		<< y.size() << ", "
		<< z.size() << endl;

	// ��insert��������
	y.insert(0, 2);
	y.insert(1, 6);
	y.insert(0, 1);
	y.insert(2, 4);
	y.insert(3, 5);
	y.insert(2, 3);
	cout << "Inserted 6 integers, list y should be 1 2 3 4 5 6" << endl;
	cout << "Size of y = " << y.size() << endl;
	cout << "Capacity of y = " << y.capacity() << endl;
	if (y.empty()) cout << "y is empty" << endl;
	else cout << "y is not empty" << endl;
	y.output(cout);
	cout << endl << "Testing overloaded <<" << endl;//ֱ�Ӵ�ӡҲ�ǿ��Ե�
	cout << y << endl;

	// ���� indexOf
	int index = y.indexOf(4);
	if (index < 0) cout << "4 not found" << endl;
	else cout << "The index of 4 is " << index << endl;
	index = y.indexOf(7);
	if (index < 0) cout << "7 not found" << endl;
	else cout << "The index of 7 is " << index << endl;

	// ����get
	cout << "Element with index 0 is " << y.get(0) << endl;
	cout << "Element with index 3 is " << y.get(3) << endl;

	// ����erase
	y.erase(1);
	cout << "Element 1 erased" << endl;
	cout << "The list is " << y << endl;
	y.erase(2);
	cout << "Element 2 erased" << endl;
	cout << "The list is " << y << endl;
	cout << "Size of y = " << y.size() << endl;
	cout << "Capacity of y = " << y.capacity() << endl;
	if (y.empty()) cout << "y is empty" << endl;
	else cout << "y is not empty" << endl;

	// �����쳣����
	try { y.insert(-3, 0); }
	catch (illegalIndex e)
	{
		cout << "Illegal index exception" << endl;
		cout << "Insert index must be between 0 and list size" << endl;
		e.outputMessage();
	}

	//���Ը��ƹ���
	_charter5_vectorList<int> w(y);
	y.erase(0);
	y.erase(0);
	cout << "w should be old y, new y has first 2 elements removed" << endl;
	cout << "w is " << w << endl;
	cout << "y is " << y << endl;

	//  ���Ե�����
	y.insert(0, 4);
	y.insert(0, 5);
	y.insert(0, 6);
	y.insert(0, 7);
	for (_charter5_vectorList<int>::iterator i = y.begin(); //iteratorʹ���˱���ʵ���Ͼ���vector�Դ���
		i != y.end(); i++)
		cout << *i << "  ";
	cout << endl;

	// ����3��stl�ķ���
	reverse(y.begin(), y.end());
	cout << "The reversed list is " << y << endl;
	int sum = accumulate(y.begin(), y.end(), 0);
	cout << "The sum of the elements is " << sum << endl;
	sort(y.begin(), y.end());
	cout << "The sorted list is " << y << endl;
	sort(y.begin(), y.end(), greater<int>());
	cout << "The list is descending order is " << y << endl;

}
void _charter5_vector_test()
{
	vector<int> arrint1(10);
	vector<int>arrint2(arrint1); // �������ֹ��캯��
	arrint2.insert(arrint2.begin(), 10, 2); //����10��2
	cout << arrint2.capacity() << endl; // �����Զ�����=20
	arrint2.insert(arrint2.end(), 5);
	cout << arrint2.capacity() << endl; // β���ּ�10
	// arrint2.insert(3, 8);ֱ�Ӳ���λ��3�ǲ������,��1�������ǵ���������
	for (vector<int>::const_iterator it = arrint2.begin(); it != arrint2.end(); it++)
		cout << *it << "   ";
	cout << endl;
	printf("arrint2[5] = %d\n", arrint2[5]); // arrint2[5] = 2
}