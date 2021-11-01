/*
1.该系统有3种身份可以使用
		学生代表：申请使用机房
		教师：审核学生的预约申请
		管理员：给学生、教师创建账号
2.机房共有三间
		1号机房：最大容量20人
		2号机房：最大容量50人
		3号机房：最大容量100人
3.申请的订单由管理员负责清空
4.学生可以预约未来一周的机房使用 预约日期周一到周五 预约需要选择时段(上午、下午)
5.具体需求：
		学生代表：输入学号、姓名、登陆密码
							功能：
									申请预约
									查看自身预约
									查看所有预约
									取消预约
									退出登录
		老师：职工号、姓名、登陆密码
							功能：
									查看所有预约
									对学生预约进行审核
									退出登录
		管理员：管理员姓名、登陆密码
							功能：
									添加账号，需要检测学生编号和老师职工号是否重复
									查看账号全部信息
									查看机房信息
									清空预约
									退出登录
		退出：退出当前程序
6.预约状态：审核中、预约成功、预约失败、取消的预约
7.机房信息：机房编号、最大容量
*/
#include "GlobalFile.h"
#include "Student.h" //必须单独包含头文件
#include "Teacher.h"//必须单独包含头文件
#include "computer.h" //必须单独包含头文件
#include "Manager.h"//必须单独包含头文件
void managerMenu(Identity* &manager)
{
	// 管理员菜单  
	// 调用了操作菜单、添加账号、查看账号、查看机房信息、清空预约记录函数
	// 此函数位置放在主函数 参数为指向抽象类引用的指针 传入的参数为account 
	while (true)
	{
		// 管理员菜单
		manager->operateMenu();
		Manager* man = (Manager*)manager; //父类指针强转为管理类指针
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			// 添加账号
			//cout << "添加账号成功！" << endl;
			man->addAccount();
		}
		else if (select == 2)
		{
			//cout << "正在查看账号" << endl;
			man->showAccount();
		}
		else if (select == 3)
		{
			//cout << "正在查看机房信息" << endl;
			man->showComputerInfo();
		}
		else if (select == 4)
		{
			//cout << "清空预约成功！" << endl;
			man->clearFileInfo();
		}
		else
		{
			delete manager;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}

	}
}
void studentMenu(Identity*& student)
{
	// 学生菜单  
	// 此函数位置放在主函数 参数为指向抽象类引用的指针 传入的参数为account 
	while (true)
	{
		// 学生菜单
		student->operateMenu();
		Student* man = (Student*)student; //父类指针强转为学生类指针
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			// 申请预约
			man->applyOrder();
		}
		else if (select == 2)
		{
			// 显示我的预约
			man->showMyOrder();
		}
		else if (select == 3)
		{
			// 显示所有预约
			man->showAllOrder();
		}
		else if (select == 4)
		{
			//取消预约
			man->cancelOrder();
		}
		else
		{
			delete  student;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
void teacherMenu(Identity*& teacher)
{
	// 教师菜单  
	// 此函数位置放在主函数 参数为指向抽象类引用的指针 传入的参数为account 
	while (true)
	{
		// 教师菜单
		teacher->operateMenu();
		Teacher* man = (Teacher*)teacher; //父类指针强转为教师类指针
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			// 查看预约
			man->showAllOrder();
		}
		else if (select == 2)
		{
			// 审核预约
			man->examineOrder();
		}
		else
		{
			delete   teacher;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}
void LoginIn(string filename, int type)
{
	Identity* account = NULL;
	ifstream ifs;
	ifs.open(filename, ios::in);
	// 文件不存在
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	int id = 0;
	string username;
	string password;
	if (type == 1)
	{
		cout << "请输入你的学号：" << endl;
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "请输入你的工号：" << endl;
		cin >> id;
	}
	// 默认执行管理员界面
	cout << "请输入用户名：" << endl;
	cin >> username;
	cout << "请输入密码：" << endl;
	cin >> password;

	// 登陆验证
	if (type == 1)
	{
		int student_id;
		string student_username;
		string student_password;
		while (ifs >> student_id && ifs >> student_username && ifs >> student_password)
		{
			if (id == student_id && username == student_username && student_password == password)
			{
				//cout << student_id << endl;
				//cout << student_password << endl;
				//cout << student_username << endl;
				cout << "学生验证登陆成功" << endl;
				system("pause");
				system("cls");
				account = new Student(id, username, password);
				// 进入学生身份子菜单
				studentMenu(account);
				return;
			}
		}
	}
	else if (type == 2)
	{
		int teacher_id;
		string teacher_username;
		string  teacher_password;
		while (ifs >> teacher_id && ifs >> teacher_username && ifs >> teacher_password)
		{
			if (id == teacher_id && username == teacher_username && teacher_password == password)
			{
				//cout << teacher_id << endl;
				//cout << teacher_password << endl;
				//cout << teacher_username << endl;
				cout << "老师验证登陆成功" << endl;
				system("pause");
				system("cls");
				account = new Teacher(id, username, password);
				// 进入老师身份子菜单
				teacherMenu(account);
				return;
			}
		}
	}
	else if (type == 3)
	{
		string admin_username;
		string  admin_password;
		while (  ifs >> admin_username && ifs >> admin_password)
		{
			if ( username == admin_username && admin_password == password)
			{
				//cout << admin_password << endl;
				//cout << admin_username << endl;
				cout << "管理员验证登陆成功" << endl;
				system("pause");
				system("cls");
				account = new Manager(username, password);
				// 进入管理员身份子菜单
				managerMenu(account);
				return;
			}
		}
	}
	cout << "登陆验证失败！" << endl;
	system("pause");
	system("cls"); 
	return;
}
int main()
{
	int select = 0;
	while (true)
	{

		cout << "====================  欢迎来到超级赛亚人机房预约系统  ==================== " << endl;
		cout << endl << "请输入您的身份" << endl;
		cout << "\t\t ----------------------------------------------------\n";
		cout << "\t\t|                                                    |\n";
		cout << "\t\t|                 1. 学生代表                        |\n";
		cout << "\t\t|                                                    |\n";
		cout << "\t\t|                 2. 老    师                        |\n";
		cout << "\t\t|                                                    |\n";
		cout << "\t\t|                 3. 管理人员                        |\n";
		cout << "\t\t|                                                    |\n";
		cout << "\t\t|                 0. 退    出                        |\n";
		cout << "\t\t|                                                    |\n";
		cout << "\t\t ----------------------------------------------------\n";
		cout << "请输入您的选择";
		cin  >> select;
		switch (select)
		{
		case 1:
			LoginIn(Student_File, 1);
			break;
		case 2:
			LoginIn(Teacher_File, 2);
			break;
		case 3:
			LoginIn(Admin_File, 3);
			break;
		case 0:
			cout << "欢迎下次使用~" << endl;
			system("pause");
			system("cls");
			return 0;

			break;
		default:
			cout << "输入有误，请重新选择！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	return 0;
}