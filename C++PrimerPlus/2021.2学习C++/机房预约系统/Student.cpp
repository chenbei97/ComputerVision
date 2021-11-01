#include  "Student.h"
#include "computer.h"
#include "GlobalFile.h"
#include "OrderFile.h"
Student::Student()
{
}
Student::Student(int id, string username, string password)
{
	this->student_id = id;
	this->_password = password;
	this->_username = username;
	 // ��ʼ��������Ϣ��ӵ�ѧ����������studentComputer
	ifstream ifs;
	ifs.open(Computer_File , ios ::in);
	
	Computer computer;
	while (ifs >> computer.computer_id && ifs >> computer.computer_room_size)
	{
		studentComputer.push_back(computer);
	}
	ifs.close();
}

void  Student::operateMenu()
{
	cout << "��ӭѧ������" << this->_username << "��¼��" << endl;
	cout << "\t\t ----------------------------------------------------\n";
	cout << "\t\t|                                                    |\n";
	cout << "\t\t|                 1. ����ԤԼ                        |\n";
	cout << "\t\t|                                                    |\n";
	cout << "\t\t|                 2. �鿴�ҵ�ԤԼ                    |\n";
	cout << "\t\t|                                                    |\n";
	cout << "\t\t|                 3. �鿴����ԤԼ                    |\n";
	cout << "\t\t|                                                    |\n";
	cout << "\t\t|                 4. ȡ��ԤԼ                        |\n";
	cout << "\t\t|                                                    |\n";
	cout << "\t\t|                 0. ע����¼                        |\n";
	cout << "\t\t|                                                    |\n";
	cout << "\t\t ----------------------------------------------------\n";
	cout << "����������ѡ��" << endl;

}

