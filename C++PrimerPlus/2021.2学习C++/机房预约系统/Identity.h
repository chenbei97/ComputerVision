#pragma once
#include <iostream>
using namespace std;
// ��ݵĻ���������
class Identity
{
public:
	// ���麯�� �̳ж�̬����
	// ��ͬ������в�ͬ�Ĳ�������
	virtual void operateMenu() = 0;
	string _username; 
	string _password;
};