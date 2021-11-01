#include <iostream>
using namespace std;
#define MaxContacts   1000  // 不加分号和等号
//通讯录功能:添加联系人、显示联系人、删除联系人、查找联系人、修改联系人、清空联系人、退出通讯录
//根据用户不同的选择进入不同的功能选择switch分支结构搭建，用户选择0时执行推出，选择其他不做操作也不退出程序
// 
//菜单选择界面函数
void showMenu() {
	cout << "*****   1、添加联系人   *****" << endl;
	cout << "*****   2、显示联系人   *****" << endl;
	cout << "*****   3、删除联系人   *****" << endl;
	cout << "*****   4、查找联系人   *****" << endl;
	cout << "*****   5、修改联系人   *****" << endl;
	cout << "*****   6、清空联系人   *****" << endl;
	cout << "*****   0、退出通讯录   *****" << endl;

}


//添加联系人函数
//联系人上限1000，联系人信息(姓名、性别、年龄、联系电话、家庭住址)
/*步骤
1.设计联系人结构体
2.设计通讯录结构体
3.main函数创建通讯录
4.封装  添加联系人函数
5.测试添加联系人功能
*/
struct contacts
{
	string  name;
	int  gender; // 1.男 2.女 方便重新输入时不用打字
	int age;
	string phone;
	string address;
};
struct address_book
{
	// 1.通讯录中保存的保存联系人数组
	struct contacts  contactsArray[MaxContacts];
	//2.当前通讯录人数的个数
	int  user_num;
};
void addContacts(address_book* abs) {
	// 输入参数是通讯录结构体类型的(address_book)，且是地址(*)，形参(abs)
	//1.判断通讯录是否已满,满了不能添加
	if (abs->user_num == MaxContacts)
	{
		cout << "通讯录已满，无法添加！" << endl;
		return;
	}
	else
	{
		/*注意事项：
		 1.由于下方有很多终端输入的命令，为了防止代码串行，性别的while循环后边才继续写年龄、地址等
		 2.终端输入的格式如果与定义的格式不同就会出错，例如性别或者年龄要求输入整型，输入字符串或者浮点型就会出错
		*/
		// 姓名
		string name;
		cout << "请输入姓名 : " << endl;
		cin >> name;
		// 这里当前通讯录联系人个数初始化为0,后续可以++ 对每个新建联系人进行顺序编号
		abs->contactsArray[abs->user_num].name = name;

		// 性别
		cout << "请输入性别  : " << endl;
		cout << "1 --- 男" << endl;
		cout << "2 --- 女" << endl;
		int gender = 0;
		while (true)
		{
		LOOK: cout << "请重新输入性别代号 : " << endl;
			cin >> gender; //性别输入错误需要重新输入,所以在while循环中其它不需要
			if (gender == 1 || gender == 2)
			{
				abs->contactsArray[abs->user_num].gender = gender;
				break; //输入1或者2 可以退出循环 否则重新输入
			}
			// 可以直接在这里打印75行代码不使用if-else-goto结构
			//cout << "输入代号错误，请重新输入！" << endl;
			//可以使用if - else打印, 但是需要goto跳转至重新输入,这里选择第2种
			else
			{
				// bug : 如果输入的不是数字而是字母会反复输出语句
				cout << "输入性别代号错误，请重新输入！" << endl;
				goto  LOOK;
			}
		}

		// 年龄
		cout << "请输入年龄 : " << endl;
		int age = 0;
		cin >> age;
		abs->contactsArray[abs->user_num].age = age;

		// 联系电话
		cout << "请输入联系电话 : " << endl;
		string phone;
		cin >> phone;
		abs->contactsArray[abs->user_num].phone = phone;

		// 住址
		cout << "请输入家庭住址 : " << endl;
		string address;
		cin >> address;
		abs->contactsArray[abs->user_num].address = address;

		// 更新通讯录 对应57行代码

		cout << "添加联系人成功，该联系人编号为 : " << abs->user_num << endl;
		abs->user_num++;

		system("pause");
		system("cls"); // 清屏操作, 避免每次输入命令都重复运行显示菜单栏函数

	}
}


