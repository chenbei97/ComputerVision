#pragma once
#include "Identity.h"
#include "computer.h"
#include "Teacher.h"
#include "GlobalFile.h" 
#include <vector>
//学生类功能：
// 显示操作界面(多态operateMenu)
// 申请预约、查看预约、查看所有预约、取消预约(学生类的新功能)

class Student : public Identity
{
public:
	// 学生自有的属性 学号
	int student_id;

	// 预约需要机房容器--->被预约函数调用 预约哪个机房
	vector<Computer> studentComputer;

	// 预约状态控制 // 0 取消的预约 1 审核中 2 已预约 -1 预约失败
	// 在teacher类对其改变
	int order_status = 1;
	// 默认构造
	Student();

	// 有参构造(学号、姓名、密码)
	Student(int id, string username, string password);

	// 菜单界面(多态)
	virtual void operateMenu();

	// 申请预约
	void applyOrder();

	// 查看我的预约
	void showMyOrder();

	// 查看所有预约
	void showAllOrder();

	// 取消预约
	void cancelOrder();
};