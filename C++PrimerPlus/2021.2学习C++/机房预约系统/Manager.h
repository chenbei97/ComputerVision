#pragma once
#include "GlobalFile.h"
#include "Student.h" //���뵥������ͷ�ļ�
#include "Teacher.h"//���뵥������ͷ�ļ�
#include "computer.h" //���뵥������ͷ�ļ�
#include "Manager.h"//���뵥������ͷ�ļ�
class Manager  : public Identity
{
public:
	
	//���ѧ������ʦ������--->ȥ�غͳ�ʼ����������ʹ��
	vector<Student> vectorStudent;
	vector<Teacher> vectorTeacher;

	// ��Ż�������Ϣ--->�鿴������Ϣ����ʹ�ã���ʼ�����캯��Ҳʹ��
	vector<Computer> vectorComputer;
	
	//��ȡ��ʷ��¼����--->��������
	void initVector();

	//ȥ�غ���---->�ڴ����˺ź����е���
	bool checkRepeat(int id ,int type);//type��������ʦorѧ��


	// Ĭ�Ϲ���
	Manager();

	//�вι���
	Manager(string username, string password);
	

	/*�ⲿ��ȫ�ֺ���managerMenu�����˵����·���Щ����*/
	/*manager.cpp����ĺ�����ͨ��ʵ��������account�����managerMenu����*/
	// �˵�����
	virtual void operateMenu();

	// ����˺�
	void addAccount();

	// �鿴�˺�
	void showAccount();

	// �鿴������Ϣ
	void showComputerInfo();

	// ���ԤԼ��¼
	void clearFileInfo();


};