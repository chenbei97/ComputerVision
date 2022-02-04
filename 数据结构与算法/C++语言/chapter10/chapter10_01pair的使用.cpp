#include <iostream>
//#include <utility>
using namespace std;
void _chapter10_pairStruct_testCode()
{
	// 10 methods to create key-value pair
	string key = "key";string value = "value";
	pair<string, string>  pair1{key, value}; // one
	pair<string, string>  pair2{ string{"key"},string{"value"} }; // two
	pair<string, string>  pair3{ "key",string{"value"} }; // three
	pair<string, string>  pair4{ "key","value"}; // four
	pair<string, string>  pair5{ pair4 }; // five by copy_constructor
	pair<string,string> pair6 = make_pair(key, value); // six  by make_pair function
	auto pair7 = make_pair("name", "bei"); // seven use auto
	auto pair8 = pair<string, string>{ make_pair("key",value) }; // eight pair+make_pair
	pair<string, string> pair9 = pair8; // nine operator =
	pair<string, string> pair10; // ten by first and second member
	pair10.first = "key"; pair10.second = "value";
	
	// pair���������߼��Ƚ�
	// != == �Ƚ�key��value
	if (pair1 == pair10)
		cout << "pair1 == pair10" << endl;
	else
		cout << "pair1 != pair10" << endl;

	// ����С�ڻ���ڱȽϣ�pair ����ĳ�Ա�����ǰ��ֵ�˳��Ƚϵ�
	pair<int, int> p1{ 10, 9 };
	pair<int, int> p2{ 10, 11 };
	pair<int, int> p3{ 11, 8 };
	// false  true  false
	cout << boolalpha << (p1 > p2) << "  " << (p1 < p3) << "  " << (p2 > p3) << endl;
	// p1>p2,��first��ȵ�������ټ����Ƚ�second
	// p1<p3,�ȱȽ�first���������,��ʹp1.second>p3.second
	// p2>p3,��ʹp2.second>p3.second,����first������Ҳ�Ͳ�����

	// cout << boolalpha << (pair1 < pair7) << endl; string�����޷��Ƚ�

	p1.first = 6; // ���Ը���
	pair<const int, int> p4(20, 21);
	// p4.first = 21; �����Ը���
	p4.second = 22; // ���Ը���
}