#include "all.h"
void Study_Text_IO()
{
	// open��������ֱ�������ַ���Ҳ��������char[]���壬ʹ��C����ַ�������
	ofstream OutFile; // �����ı�д����
	OutFile.open("test.txt");
	OutFile << "<hello world!>\n" << "<python and c++>"<< endl; // ����д���ı�
	OutFile.close();

	char filename[20];
	ifstream InFile; // �����ı���ȡ��
	//cin.getline(filename, 81); // �����ļ��� "test.txt"
	//InFile.open(filename);
    InFile.open("test.txt"); // ֱ������Ҳ��
	// �����ȡ�ַ�
	if (InFile.is_open())
	{
		char value; // ��Ŷ�ȡ���ַ�����
		
		int count = 0; // ͳ���ַ�����
		//InFile >> value; // �ȶ�ȡ1���ַ�
		//while (InFile.good()) // ���һ�ζ�ȡ�����Ƿ�ɹ�����Ҫ������һ�����
		//{
		//	++count;
		//	InFile >> value; // ������ȡ�ַ�
		// cout << value ;
		//}
		while (InFile.get(value))  // InFile >> valueҲ����,���ǲ����ȡ�ո��
		{
			++count;
			cout << value;
		}
		cout << endl;
		if (InFile.eof()) // ��������eof������ʱ
		{
			cout << "end of file reached.\n";
		}
		if (count == 0)
		{
			cout << "there is no data.\n ";
		}
		else
		{
			cout << "�ı���" << count << "���ַ�" << endl;
		}
		InFile.close();
	}
	else if (InFile.fail()) // ʧ��ʱ����1��Ĭ�Ϸ���0
	{
		cout << "InFile.fail()=" << InFile.fail() << endl;
		cout << "file is fail to open.\n";
	exit(EXIT_FAILURE);// ԭ����cstdlib�ж���
	}
	else
	{
		cout << "unknown reason failed!" << endl;
		
	}

	// ��ȡ����
	char strs[30]; // ���ڴ�������ַ�
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