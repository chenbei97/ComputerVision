#pragma once
#include "Identity.h"
#include "OrderFile.h"
class Teacher : public Identity
{
public:
	// 老师具有的属性
	int teacher_id;
	// 默认构造
	Teacher();

	// 有参构造
	Teacher(int  id, string username, string password);

	// 菜单界面
	virtual void operateMenu();

	// 查看所有预约
	void showAllOrder();

	// 审核预约
	void examineOrder();
};
