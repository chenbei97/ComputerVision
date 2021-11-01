#pragma once// 员工抽象类的声明 但是没有实现
#include <iostream>
using namespace std;
class workerIndividual
{
public:
	virtual void showInfo() = 0; //显示职工信息 虚函数
	virtual string getJobName() = 0;  // 获取岗位名称 虚函数

	int _Id; // 职工编号
	string _Name; //姓名
	int _DepartId; // 部门编号
};