//显示联系人函数
void showContacts(address_book* abs)
/*
 1.检验通讯联系人是否为空 2. 不为空时再显示联系人信息
*/
{
	if (abs->user_num == 0) // 如果为0 提示记录为空 , 否则显示记录的联系人信息
	{
		cout << "当前没有联系人！" << endl;
	}
	else
	{  //遍历每个联系人 : user_num 至少为1
		for (int i = 0; i < abs->user_num; i++)
		{
			cout << "联系人编号 : " << i << endl;
			cout << "\t姓名 : " << abs->contactsArray[i].name << endl;
			cout << "\t性别 : " << abs->contactsArray[i].gender << endl;
			cout << "\t年龄 : " << (abs->contactsArray[i].age == 1 ? "男" : "女") << endl;
			cout << "\t联系电话 : " << abs->contactsArray[i].phone << endl;
			cout << "\t家庭住址 : " << abs->contactsArray[i].address << endl;
		}
	}
	system("pause");
	system("cls"); // 清屏操作, 避免每次输入命令都重复运行显示菜单栏函数
}


// 删除联系人
/*
1.检验某个通讯联系人是否为空,这个检验使用函数进行检验调用为空返回-1
2. 不为空时返回联系人的位置再删除联系人信息
3.按照姓名进行删除, 删除操作是将删除对象后方的数据全部依次前移覆盖操作就可以
4.同时通讯联系人个数要-1操作
*/
int  isExist(address_book* abs, string name)
// 检查联系人姓名是否存在
{
	for (int i = 0; i < abs->user_num; i++)
	{
		if (abs->contactsArray[i].name == name)
		{
			return i; // 找到联系人返回其位置
		}
	}
	cout << "通讯录不存在此联系人！" << endl;
	return -1; //没找到
	system("pause");
	system("cls"); // 清屏操作, 避免每次输入命令都重复运行显示菜单栏函数
}
void deleteContacts(address_book* abs, int  location)
{
	if (location > -1) // 返回的联系人编号只可能是0,1,2,...MaxContacts
	{
		for (int i = location; i < abs->user_num; i++)
			// 从被删除的对象所在位置开始
		{
			// 数据前移操作
			abs->contactsArray[i] = abs->contactsArray[i + 1];// i =999时执行此行代码没有越界
		}
		// 所有数据前移完毕后更新联系人的数目
		abs->user_num--;
	}
	cout << "删除联系人成功！" << endl;
	system("pause");
	system("cls"); // 清屏操作, 避免每次输入命令都重复运行显示菜单栏函数
}



// 查找联系人
void findContact(address_book* abs)
{
	cout << "请输入您要查找的联系人" << endl;
	string name;
	cin >> name;
	int ret = isExist(abs, name);  // 联系人位置
	if (ret != -1)
	{
		cout << "联系人编号 : " << ret << endl;
		cout << "\t姓名 : " << abs->contactsArray[ret].name << endl;
		cout << "\t性别 : " << abs->contactsArray[ret].gender << endl;
		cout << "\t年龄 : " << (abs->contactsArray[ret].age == 1 ? "男" : "女") << endl;
		cout << "\t联系电话 : " << abs->contactsArray[ret].phone << endl;
		cout << "\t家庭住址 : " << abs->contactsArray[ret].address << endl;
	}
	else
	{
		// isExist函数内部已经有返回值
	}
	system("pause");
	system("cls"); // 清屏操作, 避免每次输入命令都重复运行显示菜单栏函数
}



