#include <iostream>
using namespace std;
#include "person.h"
template<class T1, class T2>
Person<T1, T2>  ::Person(T1 name, T2 age)
{
	this->_age = age;
	this->_name = name;
}
template<class T1, class T2>
void Person<T1, T2> ::showPerson()
{
	cout << "������" << _name << endl;
	cout << "���䣺" << _age << endl;
}