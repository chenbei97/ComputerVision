#include  "Student.h"
#include "computer.h"
#include "GlobalFile.h"
#include "OrderFile.h"
Student::Student()
{
}
Student::Student(int id, string username, string password)
{
	this->student_id = id;
	this->_password = password;
	this->_username = username;
	 // 初始化机房信息添加到学生电脑容器studentComputer
	ifstream ifs;
	ifs.open(Computer_File , ios ::in);
	
	Computer computer;
	while (ifs >> computer.computer_id && ifs >> computer.computer_room_size)
	{
		studentComputer.push_back(computer);
	}
	ifs.close();
}

void  Student::operateMenu()
{
	cout << "欢迎学生代表" << this->_username << "登录！" << endl;
	cout << "\t\t ----------------------------------------------------\n";
	cout << "\t\t|                                                    |\n";
	cout << "\t\t|                 1. 申请预约                        |\n";
	cout << "\t\t|                                                    |\n";
	cout << "\t\t|                 2. 查看我的预约                    |\n";
	cout << "\t\t|                                                    |\n";
	cout << "\t\t|                 3. 查看所有预约                    |\n";
	cout << "\t\t|                                                    |\n";
	cout << "\t\t|                 4. 取消预约                        |\n";
	cout << "\t\t|                                                    |\n";
	cout << "\t\t|                 0. 注销登录                        |\n";
	cout << "\t\t|                                                    |\n";
	cout << "\t\t ----------------------------------------------------\n";
	cout << "请输入您的选择" << endl;

}

