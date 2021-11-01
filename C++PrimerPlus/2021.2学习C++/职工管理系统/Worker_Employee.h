#pragma once
#include "Worker_Individual.h"//普通员工类的声明
#include <iostream>
using namespace std;
// 这里不是对员工的抽象类进行实现
// 而是对具体的员工去实现
//string workerIndividual::getJobName(){}
//void workerIndividual::showInfo(){}

// 普通职工
class  worker_Employee : public workerIndividual //继承员工抽象类
{
public:
	worker_Employee(int id ,string name,int did) ;
	~worker_Employee() ;
	virtual void showInfo(); // 虚函数重写 显示信息
	virtual string getJobName(); // 虚函数重写 获取岗位
};