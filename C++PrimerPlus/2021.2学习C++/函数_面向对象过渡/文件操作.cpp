#include <iostream>
#include <fstream> // 读写操作
//#include <ifstream> // 读操作
//#include <ofstream> // 写操作
#include <string>
using namespace std;
/*
1. 流对象 : 
	ofstream ofs ; 
	ofs.open("path",打开方式) ; 
	ofs<<"写入的数据" ; 
	ofs.close();
2. 打开方式 ： 
	ios :: in 只读  ;    
	ios :: out 只写   
	ios::ate 初始位置: 文件尾
	ios :: app  追加方式写文件
	ios :: trunc 文件已经存在先删除 再创建
	ios:: binary 二进制方式
	文件打开方式配合使用 : 二进制写文件  ios :: binary | ios :: out
3. 读取文本数据
	3.1 第1种
		char buf[1024] = { 0 };
		while (ifs >> buf) // 写入缓冲区
		{
			cout << buf << endl;
		}
		3.2 第2种
		char buf[1024] = { 0 };
		while (ifs.getline(buf,sizeof(buf)))  // 按行读取
		{
			cout << buf << endl;
		}
		3.3 第3种
		string buf;
		while (getline(ifs,buf))
		{
			cout << buf << endl;
		}
		3.4 第4种
		char c;
		while ((c = ifs.get())!= EOF) // 字符没有读到尾部就一直读取
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
	Person p = {"张三",18};
	// 常量字符型指针 :   指向p的首地址
	ofs.write( (const char * )&p , sizeof(Person));
	ofs.close();
}
void test_0113()
{
	ifstream ifs;
	ifs.open("person.txt", ios::in | ios::binary);
	if (ifs.is_open())
	{
		cout << "打开成功" << endl;
	}
	Person p;
	ifs.read( (char * )&p,sizeof(Person)); // 创建p对象是为了告诉以什么方式读取
	cout << "姓名 : " << p._name << "年龄 : " <<p._age<< endl;
	ifs.close();
}
int fileDealing()
//int main()
{
	// 写文本文件
	//ofstream ofs; // 输出流
	//ofs.open("data.txt",ios::out);
	//ofs << "xingmiing  :  chenbei" << endl;
	//ofs.close();
	
	// 读文本文件
	//ifstream ifs;
	//ifs.open("C://Users//chenbei//Desktop//钢//data.txt",ios::in);
	//if ( ifs.is_open())
	//{
	//	cout << "打开成功" << endl;
	//	//return;
	//}
	
	// 第1种读数据
	//char buf[1024] = { 0 };
	//while (ifs >> buf)
	//{
	//	cout << buf << endl;
	//}
	
	// 第2种读数据
	//char buf[1024] = { 0 };
	//while (ifs.getline(buf,sizeof(buf)))  // 按行读取
	//{
	//	cout << buf << endl;
	//}
	 
	//第3种读数据
	//string buf;
	//while (getline(ifs,buf))
	//{
	//	cout << buf << endl;
	//}
    
	// 第4种读数据
	//char c;
	//while ((c = ifs.get())!= EOF) // 字符没有读到尾部就一直读取
	//{
	//	cout << c;
	//}
	
	//ifs.close();

	// 写二进制文件
	//test_0112();
	// 读文件
	test_0113();
	return 0;

}