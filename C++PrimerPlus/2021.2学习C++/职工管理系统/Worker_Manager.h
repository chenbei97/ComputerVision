#pragma once
#include "Worker_Individual.h"//经理类的声明
#include <iostream>
using namespace std;
// 经理
class  worker_Manager : public workerIndividual //继承员工抽象类
{
public:
	worker_Manager(int id, string name, int did);
	~worker_Manager();
	virtual void showInfo(); // 虚函数重写 显示信息
	virtual string getJobName(); // 虚函数重写 获取岗位
};