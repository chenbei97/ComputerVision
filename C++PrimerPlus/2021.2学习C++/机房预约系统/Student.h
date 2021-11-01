#pragma once
#include "Identity.h"
#include "computer.h"
#include "Teacher.h"
#include "GlobalFile.h" 
#include <vector>
//ѧ���๦�ܣ�
// ��ʾ��������(��̬operateMenu)
// ����ԤԼ���鿴ԤԼ���鿴����ԤԼ��ȡ��ԤԼ(ѧ������¹���)

class Student : public Identity
{
public:
	// ѧ�����е����� ѧ��
	int student_id;

	// ԤԼ��Ҫ��������--->��ԤԼ�������� ԤԼ�ĸ�����
	vector<Computer> studentComputer;

	// ԤԼ״̬���� // 0 ȡ����ԤԼ 1 ����� 2 ��ԤԼ -1 ԤԼʧ��
	// ��teacher�����ı�
	int order_status = 1;
	// Ĭ�Ϲ���
	Student();

	// �вι���(ѧ�š�����������)
	Student(int id, string username, string password);

	// �˵�����(��̬)
	virtual void operateMenu();

	// ����ԤԼ
	void applyOrder();

	// �鿴�ҵ�ԤԼ
	void showMyOrder();

	// �鿴����ԤԼ
	void showAllOrder();

	// ȡ��ԤԼ
	void cancelOrder();
};