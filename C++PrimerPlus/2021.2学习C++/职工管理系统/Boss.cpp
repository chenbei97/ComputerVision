#include "Boss.h" //老板类的具体实现

boss::boss(int id, string name, int did)
{
	this->_Id = id;
	this->_Name = name;
	this->_DepartId = did;
}
boss :: ~boss()
{
}
string boss::getJobName()
{
	return  string("老板");
}
void boss::showInfo()
{
	cout << "-----------老板信息展示如下-----------" << endl;
	cout << "\t职工部门编号 ： " << this->_DepartId << endl;
	cout << "\t职工编号 ： " << this->_Id << endl;
	cout << "\t职工姓名 ： " << this->_Name << endl;
	cout << "\t职工岗位 ： " << this->getJobName() << endl;
	cout << "\t职工职责 ： " << "负责公司的全部事务" << endl;
}
