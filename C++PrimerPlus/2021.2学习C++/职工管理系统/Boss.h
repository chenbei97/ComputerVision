#pragma once
#include "Worker_Individual.h"//�ϰ��������
#include <iostream>
using namespace std;
// �ϰ�
class  boss : public workerIndividual //�̳�Ա��������
{
public:
	boss(int id, string name, int did);
	~boss();
	virtual void showInfo(); // �麯����д ��ʾ��Ϣ
	virtual string getJobName(); // �麯����д ��ȡ��λ
};