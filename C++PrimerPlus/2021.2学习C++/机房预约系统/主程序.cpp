/*
1.��ϵͳ��3����ݿ���ʹ��
		ѧ����������ʹ�û���
		��ʦ�����ѧ����ԤԼ����
		����Ա����ѧ������ʦ�����˺�
2.������������
		1�Ż������������20��
		2�Ż������������50��
		3�Ż������������100��
3.����Ķ����ɹ���Ա�������
4.ѧ������ԤԼδ��һ�ܵĻ���ʹ�� ԤԼ������һ������ ԤԼ��Ҫѡ��ʱ��(���硢����)
5.��������
		ѧ����������ѧ�š���������½����
							���ܣ�
									����ԤԼ
									�鿴����ԤԼ
									�鿴����ԤԼ
									ȡ��ԤԼ
									�˳���¼
		��ʦ��ְ���š���������½����
							���ܣ�
									�鿴����ԤԼ
									��ѧ��ԤԼ�������
									�˳���¼
		����Ա������Ա��������½����
							���ܣ�
									����˺ţ���Ҫ���ѧ����ź���ʦְ�����Ƿ��ظ�
									�鿴�˺�ȫ����Ϣ
									�鿴������Ϣ
									���ԤԼ
									�˳���¼
		�˳����˳���ǰ����
6.ԤԼ״̬������С�ԤԼ�ɹ���ԤԼʧ�ܡ�ȡ����ԤԼ
7.������Ϣ��������š��������
*/
#include "GlobalFile.h"
#include "Student.h" //���뵥������ͷ�ļ�
#include "Teacher.h"//���뵥������ͷ�ļ�
#include "computer.h" //���뵥������ͷ�ļ�
#include "Manager.h"//���뵥������ͷ�ļ�
void managerMenu(Identity* &manager)
{
	// ����Ա�˵�  
	// �����˲����˵�������˺š��鿴�˺š��鿴������Ϣ�����ԤԼ��¼����
	// �˺���λ�÷��������� ����Ϊָ����������õ�ָ�� ����Ĳ���Ϊaccount 
	while (true)
	{
		// ����Ա�˵�
		manager->operateMenu();
		Manager* man = (Manager*)manager; //����ָ��ǿתΪ������ָ��
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			// ����˺�
			//cout << "����˺ųɹ���" << endl;
			man->addAccount();
		}
		else if (select == 2)
		{
			//cout << "���ڲ鿴�˺�" << endl;
			man->showAccount();
		}
		else if (select == 3)
		{
			//cout << "���ڲ鿴������Ϣ" << endl;
			man->showComputerInfo();
		}
		else if (select == 4)
		{
			//cout << "���ԤԼ�ɹ���" << endl;
			man->clearFileInfo();
		}
		else
		{
			delete manager;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}

	}
}
void studentMenu(Identity*& student)
{
	// ѧ���˵�  
	// �˺���λ�÷��������� ����Ϊָ����������õ�ָ�� ����Ĳ���Ϊaccount 
	while (true)
	{
		// ѧ���˵�
		student->operateMenu();
		Student* man = (Student*)student; //����ָ��ǿתΪѧ����ָ��
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			// ����ԤԼ
			man->applyOrder();
		}
		else if (select == 2)
		{
			// ��ʾ�ҵ�ԤԼ
			man->showMyOrder();
		}
		else if (select == 3)
		{
			// ��ʾ����ԤԼ
			man->showAllOrder();
		}
		else if (select == 4)
		{
			//ȡ��ԤԼ
			man->cancelOrder();
		}
		else
		{
			delete  student;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
void teacherMenu(Identity*& teacher)
{
	// ��ʦ�˵�  
	// �˺���λ�÷��������� ����Ϊָ����������õ�ָ�� ����Ĳ���Ϊaccount 
	while (true)
	{
		// ��ʦ�˵�
		teacher->operateMenu();
		Teacher* man = (Teacher*)teacher; //����ָ��ǿתΪ��ʦ��ָ��
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			// �鿴ԤԼ
			man->showAllOrder();
		}
		else if (select == 2)
		{
			// ���ԤԼ
			man->examineOrder();
		}
		else
		{
			delete   teacher;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
void LoginIn(string filename, int type)
{
	Identity* account = NULL;
	ifstream ifs;
	ifs.open(filename, ios::in);
	// �ļ�������
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	int id = 0;
	string username;
	string password;
	if (type == 1)
	{
		cout << "���������ѧ�ţ�" << endl;
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "��������Ĺ��ţ�" << endl;
		cin >> id;
	}
	// Ĭ��ִ�й���Ա����
	cout << "�������û�����" << endl;
	cin >> username;
	cout << "���������룺" << endl;
	cin >> password;

	// ��½��֤
	if (type == 1)
	{
		int student_id;
		string student_username;
		string student_password;
		while (ifs >> student_id && ifs >> student_username && ifs >> student_password)
		{
			if (id == student_id && username == student_username && student_password == password)
			{
				//cout << student_id << endl;
				//cout << student_password << endl;
				//cout << student_username << endl;
				cout << "ѧ����֤��½�ɹ�" << endl;
				system("pause");
				system("cls");
				account = new Student(id, username, password);
				// ����ѧ������Ӳ˵�
				studentMenu(account);
				return;
			}
		}
	}
	else if (type == 2)
	{
		int teacher_id;
		string teacher_username;
		string  teacher_password;
		while (ifs >> teacher_id && ifs >> teacher_username && ifs >> teacher_password)
		{
			if (id == teacher_id && username == teacher_username && teacher_password == password)
			{
				//cout << teacher_id << endl;
				//cout << teacher_password << endl;
				//cout << teacher_username << endl;
				cout << "��ʦ��֤��½�ɹ�" << endl;
				system("pause");
				system("cls");
				account = new Teacher(id, username, password);
				// ������ʦ����Ӳ˵�
				teacherMenu(account);
				return;
			}
		}
	}
	else if (type == 3)
	{
		string admin_username;
		string  admin_password;
		while (  ifs >> admin_username && ifs >> admin_password)
		{
			if ( username == admin_username && admin_password == password)
			{
				//cout << admin_password << endl;
				//cout << admin_username << endl;
				cout << "����Ա��֤��½�ɹ�" << endl;
				system("pause");
				system("cls");
				account = new Manager(username, password);
				// �������Ա����Ӳ˵�
				managerMenu(account);
				return;
			}
		}
	}
	cout << "��½��֤ʧ�ܣ�" << endl;
	system("pause");
	system("cls"); 
	return;
}
int main()
{
	int select = 0;
	while (true)
	{

		cout << "====================  ��ӭ�������������˻���ԤԼϵͳ  ==================== " << endl;
		cout << endl << "�������������" << endl;
		cout << "\t\t ----------------------------------------------------\n";
		cout << "\t\t|                                                    |\n";
		cout << "\t\t|                 1. ѧ������                        |\n";
		cout << "\t\t|                                                    |\n";
		cout << "\t\t|                 2. ��    ʦ                        |\n";
		cout << "\t\t|                                                    |\n";
		cout << "\t\t|                 3. ������Ա                        |\n";
		cout << "\t\t|                                                    |\n";
		cout << "\t\t|                 0. ��    ��                        |\n";
		cout << "\t\t|                                                    |\n";
		cout << "\t\t ----------------------------------------------------\n";
		cout << "����������ѡ��";
		cin  >> select;
		switch (select)
		{
		case 1:
			LoginIn(Student_File, 1);
			break;
		case 2:
			LoginIn(Teacher_File, 2);
			break;
		case 3:
			LoginIn(Admin_File, 3);
			break;
		case 0:
			cout << "��ӭ�´�ʹ��~" << endl;
			system("pause");
			system("cls");
			return 0;

			break;
		default:
			cout << "��������������ѡ��" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	return 0;
}