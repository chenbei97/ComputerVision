#pragma once
#include "Worker_Individual.h"//�����������
#include <iostream>
using namespace std;
// ����
class  worker_Manager : public workerIndividual //�̳�Ա��������
{
public:
	worker_Manager(int id, string name, int did);
	~worker_Manager();
	virtual void showInfo(); // �麯����д ��ʾ��Ϣ
	virtual string getJobName(); // �麯����д ��ȡ��λ
};