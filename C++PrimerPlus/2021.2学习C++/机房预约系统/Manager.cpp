#include "Manager.h"
#include "GlobalFile.h"
#include "computer.h"
Manager ::Manager()
{
	
}
Manager:: Manager(string username, string password)
{
	this->_password = password;
	this->_username = username;
	this->initVector();
	 // ����û��װ�������� initComputer()
	ifstream ifs;
	ifs.open(Computer_File , ios::in);
	Computer computer;
	while (ifs >> computer.computer_id && ifs >> computer.computer_room_size)
	{
		vectorComputer.push_back(computer);
	}
	cout << "��ǰ����������Ϊ��" <<vectorComputer.size()<< endl;
	ifs.close();
}
void Manager::operateMenu()
{
	cout << "��ӭ����Ա" <<this->_username <<"��¼��"<< endl;
	cout << "\t\t ----------------------------------------------------\n";
	cout << "\t\t|                                                    |\n";
	cout << "\t\t|                 1. ����˺�                        |\n";
	cout << "\t\t|                                                    |\n";
	cout << "\t\t|                 2. �鿴�˺�                        |\n";
	cout << "\t\t|                                                    |\n";
	cout << "\t\t|                 3. �鿴����                        |\n";
	cout << "\t\t|                                                    |\n";
	cout << "\t\t|                 4. ���ԤԼ                        |\n";
	cout << "\t\t|                                                    |\n";
	cout << "\t\t|                 0. ע����¼                        |\n";
	cout << "\t\t|                                                    |\n";
	cout << "\t\t ----------------------------------------------------\n";
	cout << "����������ѡ��"<<endl;
}
void Manager::initVector()
{
	this->vectorStudent.clear();
	this->vectorTeacher.clear();
	//���ڽ������ļ�����ʷ���ݶ������� Ȼ��������бȽ��Ƿ��ظ�
	ifstream ifs;
	ifs.open(Student_File, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ��" << endl;
		return ;
	}
	Student stemp;
	while (ifs >> stemp.student_id && ifs >> stemp._username
		&& ifs >> stemp._password)
	{
		this->vectorStudent.push_back(stemp);
	}
	//cout << "��ǰѧ���˺ŵ�����Ϊ��" <<vectorStudent.size()<< endl;
	ifs.close();


	ifs.open(Teacher_File, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ��" << endl;
		return;
	}
	Teacher T;
	while (ifs >> T.teacher_id && ifs >> T._username
		&& ifs >> T._password)
	{
		this->vectorTeacher.push_back(T);
	}
	//cout << "��ǰ��ʦ�˺ŵ�����Ϊ��" << vectorTeacher.size() << endl;
	ifs.close();
}
bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		// ����ѧ������
		for (vector<Student> ::iterator it = vectorStudent.begin(); it != vectorStudent.end(); it++)
		{
			if (id == it->student_id)
			{
				return true;// ���˵�����ظ�
			}
		}
	}
	else 
	{
		for (vector<Teacher> ::iterator it1 = vectorTeacher.begin(); it1 != vectorTeacher.end(); it1++)
		{
			if (id == it1->teacher_id)
			{
				return true;
			}
		}
	}
	return false;
}
void Manager::addAccount()
{
	// ��2��txt�ļ�д���˺���Ϣ
	cout << "����������˺ŵ����ͣ�"<<endl;
	cout << "1�����ѧ��" << endl;
	cout << "2�������ʦ" << endl;
	string filename; 
	string tip;
	string errorTip;
	ofstream ofs;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		filename = Student_File;
		tip = "������ѧ�ţ�";
		errorTip = "ѧ���ظ������������룡";
	}
	else
	{
		filename = Teacher_File;
		tip = "�����빤�ţ�";
		errorTip = "�����ظ������������룡";
	}
	ofs.open(filename, ios::out | ios::app);
	ofs << endl;
	int  id;
	string username;
	string password;
	cout << tip << endl;
	while (true)
	{
		cin >> id;
		bool ret = this->checkRepeat(id,select);
		if (ret)
		{
			cout << errorTip << endl;
		}
		else { break; }
	}
	cout << "�������û�����" << endl;
	cin >> username;
	cout << "���������룺" << endl;
	cin >> password;
	ofs << id << " " << username << " " << password <<  " ";
	cout << "����˺ųɹ�" << endl;
	
	system("pause");
	system("cls");
	ofs.close();
	this->initVector();// �ظ���ȡ�ļ����ݸ���
	//����Ҫ��ʱ�������� �����´�����˺�ʱ��ⲻ���ظ�
}
void printStudent(Student &s)
{
	// ��ͨ������Ϊ��������
	cout << "ѧ�ţ�" << s.student_id << "\t" << "�û�����" <<
		s._username << "\t" << "���룺" << s._password << endl;
}
void printTeacher(Teacher& s)
{
	// ��ͨ������Ϊ��������
	cout << "ѧ�ţ�" << s.teacher_id << "\t" << "�û�����" <<
		s._username << "\t" << "���룺" << s._password << endl;
}
void Manager::showAccount()
{
	cout << "��ѡ��鿴���˺����ͣ�" << endl;
	cout << "1���鿴����ѧ��" << endl;
	cout << "2���鿴������ʦ" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		cout << "����ѧ���˻�����Ϣ���£�" << endl;
		for_each(vectorStudent.begin(),vectorStudent.end(),printStudent);
	}
	else
	{
		cout << "������ʦ�˻�����Ϣ���£�" << endl;
		for_each(vectorTeacher.begin(), vectorTeacher.end(), printTeacher);
	}
	system("pause");
	system("cls");
}
void Manager::showComputerInfo()
{
	cout << "��������Ϣ���£�" << endl;
	for (vector<Computer> ::iterator it = vectorComputer.begin(); it != vectorComputer.end(); it++)
	{
		cout << "�������Ϊ��" <<it->computer_id<<"\t"
			<<"�����������Ϊ��"<<it->computer_room_size<< endl;
	}
	system("pause");
	system("cls");
}
void Manager::clearFileInfo()
{
	ofstream ofs(Order_File, ios::trunc);
	ofs.close();
	cout << "��ճɹ���" << endl;
	system("pause");
	system("cls");
}
