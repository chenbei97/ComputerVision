#pragma once
#include "GlobalFile.h"
#include "Student.h" //必须单独包含头文件
#include "Teacher.h"//必须单独包含头文件
#include "computer.h" //必须单独包含头文件
#include "Manager.h"//必须单独包含头文件
class Manager  : public Identity
{
public:
	
	//存放学生和老师的容器--->去重和初始化容器函数使用
	vector<Student> vectorStudent;
	vector<Teacher> vectorTeacher;

	// 存放机房的信息--->查看机房信息函数使用，初始化构造函数也使用
	vector<Computer> vectorComputer;
	
	//读取历史记录函数--->放入容器
	void initVector();

	//去重函数---->在创建账号函数中调用
	bool checkRepeat(int id ,int type);//type决定是老师or学生


	// 默认构造
	Manager();

	//有参构造
	Manager(string username, string password);
	

	/*外部的全局函数managerMenu决定了调用下方哪些函数*/
	/*manager.cpp定义的函数都通过实例化对象account传入给managerMenu函数*/
	// 菜单界面
	virtual void operateMenu();

	// 添加账号
	void addAccount();

	// 查看账号
	void showAccount();

	// 查看机房信息
	void showComputerInfo();

	// 清空预约记录
	void clearFileInfo();


};