//管理类的声明
#pragma once // 防止头文件重复包含
#include <iostream>
#include "Worker_Individual.h"
#include "Boss.h" 
#include "Worker_Employee.h" 
#include "Worker_Manager.h" 
#include <fstream>
#define FileName "emFile.txt"
using namespace std;
// 头文件中只声明 不写具体的实现
class workerSystem
{
public:
	int _employeeNum; // 记录添加后的员工个数
	int _historyNum;
	workerIndividual ** _employeeArray;//保存员工数组的指针的指针
	bool _fileisEmpty; // 标值存储文件的状态 是否存在数据 没有数据不显示
	workerSystem();
	~workerSystem();

	void Show_Menu(); // 展示菜单
	void Add_Emp();//添加职工
	void Save(); // 保存数据
	int getHistoryWorkerNum(); // 在文件存在不为空时统计历史职工人数
	void initemployeeArray(); //初始化历史职工信息
	void Show_Employee(); // 打印职工信息
	int IsExist_Employee(int id); // 判断某个员工id是否存在
	void Del_Employee(); // 删除员工信息
	void Change_EmployeeInfo();// 更改员工信息
	void Find_Employee(); // 查找某个员工信息
	void Sort_Employee();// 员工编号排序
	void Clean_File(); // 清空文件
	void ExitSystem(); // 退出系统

};
