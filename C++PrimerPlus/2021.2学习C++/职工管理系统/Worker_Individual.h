#pragma once// Ա������������� ����û��ʵ��
#include <iostream>
using namespace std;
class workerIndividual
{
public:
	virtual void showInfo() = 0; //��ʾְ����Ϣ �麯��
	virtual string getJobName() = 0;  // ��ȡ��λ���� �麯��

	int _Id; // ְ�����
	string _Name; //����
	int _DepartId; // ���ű��
};