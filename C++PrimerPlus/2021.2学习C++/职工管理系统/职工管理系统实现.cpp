#include <iostream>
using namespace std;
#include "Worker_System.h"
#include "Worker_Employee.h"// �ڲ��Ѿ�������Ա���������ͷ�ļ� 
#include "Worker_Manager.h"
#include "Boss.h"
void test_employee_manager_boss()
{
	worker_Employee * employee = NULL; // ����ָ�봴����ͨԱ��������ܵ��ø�����д
	employee = new worker_Employee(1,"����Ա��",10);
	employee->showInfo();
	delete employee;
	worker_Manager* manager = new worker_Manager(2, "���ľ���", 20);
	manager->showInfo();
	delete manager;
	boss* bos = new boss(3, "�����ϰ�", 30);
	bos->showInfo();
	delete bos;
}
int main()
{
	workerSystem wm;
	//test_employee_manager_boss(); // ����Ա����
	
	int choice = 0;
	while (true)
	{
		wm.Show_Menu();// �˵�����
		cout << "����������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0 : //�˳�ϵͳ
			wm.ExitSystem();
			 break;
		case 1:  // ���Ա��
			wm.Add_Emp();
			break;
		case 2: // չʾԱ����Ϣ
			wm.Show_Employee();
			break;
		case 3: // ɾ��Ա��
			wm.Del_Employee();
			break;
		case 4:// �޸�Ա����Ϣ
			wm.Change_EmployeeInfo();
			break;
		case 5: // ����Ա����Ϣ
			wm.Find_Employee();
			break;
		case 6: // Ա���������
			wm.Sort_Employee();
			break;
		case 7: // ����ļ�
			wm.Clean_File();
			break;
		default:
			system("cls");
			break;
		}
	}
	
	// 

	

	return 0;
}