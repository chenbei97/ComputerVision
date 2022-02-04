#include <iostream>
#include "chapter10_dictionaryArray.h"
void _chapter10_dictionaryArray_testCode()
{
	dictionaryArray<int,int> d1(3),d2;
	pair<int, int> p;
	d1.output(cout);
	p.first = 1; p.second = 10; d1.insert(p);
	p.first = 5; p.second = 50; d1.insert(p);
	p.first = 3; p.second = 30; d1.insert(p);
	d1.output(cout);
	cout << d1 << endl;
	p.first = -1; p.second = -10; d1.insert(p);
	p.first = 1; p.second = 1; d1.insert(p); // ���Բ����ظ��ؼ����Ƿ�д
	cout << d1 << endl;
	d1.erase(1);
	cout << d1 << endl;
	d1.erase(6); // ����ɾ��û�еĹؼ���
	d1.find(6); // ����findû�еĹؼ���
	pair<const int, int> * kv = d1.find(-1);
	cout << "kv->first = " << kv->first << "  kv->second = " << kv->second << endl;
}