#include "all.h"
void Study_Text_IO()
{
	// open方法可以直接输入字符串也可以先用char[]定义，使用C风格字符串传入
	ofstream OutFile; // 定义文本写入流
	OutFile.open("test.txt");
	OutFile << "<hello world!>\n" << "<python and c++>"<< endl; // 覆盖写入文本
	OutFile.close();

	char filename[20];
	ifstream InFile; // 定义文本读取流
	//cin.getline(filename, 81); // 输入文件名 "test.txt"
	//InFile.open(filename);
    InFile.open("test.txt"); // 直接输入也可
	// 逐个读取字符
	if (InFile.is_open())
	{
		char value; // 存放读取的字符变量
		
		int count = 0; // 统计字符个数
		//InFile >> value; // 先读取1个字符
		//while (InFile.good()) // 最后一次读取输入是否成功，需要先输入一条语句
		//{
		//	++count;
		//	InFile >> value; // 持续读取字符
		// cout << value ;
		//}
		while (InFile.get(value))  // InFile >> value也可以,但是不会读取空格符
		{
			++count;
			cout << value;
		}
		cout << endl;
		if (InFile.eof()) // 读到最后的eof结束符时
		{
			cout << "end of file reached.\n";
		}
		if (count == 0)
		{
			cout << "there is no data.\n ";
		}
		else
		{
			cout << "文本有" << count << "个字符" << endl;
		}
		InFile.close();
	}
	else if (InFile.fail()) // 失败时返回1，默认返回0
	{
		cout << "InFile.fail()=" << InFile.fail() << endl;
		cout << "file is fail to open.\n";
	exit(EXIT_FAILURE);// 原型在cstdlib中定义
	}
	else
	{
		cout << "unknown reason failed!" << endl;
		
	}

	// 读取整行
	char strs[30]; // 用于存放所有字符
	InFile.open("test.txt");
	InFile.getline(strs, 80);
	while (InFile.good())
	{
		cout << strs << endl;
		InFile.getline(strs, 80);
	}
	//while (InFile.getline(strs, 80))
	//{
	//	cout << strs << endl;
	//}
	InFile.close();
	
}