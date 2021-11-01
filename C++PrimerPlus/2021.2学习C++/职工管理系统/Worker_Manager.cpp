#include "Worker_Manager.h" //经理类的具体实现

worker_Manager::worker_Manager(int id, string name, int did)
{
	this->_Id = id;
	this->_Name = name;
	this->_DepartId = did;
}
worker_Manager :: ~worker_Manager()
{
}
string worker_Manager::getJobName()
{
	return  string("经理");
}
void worker_Manager::showInfo()
{
	cout << "-----------经理信息展示如下-----------" << endl;
	cout << "\t职工部门编号 ： " << this->_DepartId << endl;
	cout << "\t职工编号 ： " << this->_Id << endl;
	cout << "\t职工姓名 ： " << this->_Name << endl;
	cout << "\t职工岗位 ： " << this->getJobName() << endl;
	cout << "\t职工职责 ： " << "完成老板交给的任务" << endl;
}
