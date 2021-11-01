#include <iostream>
#include <fstream> // ��д����
//#include <ifstream> // ������
//#include <ofstream> // д����
#include <string>
using namespace std;
/*
1. ������ : 
	ofstream ofs ; 
	ofs.open("path",�򿪷�ʽ) ; 
	ofs<<"д�������" ; 
	ofs.close();
2. �򿪷�ʽ �� 
	ios :: in ֻ��  ;    
	ios :: out ֻд   
	ios::ate ��ʼλ��: �ļ�β
	ios :: app  ׷�ӷ�ʽд�ļ�
	ios :: trunc �ļ��Ѿ�������ɾ�� �ٴ���
	ios:: binary �����Ʒ�ʽ
	�ļ��򿪷�ʽ���ʹ�� : ������д�ļ�  ios :: binary | ios :: out
3. ��ȡ�ı�����
	3.1 ��1��
		char buf[1024] = { 0 };
		while (ifs >> buf) // д�뻺����
		{
			cout << buf << endl;
		}
		3.2 ��2��
		char buf[1024] = { 0 };
		while (ifs.getline(buf,sizeof(buf)))  // ���ж�ȡ
		{
			cout << buf << endl;
		}
		3.3 ��3��
		string buf;
		while (getline(ifs,buf))
		{
			cout << buf << endl;
		}
		3.4 ��4��
		char c;
		while ((c = ifs.get())!= EOF) // �ַ�û�ж���β����һֱ��ȡ
		{
			cout << c;
		}
	*/
class Person
{
public:
	    char _name[64];
		int _age;
};
void test_0112()
{
	ofstream ofs;//("person.txt", ios::out | ios::binary);
	ofs.open("person.txt",ios::out | ios::binary);
	Person p = {"����",18};
	// �����ַ���ָ�� :   ָ��p���׵�ַ
	ofs.write( (const char * )&p , sizeof(Person));
	ofs.close();
}
void test_0113()
{
	ifstream ifs;
	ifs.open("person.txt", ios::in | ios::binary);
	if (ifs.is_open())
	{
		cout << "�򿪳ɹ�" << endl;
	}
	Person p;
	ifs.read( (char * )&p,sizeof(Person)); // ����p������Ϊ�˸�����ʲô��ʽ��ȡ
	cout << "���� : " << p._name << "���� : " <<p._age<< endl;
	ifs.close();
}
int fileDealing()
//int main()
{
	// д�ı��ļ�
	//ofstream ofs; // �����
	//ofs.open("data.txt",ios::out);
	//ofs << "xingmiing  :  chenbei" << endl;
	//ofs.close();
	
	// ���ı��ļ�
	//ifstream ifs;
	//ifs.open("C://Users//chenbei//Desktop//��//data.txt",ios::in);
	//if ( ifs.is_open())
	//{
	//	cout << "�򿪳ɹ�" << endl;
	//	//return;
	//}
	
	// ��1�ֶ�����
	//char buf[1024] = { 0 };
	//while (ifs >> buf)
	//{
	//	cout << buf << endl;
	//}
	
	// ��2�ֶ�����
	//char buf[1024] = { 0 };
	//while (ifs.getline(buf,sizeof(buf)))  // ���ж�ȡ
	//{
	//	cout << buf << endl;
	//}
	 
	//��3�ֶ�����
	//string buf;
	//while (getline(ifs,buf))
	//{
	//	cout << buf << endl;
	//}
    
	// ��4�ֶ�����
	//char c;
	//while ((c = ifs.get())!= EOF) // �ַ�û�ж���β����һֱ��ȡ
	//{
	//	cout << c;
	//}
	
	//ifs.close();

	// д�������ļ�
	//test_0112();
	// ���ļ�
	test_0113();
	return 0;

}