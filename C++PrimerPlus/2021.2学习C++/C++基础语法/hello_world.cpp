#include <iostream>
#include <string> //2019不会报错 c++20
#include <ctime> // 时间头文件
#include "hello_world.h"
using namespace std;
#define pi = 3.14 //宏常量
//int main()
int hello_world()
{  
	srand((unsigned int)time (NULL));  // 利用时间避免伪随机数
	for (int i = 0; i <= 100; i++) {
		if (i % 2 == 0)
		{
			continue;  //只在i=偶数时才继续执行  输出的是奇数
		}
		cout << i <<  endl;
 	}
	const int  a = 10; // const修饰的变量
	// a = 20;  const变量与宏常量相同不能再次修改
	// 类似于python的global变量,必须事先声明才能更改值
    // short int = 2 子节 -32768~32767  int : 4子节  str : 1子节
	int 美女 = 30;
	 string 帅哥 = "handsome"; //C++风格字符串
	 char str[] = "chenebei"; //C风格的字符串 要用双引号
	 char b = 'F'; 
	 cout << "F 的ASCII码为 :\t " << int(b) << endl;
	cout << "hello world :\t " << 美女 << endl;
	cout << "整型的内存大小为 :\t" << sizeof(美女) << endl;
	int c = 0;
	cin >> c;
	while (c > 0) {
		printf("输出的数字为%d\n",c);
		c = c - 1;
	}
	switch (c) 
	{
	  case 100 :  
		  cout << "满分" << endl;
		  break;
	  default :
		  cout << "不是满分" << endl;
		  break;
	}

		
	   system("pause");
	   return 0;
}


