#include "Worker_Manager.h" //������ľ���ʵ��

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
	return  string("����");
}
void worker_Manager::showInfo()
{
	cout << "-----------������Ϣչʾ����-----------" << endl;
	cout << "\tְ�����ű�� �� " << this->_DepartId << endl;
	cout << "\tְ����� �� " << this->_Id << endl;
	cout << "\tְ������ �� " << this->_Name << endl;
	cout << "\tְ����λ �� " << this->getJobName() << endl;
	cout << "\tְ��ְ�� �� " << "����ϰ彻��������" << endl;
}
