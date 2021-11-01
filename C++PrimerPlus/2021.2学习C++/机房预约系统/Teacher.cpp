#include"Teacher.h"
// ��ʦ�ࣺ�˵�����(��̬)���鿴����ԤԼ�����ԤԼ
Teacher::Teacher()
{
}
Teacher::Teacher(int  id, string username, string password)
{
	this->_password = password;
	this->_username = username;
	this->teacher_id = id; 
}
void Teacher::operateMenu()
{
	cout << "��ӭ��ʦ����" << this->_username << "��¼��" << endl;
	cout << "\t\t ----------------------------------------------------\n";
	cout << "\t\t|                                                    |\n";
	cout << "\t\t|                 1. �鿴ԤԼ                        |\n";
	cout << "\t\t|                                                    |\n";
	cout << "\t\t|                 2. ���ԤԼ                        |\n";
	cout << "\t\t|                                                    |\n";
	cout << "\t\t|                 0. ע����¼                        |\n";
	cout << "\t\t|                                                    |\n";
	cout << "\t\t ----------------------------------------------------\n";
	cout << "����������ѡ��" << endl;
}
void Teacher::showAllOrder()
{
	OrderFile of;
	if (of.OrderNum== 0)
	{
		cout << "û��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.OrderNum; i++)
	{
		cout << "��" << i + 1 << "��ԤԼ��¼��Ϣ��" << endl;
		cout << "\tѧ��������" << of.mapOrderFile[i]["ѧ������"] << endl;
		cout << "\tԤԼ���ڣ�" << of.mapOrderFile[i]["ԤԼ����"] << endl;
		cout << "\tԤԼʱ�Σ�" << of.mapOrderFile[i]["ԤԼʱ��"] << endl;
		cout << "\tԤԼ���ţ�" << of.mapOrderFile[i]["ԤԼ����"] << endl;
		cout << "\tԤԼ״̬��" << of.mapOrderFile[i]["ԤԼ״̬"] << endl;
	}
}

void Teacher::examineOrder()
{
	OrderFile of;
	if (of.OrderNum == 0)
	{
		cout << "û��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "����˵�ԤԼ������ʾ��" << endl;
	vector <int> v;
	for (int i = 0; i < of.OrderNum; i++)
	{
		if ( of.mapOrderFile[i]["ԤԼ״̬"] == "�����")
		{
			v.push_back(i); // ��¼����˵�����

			cout << "��" << i + 1 << "��ԤԼ��Ϣ��" << endl; // ʵ�ʵ�λ��
			cout << "\tѧ��������" << of.mapOrderFile[i]["ѧ������"] << endl;
			cout << "\tԤԼ���ڣ�" << of.mapOrderFile[i]["ԤԼ����"] << endl;
			cout << "\tԤԼʱ�Σ�" << of.mapOrderFile[i]["ԤԼʱ��"] << endl;
			cout << "\tԤԼ���ţ�" << of.mapOrderFile[i]["ԤԼ����"] << endl;
			cout << "\tԤԼ״̬��" << of.mapOrderFile[i]["ԤԼ״̬"] << endl;
		}
	}
	// �������������õ��˿�����˵�������Ϣ
	if (v.size() == 0)
	{
		cout  << "����˵�ԤԼ��¼��0��" << endl;
		return;
	}
	else
	{
		cout << "������ȡ���ļ�¼���(���ֱ��������������)��" << endl;
		for (vector<int> ::iterator it = v.begin(); it != v.end(); it++)
		{
			cout << "��" << *it + 1 << "��" << endl; // ��֤�����λ�� = 0��1��4
		}
		int select = 0;
		while (true)
		{
			// ѡ�����������
			cin >> select; // ѧ��������ΪҪͳ���Լ���ԤԼ��¼ ����ʦֻ��Ҫ����������˵�����Ŀ����
			if (select >= 0 && select <= of.OrderNum + 1)// ��������Ϣ��������
			{
				if (select == 0)
				{
					break;
				}
				else
				{
					cout << "��������˽����" << endl;
					cout << "1��ͨ��" << endl;
					cout << "2����ͨ��" << endl;
					int sel;
					cin >> sel;
					string statusName;
					if (sel == 1)
					{
						statusName = "ԤԼ�ɹ�";
					}
					else if (sel == 2)
					{
						statusName = "ԤԼʧ��";
					}
					else
					{
						cout << "����������������룡" << endl;
					}
					of.mapOrderFile[select - 1]["ԤԼ״̬"] = statusName;
					of.updateOrder();
					cout << "ԤԼȡ���ɹ�" << endl;
					break;
				}
			}
			else
			{
				cout << "�����������������룡" << endl;
			}
		}
	}
	system("pause");
	system("cls");
}