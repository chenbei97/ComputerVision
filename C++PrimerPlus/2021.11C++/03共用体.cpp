#include "all.h"
void Study_union()
{
	// ��������Դ洢��ͬ���ͣ�����ÿ��ֻ�洢1��ֵ
	struct Person 
	{
		int age;
		string name;
		int type=0;
		union ID 
		{
			char id_str[20] = "cb";
			int id_int ; //ֻ����һ������ʼ��
		} id;
	} person1;
	person1.type = 0;
	if (person1.type == 0)
	{
		strcpy_s(person1.id.id_str,  "chenbei");
		cout << "person id is string = " << person1.id.id_str<<endl;
	}
	else
	{
		cin >> person1.id.id_int;
		cout << "person id is int = " << person1.id.id_int<< endl;
	}
	system("pause");
}