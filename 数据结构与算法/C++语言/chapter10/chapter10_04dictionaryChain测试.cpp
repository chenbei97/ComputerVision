#include "chapter10_dictionaryChain.h"
#include <iostream>
void _chapter10_dictionaryChain_testVode()
{
	dictionaryChain<int, int> z; // ʹ��int,int���Խ��бȽ�
	pair<int, int> p; // ��Ϊinsert��ͨ��newʵ��,p���Է���ʹ��,ֻ���ṩ1����ֵ

	p.first = 2; p.second = 10;z.insert(p); 
	p.first = 10; p.second = 50;z.insert(p);
	p.first = 6; p.second = 30;z.insert(p);
	p.first = 8; p.second = 40;z.insert(p);
	p.first = 1; p.second = 5;z.insert(p);
	p.first = 12; p.second = 60;z.insert(p);
	cout << "chain size is " << z.size() << endl;
	cout << "The chain's " << z << endl; // ��ӡ˳���ǰ���key��С�����
	// find���ص���pairNode�ĳ�Աelement��ֵ��ָ��,����second��Աʹ��->�����
	cout << "key = 12 " << " value is " << z.find(12)->second << endl;
	z.insert(pair<int, int>{12, 600});
	cout << "key = 12 " << " value is " << z.find(12)->second << endl; // ��д

	z.erase(1);z.erase(2);z.erase(6);
	cout << "After erase,the chain's " << z << endl;

}