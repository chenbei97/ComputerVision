#pragma once
#include "Worker_Individual.h"//��ͨԱ���������
#include <iostream>
using namespace std;
// ���ﲻ�Ƕ�Ա���ĳ��������ʵ��
// ���ǶԾ����Ա��ȥʵ��
//string workerIndividual::getJobName(){}
//void workerIndividual::showInfo(){}

// ��ְͨ��
class  worker_Employee : public workerIndividual //�̳�Ա��������
{
public:
	worker_Employee(int id ,string name,int did) ;
	~worker_Employee() ;
	virtual void showInfo(); // �麯����д ��ʾ��Ϣ
	virtual string getJobName(); // �麯����д ��ȡ��λ
};