void Student::applyOrder()
{
	// ѡ�����ڣ���һ������
	cout << "��������ʱ��Ϊ��һ�����壡" << endl;
	cout << "����������ԤԼ��ʱ�䣺" << endl;
	cout << "1����һ��" << endl;
	cout << "2���ܶ���" << endl;
	cout << "3��������" << endl;
	cout << "4�����ģ�" << endl;
	cout << "5�����壡" << endl;
	int date = 0;
	int interval = 0;
	int room = 0;
	// ѡ��ʱ�Σ�����/����
	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "�����������������룡" << endl;
	}
	cout << "����������ԤԼ��ʱ��Σ�" << endl;
	cout << "1������" << endl;
	cout << "2������" << endl;
	while (true)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		cout << "�����������������룡" << endl;
	}
	//ѡ�������1��2��3��
	// ���� studentComputer��3�о��ӣ���16�д����г�ʼ��ʱ����push_back��
	cout << "��ѡ�������" << endl;
	for (int i = 0; i < studentComputer.size(); i++)
	{
		cout << studentComputer[i].computer_id << "�Ż�������Ϊ��" << studentComputer[i].computer_room_size << endl;
	}
	//cout << "1�ŷ�����Ϊ��" << studentComputer[0].computer_room_size<< endl;
	//cout << "2�ŷ�����Ϊ��" << studentComputer[1].computer_room_size<<endl;
	//cout << "3�ŷ�����Ϊ��" << studentComputer[2].computer_room_size<<endl;
	while (true)
	{
		cin >> room;
		if (room >= 1 && room <= 3)
		{
			break;
		}
		cout << "�����������������룡" << endl;
	}
	cout << "ԤԼ�ɹ������������" << endl;
	// ���ɼ�¼-->order.txt
	string datename;
	if (date == 1)
	{
		datename = "��һ";
	}
	else if (date == 2)
	{
		datename = "�ܶ�";
	}
	else if (date == 3)
	{
		datename = "����";
	}
	else if (date == 4)
	{
		datename = "����";
	}
	else 
	{
		datename = "����";
	}
	string intervalname;
	if (interval == 1)
	{
		intervalname = "����";
	}
	else
	{
		intervalname = "����";
	}
	string roomname;
	if (room == 1)
	{
		roomname = "һ�Ż���";
	}
	else if (room == 2)
	{
		roomname = "���Ż���";
	}
	else
	{
		roomname = "���Ż���";
	}
	string statusname;
	if (this->order_status == 0)
	{
		statusname = "ԤԼȡ��";
	}
	else if (this->order_status == 1)
	{
		statusname = "ԤԼ�����";
	}
	else if (this->order_status == 2)
	{
		statusname = "ԤԼ�ɹ�";
	}
	else
	{
		statusname = "ԤԼʧ��";
	}
	ofstream ofs(Order_File, ios::app);
	ofs << endl; //�Ȼ�����׷��д��
	ofs << "ԤԼ����:" << datename << " ";
	ofs << "ԤԼʱ��:" << intervalname << " ";
	ofs << "ѧ��ѧ��:" << this->student_id << " ";
	ofs << "ѧ������:" << this->_username << " ";
	ofs << "ԤԼ����:" << roomname << " ";
	ofs << "ԤԼ״̬:" <<statusname << endl;
	// 0 ȡ����ԤԼ 1 ����� 2 ��ԤԼ -1 ԤԼʧ��
	ofs.close();
	system("pause");
	system("cls");
}
void Student::showMyOrder()
{
	OrderFile of;
	if (of.OrderNum == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	int index = 1;
	for (int i = 0; i < of.OrderNum; i++)
	{
		// c_str()ת����const char*  , atoi��const char*ת����int  ����int���Ը�ѧ�űȽ�
		if (atoi(of.mapOrderFile[i]["ѧ��ѧ��"].c_str()) == this->student_id)
		{
			cout << "��" << index<< "��ԤԼ��¼��Ϣ��" << endl;
			cout << "\tԤԼ���ڣ�" << of.mapOrderFile[i]["ԤԼ����"]<<endl;
			cout << "\tԤԼʱ�Σ�" << of.mapOrderFile[i]["ԤԼʱ��"]<<endl;
			cout << "\tԤԼ���ţ�" << of.mapOrderFile[i]["ԤԼ����"]<<endl;
			cout << "\tԤԼ״̬��" << of.mapOrderFile[i]["ԤԼ״̬"]<<endl;
			index++;
		}
	}
	system("pause");
	system("cls");
}
void Student::showAllOrder()
{
	OrderFile of;
	if (of.OrderNum == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.OrderNum; i++)
	{
		cout << "��"<<i + 1 << "��ԤԼ��¼��Ϣ��"<<endl;
		cout << "\tѧ��������" << of.mapOrderFile[i]["ѧ������"] << endl;
		cout << "\tԤԼ���ڣ�" << of.mapOrderFile[i]["ԤԼ����"]<<endl;
		cout << "\tԤԼʱ�Σ�" << of.mapOrderFile[i]["ԤԼʱ��"]<<endl;
		cout << "\tԤԼ���ţ�" << of.mapOrderFile[i]["ԤԼ����"]<<endl;
		cout << "\tԤԼ״̬��" << of.mapOrderFile[i]["ԤԼ״̬"]<<endl;

	}
	system("pause");
	system("cls");
}
void Student::cancelOrder()
{
	OrderFile of;
	if (of.OrderNum == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	//cout << "����л���ԤԼ�ɹ��ļ�¼����ȡ��������Ϣ������ʾ��" << endl;
	vector <int> v;
	int num = 0; // ��¼��ǰѧ��һ���ж�����ԤԼ��¼
	for (int i = 0; i < of.OrderNum; i++)
	{
		if (atoi(of.mapOrderFile[i]["ѧ��ѧ��"].c_str()) == this->student_id)
		{
			num++;
		}
	}
	cout << this->_username <<"��ԤԼ��¼��" <<num <<"��"<< endl;
	for (int i = 0; i < of.OrderNum; i++)
	{
		if (atoi(of.mapOrderFile[i]["ѧ��ѧ��"].c_str()) == this->student_id)
		{
			if (of.mapOrderFile[i]["ԤԼ״̬"] == "ԤԼ�ɹ�" || of.mapOrderFile[i]["ԤԼ״̬"] == "�����")
			{
				v.push_back(i); // ��¼��ȡ����¼������

				cout << "��" << i + 1 << "��ԤԼ��Ϣ��" << endl; // ʵ�ʵ�λ��
				cout << "\tѧ��������" << of.mapOrderFile[i]["ѧ������"] << endl;
				cout << "\tԤԼ���ڣ�" << of.mapOrderFile[i]["ԤԼ����"] << endl;
				cout << "\tԤԼʱ�Σ�" << of.mapOrderFile[i]["ԤԼʱ��"] << endl;
				cout << "\tԤԼ���ţ�" << of.mapOrderFile[i]["ԤԼ����"] << endl;
				cout << "\tԤԼ״̬��" << of.mapOrderFile[i]["ԤԼ״̬"] << endl;
			}
		}
	}
	// �������������õ��˶�Ӧĳ��ѧ��������л���ԤԼ�ɹ���������Ϣ
	if (v.size() == 0)
	{
		cout << this->_username << "��ȡ����ԤԼ��¼��0��" << endl;
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
			cin >> select;
			if (select >= 0 && select <= num)
			{
				if (select == 0)
				{
					break;
				}
				else
				{
					of.mapOrderFile[select - 1]["ԤԼ״̬"] = "ԤԼȡ��";
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
