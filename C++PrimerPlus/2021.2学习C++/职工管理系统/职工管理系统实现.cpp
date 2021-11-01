#include <iostream>
using namespace std;
#include "Worker_System.h"
#include "Worker_Employee.h"// 内部已经包含了员工抽象类的头文件 
#include "Worker_Manager.h"
#include "Boss.h"
void test_employee_manager_boss()
{
	worker_Employee * employee = NULL; // 必须指针创建普通员工子类才能调用父类重写
	employee = new worker_Employee(1,"张三员工",10);
	employee->showInfo();
	delete employee;
	worker_Manager* manager = new worker_Manager(2, "李四经理", 20);
	manager->showInfo();
	delete manager;
	boss* bos = new boss(3, "王五老板", 30);
	bos->showInfo();
	delete bos;
}
int main()
{
	workerSystem wm;
	//test_employee_manager_boss(); // 测试员工类
	
	int choice = 0;
	while (true)
	{
		wm.Show_Menu();// 菜单功能
		cout << "请输入您的选择" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0 : //退出系统
			wm.ExitSystem();
			 break;
		case 1:  // 添加员工
			wm.Add_Emp();
			break;
		case 2: // 展示员工信息
			wm.Show_Employee();
			break;
		case 3: // 删除员工
			wm.Del_Employee();
			break;
		case 4:// 修改员工信息
			wm.Change_EmployeeInfo();
			break;
		case 5: // 查找员工信息
			wm.Find_Employee();
			break;
		case 6: // 员工编号排序
			wm.Sort_Employee();
			break;
		case 7: // 清空文件
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