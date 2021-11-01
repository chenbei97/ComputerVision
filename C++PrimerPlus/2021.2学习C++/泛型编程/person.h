#pragma once
#include <iostream>
using namespace std;
// ÀàÍâÉùÃ÷
template <class T1, class T2>
class Person
{
public:
	T1 _name;
	T2 _age;
	Person(T1 name, T2 age);
	void showPerson();
};
