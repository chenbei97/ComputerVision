#include "Worker_Employee.h" //��ͨԱ����ľ���ʵ��

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
	return  string("��ͨԱ��");
}
void worker_Employee::showInfo()
{
	cout << "-----------��ͨԱ����Ϣչʾ����-----------" << endl;
	cout << "\tְ�����ű�� �� " << this->_DepartId << endl;
	cout << "\tְ����� �� " << this->_Id << endl;
	cout << "\tְ������ �� " << this->_Name << endl;
	cout << "\tְ����λ �� " << this->getJobName() << endl;
	cout << "\tְ��ְ�� �� " << "��ɾ�����������" << endl;
}





