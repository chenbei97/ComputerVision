#include"Teacher.h"
// 教师类：菜单界面(多态)、查看所有预约、审核预约
Teacher::Teacher()
{
}
Teacher::Teacher(int  id, string username, string password)
{
	this->_password = password;
	this->_username = username;
	this->teacher_id = id; 
}
void Teacher::operateMenu()
{
	cout << "欢迎老师代表" << this->_username << "登录！" << endl;
	cout << "\t\t ----------------------------------------------------\n";
	cout << "\t\t|                                                    |\n";
	cout << "\t\t|                 1. 查看预约                        |\n";
	cout << "\t\t|                                                    |\n";
	cout << "\t\t|                 2. 审核预约                        |\n";
	cout << "\t\t|                                                    |\n";
	cout << "\t\t|                 0. 注销登录                        |\n";
	cout << "\t\t|                                                    |\n";
	cout << "\t\t ----------------------------------------------------\n";
	cout << "请输入您的选择" << endl;
}
void Teacher::showAllOrder()
{
	OrderFile of;
	if (of.OrderNum== 0)
	{
		cout << "没有预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.OrderNum; i++)
	{
		cout << "第" << i + 1 << "条预约记录信息：" << endl;
		cout << "\t学生姓名：" << of.mapOrderFile[i]["学生姓名"] << endl;
		cout << "\t预约日期：" << of.mapOrderFile[i]["预约日期"] << endl;
		cout << "\t预约时段：" << of.mapOrderFile[i]["预约时段"] << endl;
		cout << "\t预约房号：" << of.mapOrderFile[i]["预约房号"] << endl;
		cout << "\t预约状态：" << of.mapOrderFile[i]["预约状态"] << endl;
	}
}

void Teacher::examineOrder()
{
	OrderFile of;
	if (of.OrderNum == 0)
	{
		cout << "没有预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "待审核的预约如下所示：" << endl;
	vector <int> v;
	for (int i = 0; i < of.OrderNum; i++)
	{
		if ( of.mapOrderFile[i]["预约状态"] == "审核中")
		{
			v.push_back(i); // 记录待审核的条数

			cout << "第" << i + 1 << "条预约信息：" << endl; // 实际的位置
			cout << "\t学生姓名：" << of.mapOrderFile[i]["学生姓名"] << endl;
			cout << "\t预约日期：" << of.mapOrderFile[i]["预约日期"] << endl;
			cout << "\t预约时段：" << of.mapOrderFile[i]["预约时段"] << endl;
			cout << "\t预约房号：" << of.mapOrderFile[i]["预约房号"] << endl;
			cout << "\t预约状态：" << of.mapOrderFile[i]["预约状态"] << endl;
		}
	}
	// 经过上述操作得到了可以审核的所有信息
	if (v.size() == 0)
	{
		cout  << "可审核的预约记录有0条" << endl;
		return;
	}
	else
	{
		cout << "请输入取消的记录编号(数字编号限于以下数字)：" << endl;
		for (vector<int> ::iterator it = v.begin(); it != v.end(); it++)
		{
			cout << "第" << *it + 1 << "条" << endl; // 验证输出的位置 = 0、1、4
		}
		int select = 0;
		while (true)
		{
			// 选择了审核哪条
			cin >> select; // 学生类是因为要统计自己的预约记录 而老师只需要告诉所有审核的总数目即可
			if (select >= 0 && select <= of.OrderNum + 1)// 必须在信息条数以内
			{
				if (select == 0)
				{
					break;
				}
				else
				{
					cout << "请输入审核结果：" << endl;
					cout << "1、通过" << endl;
					cout << "2、不通过" << endl;
					int sel;
					cin >> sel;
					string statusName;
					if (sel == 1)
					{
						statusName = "预约成功";
					}
					else if (sel == 2)
					{
						statusName = "预约失败";
					}
					else
					{
						cout << "输入错误，请重新输入！" << endl;
					}
					of.mapOrderFile[select - 1]["预约状态"] = statusName;
					of.updateOrder();
					cout << "预约取消成功" << endl;
					break;
				}
			}
			else
			{
				cout << "输入有误，请重新输入！" << endl;
			}
		}
	}
	system("pause");
	system("cls");
}