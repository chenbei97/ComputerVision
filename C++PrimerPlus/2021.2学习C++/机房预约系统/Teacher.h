#pragma once
#include "Identity.h"
#include "OrderFile.h"
class Teacher : public Identity
{
public:
	// ��ʦ���е�����
	int teacher_id;
	// Ĭ�Ϲ���
	Teacher();

	// �вι���
	Teacher(int  id, string username, string password);

	// �˵�����
	virtual void operateMenu();

	// �鿴����ԤԼ
	void showAllOrder();

	// ���ԤԼ
	void examineOrder();
};