// 修改联系人
void modifyContact(address_book* abs)
{
	cout << "请输入您要修改的联系人 :  " << endl;
	string name;
	cin >> name;
	int ret = isExist(abs, name);//修改的联系人编号
	if (ret != -1)
	{
		//姓名
		string name;
		cout << " 请输入新的姓名 : " << endl;
		cin >> name;
		abs->contactsArray[ret].name = name;
		//性别
		cout << " 请输入新的性别 : " << endl;
		cout << "1 --- 男" << endl;
		cout << "2 --- 女" << endl;
		int gender = 0;
		while (true)
		{
			cin >> gender;
			if (gender == 1 || gender == 2)
			{
				// 输入正确退出循环
				abs->contactsArray[ret].gender = gender;
				break;
			}
			cout << "输入有误，请重新输入!" << endl;// 这里对应79行代码可以在输入错误时重新输入
		}
		//年龄
		cout << "请输入新的年龄 : " << endl;
		int age = 0;
		cin >> age;
		abs->contactsArray[ret].age = age;

		// 联系电话
		cout << "请输入新的联系电话 : " << endl;
		string phone;
		cin >> phone;
		abs->contactsArray[ret].phone = phone;

		// 住址
		cout << "请输入新的家庭住址 : " << endl;
		string address;
		cin >> address;
		abs->contactsArray[ret].address = address;

	}
	else
	{
		// isExist函数内部已经有返回值
	}
	system("pause");
	system("cls"); // 清屏操作, 避免每次输入命令都重复运行显示菜单栏函数
}



// 清空联系人
void clearContact(address_book* abs)
{
	int select = 0;
	cout << "您确定是否要清空联系人？" << endl;
	cout << "1----确定清空" << endl;
	cout << "2----撤销清空" << endl;
	cin >> select; 
	if (select == 1)
	{
		abs->user_num = 0; // 逻辑情况,不需要循环删除每个信息
		cout << "通讯录联系人已经全部清空!" << endl;
	}
	else {
		cout << "取消清空联系人成功!" << endl;
	}
	system("pause");
	system("cls"); // 清屏操作, 避免每次输入命令都重复运行显示菜单栏函数
}



// 主函数
int main()
{
	// 创建通讯录结构体变量
	address_book  current_address_book;
	// 初始化通讯书人员的个数
	current_address_book.user_num = 0;

	while (true) // 用户选择0时才会退出
	{
		//显示菜单栏
		showMenu();
		//用户选择功能
		int select = 0;
		cout << "请问您想做什么，下方输入命令代号--->(1,2,3,4,5,6,0) : " << endl;
		cin >> select; //用户输入到终端的值
		switch (select)
		{
		case 1:  //1、添加联系人
			// 输入参数为通讯录的地址 , 该函数利用地址传递可以给通讯录结构体添加成员
			addContacts(&current_address_book);
			break;

		case 2://2、显示联系人
			showContacts(&current_address_book);
			break;

		case 3: //3、删除联系人
		{ // 大段代码时需要用{}指定为一个代码段, 否则报错
			cout << "请输入删除的联系人姓名 : " << endl;
			string _name;
			cin >> _name;
			cout << isExist(&current_address_book, _name) << endl;
			if (isExist(&current_address_book, _name) == -1)
			{
				// isExist函数内部已经有返回值
			}
			else
			{
				cout << "找到此人，此人所在位置为 : " << isExist(&current_address_book, _name) << endl;
				deleteContacts(&current_address_book, isExist(&current_address_book, _name));
			}
		}
		break;

		case 4://4、查找联系人
			findContact(&current_address_book);
			break;

		case 5://5、修改联系人
			modifyContact(&current_address_book);
			break;
		
		case 6://6、清空联系人
			clearContact(&current_address_book);
			break;
		
		case 0://7、退出通讯录
			cout << "欢迎下次使用" << endl;
			system("pause");
			return 0;  // 退出while循环的唯一方式
			break;

		default:
			break;
		}
	}
	system("pause");
	return 0;
}
