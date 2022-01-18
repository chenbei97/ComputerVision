#include "charter6_chainList.h"
void _charter6_chainList_testCode()
{
	_charter6_chainList<int> chain1(5);
	// ����insert<<���غ�output
	chain1.insert(0, 1);
	chain1.insert(1, 2);
	chain1.insert(2, 3);
	chain1.insert(3, 4);
	chain1.insert(4, 5);
	chain1.output(cout); // ֻ0��4����2��Ԫ�ش�ӡ�����ᱨ��
	cout << chain1 << endl; // overload test
	
	// ���Ը��ƹ���
	_charter6_chainList<int> chain2(chain1);

	// ����get,indexOf,size,empty
	cout << "Size of chain2 = " << chain2.size() << endl;
	if (chain2.empty()) cout << "chain2 is empty" << endl;
	else cout << "chain2 is not empty" << endl;
	int index = chain2.indexOf(4);
	if (index < 0) cout << "4 not found" << endl;
	else cout << "The index of 4 is " << index << endl;
	cout << "Element with index 0 is " << chain2.get(0) << endl;

	// ����erase
	chain2.erase(3);
	cout << "Element 3 erased" << endl;
	cout << "The list is " << chain2 << endl;
}