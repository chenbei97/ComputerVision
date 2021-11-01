#pragma once
#include "Worker_Individual.h"//老板类的声明
#include <iostream>
using namespace std;
// 老板
class  boss : public workerIndividual //继承员工抽象类
{
public:
	boss(int id, string name, int did);
	~boss();
	virtual void showInfo(); // 虚函数重写 显示信息
	virtual string getJobName(); // 虚函数重写 获取岗位
};