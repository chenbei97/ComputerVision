#pragma once
#include <iostream>
using namespace std;
// 身份的基础抽象类
class Identity
{
public:
	// 纯虚函数 继承多态技术
	// 不同的身份有不同的操作界面
	virtual void operateMenu() = 0;
	string _username; 
	string _password;
};