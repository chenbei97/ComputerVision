//�����������
#pragma once // ��ֹͷ�ļ��ظ�����
#include <iostream>
#include "Worker_Individual.h"
#include "Boss.h" 
#include "Worker_Employee.h" 
#include "Worker_Manager.h" 
#include <fstream>
#define FileName "emFile.txt"
using namespace std;
// ͷ�ļ���ֻ���� ��д�����ʵ��
class workerSystem
{
public:
	int _employeeNum; // ��¼��Ӻ��Ա������
	int _historyNum;
	workerIndividual ** _employeeArray;//����Ա�������ָ���ָ��
	bool _fileisEmpty; // ��ֵ�洢�ļ���״̬ �Ƿ�������� û�����ݲ���ʾ
	workerSystem();
	~workerSystem();

	void Show_Menu(); // չʾ�˵�
	void Add_Emp();//���ְ��
	void Save(); // ��������
	int getHistoryWorkerNum(); // ���ļ����ڲ�Ϊ��ʱͳ����ʷְ������
	void initemployeeArray(); //��ʼ����ʷְ����Ϣ
	void Show_Employee(); // ��ӡְ����Ϣ
	int IsExist_Employee(int id); // �ж�ĳ��Ա��id�Ƿ����
	void Del_Employee(); // ɾ��Ա����Ϣ
	void Change_EmployeeInfo();// ����Ա����Ϣ
	void Find_Employee(); // ����ĳ��Ա����Ϣ
	void Sort_Employee();// Ա���������
	void Clean_File(); // ����ļ�
	void ExitSystem(); // �˳�ϵͳ

};
