#include "Worker_Employee.h" //普通员工类的具体实现

worker_Employee::worker_Employee(int id,string name,int did)
{
	this->_Id = id;
	this->_Name = name;
	this->_DepartId = did;
}
worker_Employee :: ~worker_Employee()
{
}
string worker_Employee::getJobName()
{
	return  string("普通员工");
}
void worker_Employee::showInfo()
{
	cout << "-----------普通员工信息展示如下-----------" << endl;
	cout << "\t职工部门编号 ： " << this->_DepartId << endl;
	cout << "\t职工编号 ： " << this->_Id << endl;
	cout << "\t职工姓名 ： " << this->_Name << endl;
	cout << "\t职工岗位 ： " << this->getJobName() << endl;
	cout << "\t职工职责 ： " << "完成经理交给的任务" << endl;
}





