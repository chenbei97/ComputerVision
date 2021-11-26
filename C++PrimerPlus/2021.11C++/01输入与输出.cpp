#include "all.h"

using namespace std;
void Study_cout_and_cin() 
{
	// 输出 cout
	cout << "hello world" << endl;
	cout << endl; // <=> cout<< '\n'
	cout << "123456\n";
	printf("num is %d\n",25);
	printf("str is %s\n", "25");
	
	int num = pow(2,31)-1; // 默认是有符号整型
	cout <<"sqrt(num) is "<< sqrt(num)<< endl;
	float a = rand();
	cout << sizeof(int) << " " <<
		sizeof(short) <<" " << sizeof(float) << " "
		<< sizeof(double) << " "<<sizeof(long) << 
		" " << sizeof(long long)<<endl;// 4 , 2 ,4, 8 , 4, 8
	cout << "strlen(aaa) ="<<strlen("aaa")<<endl;
	// 输入 cin
	const int Size = 20;
	char name1[Size];
	char name2[Size];
	char name3[Size];
	//cin >> name1; 
	// cout <<"cout="<<name1 << endl;
	cin.getline(name2, Size);
	cin.get(name3, Size);
	cout << 
		" cin.getline=" << name2<<
		" cin.get="<<name3<<endl; // 不会输出整行,
}













