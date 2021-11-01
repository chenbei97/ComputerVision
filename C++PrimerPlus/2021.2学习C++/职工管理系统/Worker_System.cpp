#include "Worker_System.h"
#include "Worker_Individual.h"
#include <string>
#include <stdlib.h>
// 管理类的实现
// 头文件写好声明后 对于析构和构造函数 加作用域即可
// 对函数而言还需要返回类型写在前头
workerSystem::workerSystem()
{
	// 修改构造函数 不是简单的初始化人数 重而是根据文件数据新构造
	//// 初始化人数
	//this->_employeeNum = 0;
	//this->_employeeArray = { 0 };

	// 文件不存在的情况依据下方程序构造
	ifstream ifs;
	ifs.open(FileName, ios::in);
	if ( ! ifs.is_open())
	{
		cout << "文件不存在" << endl;
		this->_employeeNum = 0;
		this->_employeeArray = NULL;
		this->_fileisEmpty = true; // 文件为空
		ifs.close();
		return ;
	}
	
	//文件存在但是数据为空
	char ch;
	ifs >> ch; // 读一个字符
	if (ifs.eof()) // 读到了文件的尾部位置
	{
		cout << "文件为空！"<<endl;
		this->_employeeArray = NULL;
		this->_employeeNum = 0;
		this->_fileisEmpty = true;
		ifs.close();
		return ;
	}
	ifs.close();
	//文件存在且有历史数据 之前的数据都是_employeeArray = NULL;所以需要给出新内存
	 //统计历史员工人数 
	int historynum = this->getHistoryWorkerNum(); // 同时更新内存数组大小
	this->_employeeNum = historynum; 
	cout << "历史职工人数为" << historynum << "名" << endl;
	this->_employeeArray = new workerIndividual *[ this->_employeeNum];//更新内存大小
	// //定义初始化函数 void initemployeeArray();即把历史职工信息传给_employeeArray;
	this->initemployeeArray(); //_employeeArray存储完毕历史信息
}
workerSystem :: ~workerSystem()
{
		if (this->_employeeArray != NULL)
		{
			delete[]  this->_employeeArray;
			this->_employeeArray = NULL;
		}
}
void workerSystem::Show_Menu() // 类外声明
{
	cout << "*************************************************" << endl;
	cout << "***********   欢迎使用职工管理系统!    **********" << endl;
	cout << "***********      0. 退出管理程序       **********" << endl;
	cout << "***********      1. 增加职工信息       **********" << endl;
	cout << "***********      2. 显示职工信息       **********" << endl;
	cout << "***********      3. 删除离职职工       **********" << endl;
	cout << "***********      4. 修改职工信息       **********" << endl;
	cout << "***********      5. 查找职工信息       **********" << endl;
	cout << "***********      6. 按照编号排序       **********" << endl;
	cout << "***********      7. 清空所有信息       **********" << endl;
	cout << endl;
}
void workerSystem::Add_Emp()
/*
主要做的事情:
1.原本的系统类有一个员工人数和一个存放不同员工指针的指针 workerIndividual ** _employeeArray
2.此函数中开辟了一个新的指向系统类的存放员工指针的指针  workerIndividual** newspace 其大小是原有数目加上要添加新员工的数目
3.新空间newspace先把老员工留下(_employeeNum个) 再添加新员工(addNum个)
4. 添加新员工需要一些信息 ：  员工类(用dSelect=1,2,3代指)、姓名、编号
5. 特别的对于员工类的选择 需要一个临时的员工抽象类指针 workerIndividual* worker = NULL;
	之所以创建父类是没有实例化，然后根据dSelect的选择就可以确定子类员工、经理或老板(多态技术)
5. 以上这些信息都是用户输入的，输入完毕后需要存放到newspace 新员工的位置上
6. 现在所有的新数据都在newspace中所以可以释放掉管理类原有的_employeeArray
	即   delete[] this->_employeeArray;  删除的是数组指针 所以用delete[]
7. 更改newspace的指向 , 将这个新数据又给了_employeeArray
	this->_employeeArray = newspace;
*/
{
	cout << "请输入增加职工的数量 : " << endl;
	int addNum = 0;
	cin >> addNum;
	//if   (! isdigit( addNum) )
	//{    //不是数字返回0  那么判断为1
	//	cout << "输入的不是整型数字，请重新输入！" << endl;
	//	cin >> addNum;
	//}
	if (addNum > 0)
	{
		// 计算添加后的职工人数
		int newsize = this->_employeeNum + addNum;
		// 开辟空间
		workerIndividual** newspace = new workerIndividual * [newsize];
		// 将原空间的内容放到新空间
		// 把原来的老员工先拿出来给新空间
		if (this->_employeeArray != NULL)
		{
			for (int i = 0; i < this->_employeeNum; i++)
			{
				newspace[i] = this->_employeeArray[i];
			}
		}
		// 释放原有变量空间
		delete[] this->_employeeArray; 
		// 创建新数据放到第i+1以后
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;
			cout << "请输入第" << i + 1 << "个新员工编号" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个新员工姓名" << endl;
			cin >> name;
			cout << "请选择该职工的岗位：" << endl;
			cout << "1.普通员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelect;
			workerIndividual* worker = NULL; // 创建抽象类是希望根据dSelect的选择去实例化具体的员工类
			switch (dSelect)
			{
			case 1:
				worker = new  worker_Employee(id, name, dSelect);//使用worker配合子类去多态呈现抽象类
				//cout << "worker有" << sizeof(worker) << "个子节" << endl;
				break;
			case 2:
				worker = new worker_Manager(id, name, dSelect);
				//cout << "worker有" << sizeof(worker) << "个子节" << endl;
				break;
			case 3:
				worker = new boss(id, name, dSelect);
				//cout << "worker有" << sizeof(worker) << "个子节" << endl;
				break;
			default:
				break;
			}
			newspace[this->_employeeNum + i] = worker; //最终所有数据存放的地方 存放的是员工类的指针(地址)
		}

		// 更改newspace的指向 , 将这个新数据又给了_employeeArray
		this->_employeeArray = newspace;
		//更新新的职工人数
		this->_employeeNum = newsize;
		// 更新文件状态
		this->_fileisEmpty = false; //文件不为空
		// 存入文件 但是这里存在的问题是只能在运行时显示一共几名员工
		// 不能读取历史数据给出真正的职工人数
		// 这个需要交给读取文件的有关函数进行处理 即统计历史人员函数int getHistoryWorkerNum();
		this->Save();
	}
	else
		{
			cout << "输入添加员工数目有误，请重新输入！" << endl;
		}
     	system("cls");
		// 提示添加成功
		cout << "成功添加" << addNum << "名新员工信息！" << endl;
		cout << "当前公司一共有" << this->_employeeNum << "名新员工" << endl;
}
int workerSystem::getHistoryWorkerNum() // 统计历史职工人数
{
	ifstream ifs;
	ifs.open(FileName,ios::in);
	string ch;
	int num = 0; // 统计文件行数
	while (getline(ifs,ch,'\n')) //当读取的字符为换行时
	{
		// 遇到空格符换行
		num++;
		//cout << ch << endl; // 不打印每行内容
	}
	ifs.close();
	return num;
}
void workerSystem::initemployeeArray() //初始化历史职工信息
{
	ifstream  ifs;
	ifs.open(FileName, ios::in);
	string str;
	int index = 0; //记录加载历史数据的每一行 用于控制存放数组的位置
	while (getline(ifs, str, '\n'))
	{
			// str= "职工编号(空格)(：)(4)(tab)职工性格(空格)(：)(ccc)(tab)职工编号(空格)(：)(3)(tab)"" 中文2子节
			int arr1[3];
			int* p1 = arr1;
			int arr2[3];
			int* p2 = arr2;
			for (unsigned int j = 0; j < str.length();j++)
			{
				if (str[j] == ':')
				{
					*p1 = j + 1; //记录需要的字符串起始位置
					//continue; // 跳出第i次循环 执行第i+1次循环 遇到冒号就记录跳出循环
					p1++; // p记录了每个位置
					//cout << j + 1 << endl;//4 、c、3---->10、22、40   41是换行符
				}
				if (str[j] == '	')
				{
					*p2 = j;
					p2++; // 记录了tab的位置 11、25、()第三个没有
					//cout << j << endl;
				}
			}
			string id = str.substr(arr1[0], arr2[0] - arr1[0]); // id的字符串   substr(起始位置，截取的字符个数) =(10,11-10)
			string name = str.substr(arr1[1], arr2[1] - arr1[1]); // (22,25-22)
			string did = str.substr(arr1[2], str.length() - arr1[2]); //(40,41-40)
			int _id = stoi(id);  //字符串转整型
			int _did = stoi(did);
			 //到这里已经得到了某个职工的编号、名字、部门编号
			workerIndividual* worker = NULL; // 定义员工抽象类
			if (_did == 1)
			{
			   worker = new worker_Employee(_id, name, _did);
			}
			else if (_did == 2)
			{
				worker = new worker_Manager(_id,name,_did);
			}
			else 
			{
				worker = new boss(_id, name, _did); 
			}
		   // 这个循环结束是这行信息被分类好对应的worker
		   this->_employeeArray[index] = worker; // 根据当前行的位置
		   //cout << index << endl; // 0~41
		   index++; // 随着每读取一次递增
	}
	ifs.close();
}
void workerSystem :: Save()
{
	// 逐条写入每个员工的编号、姓名和部门代号
	ofstream ofs;
	ofs.open(FileName, ios::out); // 覆盖写入  
	// 追加写入会产生问题 ： 即在历史数据之上先追加了历史数据然后才是新员工信息
	// 为什么指针数组_employeeNum已经释放内存再存入newspace也没用： 
	//  因为释放的是内存数组的历史数据而不是文本文档的历史数据
	//  新内存数组的数据依然会追加到文本文档的历史数据
	// 所以为了每次加载数据没有历史文本数据，需要覆盖写入 历史文本数据总是当前的内存历史数据决定的
	//ofs.open(FileName , ios::out | ios::app); // 追加写入
	//ofs << "\n"; // 换行追加写入
	for (int i = 0; i < this->_employeeNum; i++)
	{
		ofs << "职工编号 :"<<this->_employeeArray[i]->_Id 
			<< "\t职工姓名 :" << this->_employeeArray[i]->_Name
			<< "\t职工部门编号 :" << this->_employeeArray[i]->_DepartId << endl;
	}
	ofs.close();
	if (this->_employeeNum == 0)
	{
		this->_fileisEmpty = true;
	}
}
void workerSystem::Show_Employee()
{
	if (this->_fileisEmpty) 
	{
		cout<< "文件不存在或者记录为空！" << endl;
	}
	else
	{
		for (int i = 0; i < this->_employeeNum; i++ )
		{
			this->_employeeArray[i]->showInfo();// 职工类有显示信息的方法 直接调用即可
		}
	}
	system("pause");
	system("cls");
	
}
int workerSystem::IsExist_Employee(int id)// 判断某个员工是否存在
{
	int index = -1;
	for (int i = 0; i < this->_employeeNum; i++)
	{
		if (this->_employeeArray[i]->_Id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}
void workerSystem::Del_Employee()
{
	if ( this->_fileisEmpty)
	{
		cout << "文件不存在或者职工信息为空！" << endl;
	}
	else 
	{
		cout << "请输入您想查找的员工编号 : " << endl;
		int  Id;
		cin >> Id;
		int index= this->IsExist_Employee(Id);
		if (index != -1)
		{
			//cout << "该职工存在" << endl;
			//this->_employeeArray[0]->showInfo();
			for (int i = index; i < this->_employeeNum -1; i++)
			{
				// 数据前移操作
				this->_employeeArray[i] = this->_employeeArray[i + 1];
			}
			this->_employeeNum--; // 更新数组中人员的个数
			this->Save(); // 保存文件
			cout << "删除成功！" << endl;
		}
		else
		{
			cout << "该职工不存在!" << endl;
		}
	}
	
	system("pause");
	system("cls");
}
void workerSystem::Change_EmployeeInfo() // 更改员工信息
{
	if (this->_fileisEmpty)
	{
		cout << "文件不存在或者职工信息为空" << endl;
	}
	else
	{
		cout << "请输入修改的职工编号 : " << endl;
		int id;
		cin >> id;
		int ret = this->IsExist_Employee(id); // 判断一下是否存在这个员工
		if (ret != -1)
		{
			delete this->_employeeArray[ret];
			int newid = 0;
			string newname = "";
			int dSelect = 0;
			cout << "已经查到：" <<id <<"号职工，请输入新的职工编号" <<endl;
			cin >> newid;
			cout << "请输入新姓名：" << endl;
			cin >> newname;
			cout << "请输入新职责：" << endl;
			cout << "1.普通员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> dSelect;
			workerIndividual * worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new  worker_Employee(newid, newname, dSelect);//使用worker配合子类去多态呈现抽象类
				break;
			case 2:
				worker = new worker_Manager(newid, newname, dSelect);
				break;
			case 3:
				worker = new boss(newid, newname, dSelect);
				break;
			default:
				break;
			}
			// 更新修改的员工信息所在位置的数据
			this->_employeeArray[ret] = worker;
			cout << "修改员工信息成功！其职位部门编号为：" <<this->_employeeArray[ret]->_DepartId<<endl;
			this->Save();
		}
		else
		{
			cout << "没有此人！修改员工信息失败" << endl;
		}
	}
	system("pause");
	system("cls");
}
void workerSystem::Find_Employee() //查找员工
{
	if (this->_fileisEmpty)
	{
		cout << "文件不存在或者职工信息为空" << endl;
	}
	else
	{
		cout << "请输入查找的方式：" << endl;
		cout << "1、按职工编号查找" << endl;
		cout << "2、按职工姓名查找" << endl;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			int id;
			cout << "请输入查找的职工编号：" << endl;
			cin >>id;
			int ret = IsExist_Employee(id);
			if (ret != -1)
			{
				cout << "找到此人，此员工信息如下：" << endl;
				this->_employeeArray[ret]->showInfo();
			}
			else
			{
				cout << "没有此人！" << endl;
			}
		}
		else if( select == 2)
		{
			string name;
			cout << "请输入查找的职工姓名：" << endl;
			cin >> name;
			bool flag = false; // 查找到的标志
			for (int i = 0; i < this->_employeeNum; i++)
			{
				if (this->_employeeArray[i]->_Name == name) 
				{
					cout << "查找成功，其职工编号为：" << this->_employeeArray[i]->_Id << endl;
					cout << "该员工的具体信息如下：" << endl;
					this->_employeeArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false)
			{
				cout << "没有此人！" << endl;
			}
		}
		else
		{
			cout << "输入选项有误！" << endl;
		}
	}
	system("pause");
	system("cls");
}
void workerSystem::Sort_Employee()// 员工编号排序
{
	if (this->_fileisEmpty)
	{
		cout << "文件不存在或者职工信息为空" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序的方式：" << endl;
		cout << "1、按职工编号升序" << endl;
		cout << "2、按职工编号降序" << endl;
		int select = 0;
		cin >> select;
		for (int i = 0; i < this->_employeeNum; i++)
		{
			int minOrmax = i; //声明最小值或最大值下标
			for (int j = i + 1; j < this->_employeeNum; j++)
			{
				if (select == 1) //升序
				{
					if (this->_employeeArray[minOrmax]->_Id > this->_employeeArray[j]->_Id)
					{
						minOrmax = j;
					}
				}
				else // 降序
				{
					if (this->_employeeArray[minOrmax]->_Id < this->_employeeArray[j]->_Id)
					{
						minOrmax = j;
					}
				}
			}
			if (i != minOrmax)
			{
				workerIndividual* temp = this->_employeeArray[i];
				this->_employeeArray[i] = this->_employeeArray[minOrmax];
				this->_employeeArray[minOrmax] = temp; 
			}
		}
		cout << "排序成功，排序后结果为：" << endl;
		this->Save();
		this->Show_Employee();
	
	}
}
void workerSystem::Clean_File() // 清空文件
{
	cout << "确认清空？" << endl;
	cout << "1. 确认" << endl;
	cout << "2. 返回" << endl;
	int select;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs(FileName, ios::trunc); //如果存在则删除后在创建
		ofs.close();
		if (this->_employeeArray != NULL) // 堆区数组不为空
		{
			for (int i = 0; i < this->_employeeNum; i++)
			{
				if (this->_employeeArray[i] != NULL)
				{
					delete this->_employeeArray[i];//删除每个堆区的数据
				}
			}
			this->_employeeNum = 0; // 数组数量置零
			delete[] this->_employeeArray; // 指针本身也删除
			this->_employeeArray = NULL;
			this->_fileisEmpty = true; // 更新状态
		}
		cout << "清空成功！"<<endl;
	}
	system("pause");
	system("cls");
}
void workerSystem::ExitSystem() // 退出系统
{
	cout << "欢迎下次使用！" << endl;
	//system("pause");
	exit(0); 
}