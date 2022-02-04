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
	
	// pair对象允许逻辑比较
	// != == 比较key和value
	if (pair1 == pair10)
		cout << "pair1 == pair10" << endl;
	else
		cout << "pair1 != pair10" << endl;

	// 对于小于或大于比较，pair 对象的成员变量是按字典顺序比较的
	pair<int, int> p1{ 10, 9 };
	pair<int, int> p2{ 10, 11 };
	pair<int, int> p3{ 11, 8 };
	// false  true  false
	cout << boolalpha << (p1 > p2) << "  " << (p1 < p3) << "  " << (p2 > p3) << endl;
	// p1>p2,在first相等的情况下再继续比较second
	// p1<p3,先比较first成立则成立,即使p1.second>p3.second
	// p2>p3,即使p2.second>p3.second,但是first不成立也就不成立

	// cout << boolalpha << (pair1 < pair7) << endl; string类型无法比较

	p1.first = 6; // 可以更改
	pair<const int, int> p4(20, 21);
	// p4.first = 21; 不可以更改
	p4.second = 22; // 可以更改
}