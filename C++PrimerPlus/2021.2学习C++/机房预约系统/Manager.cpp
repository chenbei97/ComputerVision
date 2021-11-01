#include "Manager.h"
#include "GlobalFile.h"
#include "computer.h"
Manager ::Manager()
{
	
}
Manager:: Manager(string username, string password)
{
	this->_password = password;
	this->_username = username;
	this->initVector();
	 // 这里没封装机房函数 initComputer()
	ifstream ifs;
	ifs.open(Computer_File , ios::in);
	Computer computer;
	while (ifs >> computer.computer_id && ifs >> computer.computer_room_size)
	{
		vectorComputer.push_back(computer);
	}
	cout << "当前机房的数量为：" <<vectorComputer.size()<< endl;
	ifs.close();
}
void Manager::operateMenu()
{
	cout << "欢迎管理员" <<this->_username <<"登录！"<< endl;
	cout << "\t\t ----------------------------------------------------\n";
	cout << "\t\t|                                                    |\n";
	cout << "\t\t|                 1. 添加账号                        |\n";
	cout << "\t\t|                                                    |\n";
	cout << "\t\t|                 2. 查看账号                        |\n";
	cout << "\t\t|                                                    |\n";
	cout << "\t\t|                 3. 查看机房                        |\n";
	cout << "\t\t|                                                    |\n";
	cout << "\t\t|                 4. 清空预约                        |\n";
	cout << "\t\t|                                                    |\n";
	cout << "\t\t|                 0. 注销登录                        |\n";
	cout << "\t\t|                                                    |\n";
	cout << "\t\t ----------------------------------------------------\n";
	cout << "请输入您的选择"<<endl;
}
void Manager::initVector()
{
	this->vectorStudent.clear();
	this->vectorTeacher.clear();
	//用于将两个文件的历史数据读入容器 然后后续进行比较是否重复
	ifstream ifs;
	ifs.open(Student_File, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
		return ;
	}
	Student stemp;
	while (ifs >> stemp.student_id && ifs >> stemp._username
		&& ifs >> stemp._password)
	{
		this->vectorStudent.push_back(stemp);
	}
	//cout << "当前学生账号的数量为：" <<vectorStudent.size()<< endl;
	ifs.close();


	ifs.open(Teacher_File, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
		return;
	}
	Teacher T;
	while (ifs >> T.teacher_id && ifs >> T._username
		&& ifs >> T._password)
	{
		this->vectorTeacher.push_back(T);
	}
	//cout << "当前老师账号的数量为：" << vectorTeacher.size() << endl;
	ifs.close();
}
bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		// 遍历学生容器
		for (vector<Student> ::iterator it = vectorStudent.begin(); it != vectorStudent.end(); it++)
		{
			if (id == it->student_id)
			{
				return true;// 相等说明有重复
			}
		}
	}
	else 
	{
		for (vector<Teacher> ::iterator it1 = vectorTeacher.begin(); it1 != vectorTeacher.end(); it1++)
		{
			if (id == it1->teacher_id)
			{
				return true;
			}
		}
	}
	return false;
}
void Manager::addAccount()
{
	// 向2个txt文件写入账号信息
	cout << "请输入添加账号的类型："<<endl;
	cout << "1、添加学生" << endl;
	cout << "2、添加老师" << endl;
	string filename; 
	string tip;
	string errorTip;
	ofstream ofs;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		filename = Student_File;
		tip = "请输入学号：";
		errorTip = "学号重复，请重新输入！";
	}
	else
	{
		filename = Teacher_File;
		tip = "请输入工号：";
		errorTip = "工号重复，请重新输入！";
	}
	ofs.open(filename, ios::out | ios::app);
	ofs << endl;
	int  id;
	string username;
	string password;
	cout << tip << endl;
	while (true)
	{
		cin >> id;
		bool ret = this->checkRepeat(id,select);
		if (ret)
		{
			cout << errorTip << endl;
		}
		else { break; }
	}
	cout << "请输入用户名：" << endl;
	cin >> username;
	cout << "请输入密码：" << endl;
	cin >> password;
	ofs << id << " " << username << " " << password <<  " ";
	cout << "添加账号成功" << endl;
	
	system("pause");
	system("cls");
	ofs.close();
	this->initVector();// 重复读取文件内容更新
	//必须要及时更新容器 否则下次添加账号时检测不出重复
}
void printStudent(Student &s)
{
	// 普通函数作为迭代函数
	cout << "学号：" << s.student_id << "\t" << "用户名：" <<
		s._username << "\t" << "密码：" << s._password << endl;
}
void printTeacher(Teacher& s)
{
	// 普通函数作为迭代函数
	cout << "学号：" << s.teacher_id << "\t" << "用户名：" <<
		s._username << "\t" << "密码：" << s._password << endl;
}
void Manager::showAccount()
{
	cout << "请选择查看的账号类型：" << endl;
	cout << "1、查看所有学生" << endl;
	cout << "2、查看所有老师" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		cout << "所有学生账户的信息如下：" << endl;
		for_each(vectorStudent.begin(),vectorStudent.end(),printStudent);
	}
	else
	{
		cout << "所有老师账户的信息如下：" << endl;
		for_each(vectorTeacher.begin(), vectorTeacher.end(), printTeacher);
	}
	system("pause");
	system("cls");
}
void Manager::showComputerInfo()
{
	cout << "机房的信息如下：" << endl;
	for (vector<Computer> ::iterator it = vectorComputer.begin(); it != vectorComputer.end(); it++)
	{
		cout << "机房编号为：" <<it->computer_id<<"\t"
			<<"机房最大容量为："<<it->computer_room_size<< endl;
	}
	system("pause");
	system("cls");
}
void Manager::clearFileInfo()
{
	ofstream ofs(Order_File, ios::trunc);
	ofs.close();
	cout << "清空成功！" << endl;
	system("pause");
	system("cls");
}