void Student::applyOrder()
{
	// 选择日期：周一到周五
	cout << "机房开放时间为周一到周五！" << endl;
	cout << "请输入申请预约的时间：" << endl;
	cout << "1、周一！" << endl;
	cout << "2、周二！" << endl;
	cout << "3、周三！" << endl;
	cout << "4、周四！" << endl;
	cout << "5、周五！" << endl;
	int date = 0;
	int interval = 0;
	int room = 0;
	// 选择时段：上午/下午
	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "输入有误，请重新输入！" << endl;
	}
	cout << "请输入申请预约的时间段：" << endl;
	cout << "1、上午" << endl;
	cout << "2、下午" << endl;
	while (true)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		cout << "输入有误，请重新输入！" << endl;
	}
	//选择机房：1、2、3号
	// 这里 studentComputer是3行句子，在16行代码中初始化时按行push_back的
	cout << "请选择机房：" << endl;
	for (int i = 0; i < studentComputer.size(); i++)
	{
		cout << studentComputer[i].computer_id << "号机房容量为：" << studentComputer[i].computer_room_size << endl;
	}
	//cout << "1号房容量为：" << studentComputer[0].computer_room_size<< endl;
	//cout << "2号房容量为：" << studentComputer[1].computer_room_size<<endl;
	//cout << "3号房容量为：" << studentComputer[2].computer_room_size<<endl;
	while (true)
	{
		cin >> room;
		if (room >= 1 && room <= 3)
		{
			break;
		}
		cout << "输入有误，请重新输入！" << endl;
	}
	cout << "预约成功！正在审核中" << endl;
	// 生成记录-->order.txt
	string datename;
	if (date == 1)
	{
		datename = "周一";
	}
	else if (date == 2)
	{
		datename = "周二";
	}
	else if (date == 3)
	{
		datename = "周三";
	}
	else if (date == 4)
	{
		datename = "周四";
	}
	else 
	{
		datename = "周五";
	}
	string intervalname;
	if (interval == 1)
	{
		intervalname = "上午";
	}
	else
	{
		intervalname = "下午";
	}
	string roomname;
	if (room == 1)
	{
		roomname = "一号机房";
	}
	else if (room == 2)
	{
		roomname = "二号机房";
	}
	else
	{
		roomname = "三号机房";
	}
	string statusname;
	if (this->order_status == 0)
	{
		statusname = "预约取消";
	}
	else if (this->order_status == 1)
	{
		statusname = "预约审核中";
	}
	else if (this->order_status == 2)
	{
		statusname = "预约成功";
	}
	else
	{
		statusname = "预约失败";
	}
	ofstream ofs(Order_File, ios::app);
	ofs << endl; //先换行再追加写入
	ofs << "预约日期:" << datename << " ";
	ofs << "预约时段:" << intervalname << " ";
	ofs << "学生学号:" << this->student_id << " ";
	ofs << "学生姓名:" << this->_username << " ";
	ofs << "预约房号:" << roomname << " ";
	ofs << "预约状态:" <<statusname << endl;
	// 0 取消的预约 1 审核中 2 已预约 -1 预约失败
	ofs.close();
	system("pause");
	system("cls");
}
void Student::showMyOrder()
{
	OrderFile of;
	if (of.OrderNum == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	int index = 1;
	for (int i = 0; i < of.OrderNum; i++)
	{
		// c_str()转换成const char*  , atoi将const char*转换成int  这样int可以跟学号比较
		if (atoi(of.mapOrderFile[i]["学生学号"].c_str()) == this->student_id)
		{
			cout << "第" << index<< "条预约记录信息：" << endl;
			cout << "\t预约日期：" << of.mapOrderFile[i]["预约日期"]<<endl;
			cout << "\t预约时段：" << of.mapOrderFile[i]["预约时段"]<<endl;
			cout << "\t预约房号：" << of.mapOrderFile[i]["预约房号"]<<endl;
			cout << "\t预约状态：" << of.mapOrderFile[i]["预约状态"]<<endl;
			index++;
		}
	}
	system("pause");
	system("cls");
}
void Student::showAllOrder()
{
	OrderFile of;
	if (of.OrderNum == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.OrderNum; i++)
	{
		cout << "第"<<i + 1 << "条预约记录信息："<<endl;
		cout << "\t学生姓名：" << of.mapOrderFile[i]["学生姓名"] << endl;
		cout << "\t预约日期：" << of.mapOrderFile[i]["预约日期"]<<endl;
		cout << "\t预约时段：" << of.mapOrderFile[i]["预约时段"]<<endl;
		cout << "\t预约房号：" << of.mapOrderFile[i]["预约房号"]<<endl;
		cout << "\t预约状态：" << of.mapOrderFile[i]["预约状态"]<<endl;

	}
	system("pause");
	system("cls");
}
void Student::cancelOrder()
{
	OrderFile of;
	if (of.OrderNum == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	//cout << "审核中或者预约成功的记录可以取消，其信息如下所示：" << endl;
	vector <int> v;
	int num = 0; // 记录当前学生一共有多少条预约记录
	for (int i = 0; i < of.OrderNum; i++)
	{
		if (atoi(of.mapOrderFile[i]["学生学号"].c_str()) == this->student_id)
		{
			num++;
		}
	}
	cout << this->_username <<"的预约记录有" <<num <<"条"<< endl;
	for (int i = 0; i < of.OrderNum; i++)
	{
		if (atoi(of.mapOrderFile[i]["学生学号"].c_str()) == this->student_id)
		{
			if (of.mapOrderFile[i]["预约状态"] == "预约成功" || of.mapOrderFile[i]["预约状态"] == "审核中")
			{
				v.push_back(i); // 记录被取消记录的条数

				cout << "第" << i + 1 << "条预约信息：" << endl; // 实际的位置
				cout << "\t学生姓名：" << of.mapOrderFile[i]["学生姓名"] << endl;
				cout << "\t预约日期：" << of.mapOrderFile[i]["预约日期"] << endl;
				cout << "\t预约时段：" << of.mapOrderFile[i]["预约时段"] << endl;
				cout << "\t预约房号：" << of.mapOrderFile[i]["预约房号"] << endl;
				cout << "\t预约状态：" << of.mapOrderFile[i]["预约状态"] << endl;
			}
		}
	}
	// 经过上述操作得到了对应某个学生的审核中或者预约成功的所有信息
	if (v.size() == 0)
	{
		cout << this->_username << "可取消的预约记录有0条" << endl;
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
			cin >> select;
			if (select >= 0 && select <= num)
			{
				if (select == 0)
				{
					break;
				}
				else
				{
					of.mapOrderFile[select - 1]["预约状态"] = "预约取消";
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
