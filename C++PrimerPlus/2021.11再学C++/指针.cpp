#include "all.h"
//char* Study_pointer_getname(void);
void Study_pointer()
{
	// C风格定义指针，强调*p1是一个int类型
	int  *p1 ;
	// C++风格 要将int*看成一种数据类型, 强调p2是一个指针类型
	int* p2 ;
	// 同时定义时使用C风格更容易理解
	int  *p3, p4=5; // p4是整型,*p3也是整型
	
	// 定义1个指向p4的指针p5
	int*  p5 = &p4;
	cout << "&p4 = " << &p4 << " p5 = " << p5 << endl; // &p4和p5是相同的

	int a = 0;
	int* p6 = &a;
	// delete p6;  非法,一般delete用于删除new分配的内存

	// 访问动态数组：指针和数组在某些情况是等价的
	int* p7 = new int[10];
	p7[0] = 1;
	p7[1] = 2;
	p7[2] = 3;
	// 指针与数组的不同处,指针是变量可以移动
	cout << "before p7[0]=" << p7[0] << endl;
	p7 = p7 + 1; // 指针移动到下1个元素的地址
	cout << "after p7[0]=" << p7[0] << endl;
	p7 = p7 - 1; // 返回正确的地址再进行delete
	delete[] p7;
	
	int arr[] = { 0,1,2 };
	cout << "arr=" << arr <<" &arr[0]="<<&arr[0]<< " &arr=" << &arr << endl;
	// arr = arr + 1; 非法
	a = *(arr + 1); // 但是解引用是合法的
	int* arrp = &arr[0];
	cout << "*(arr+1)=" << a << " arr[1]="<< arr[1] << " *(p+1)="<<*(arrp +1) << endl;// *(arr+1)和arr[1]和*(p+1)等价
	cout << "sizeof(arr)=" << sizeof(arr) <<" *arrp="<<*arrp<< " sizeof(arrp)=" << sizeof(arrp) << endl;
	//1个int使用4个8位字节,所以arr有12个字节,sizeof(arr)表示有多少个字节
	// sizeof(arrp)=8,表示1个字节的长度=8,或者说指针的长度
	

    // 其他类型的指针类型char* , double*, 使用C++风格理解
	double age[3] = { 1.2,3.5,5.9 };
	char name[5] = {'a','b','c','d','\0'};
	short len[3] = { 7,8,9 };
	short* l1 = len;
	char* c1 = name;
	double* d1 = age;
	cout << "sizeof(short)"<<sizeof(l1) << "sizeof(double)=" << sizeof(d1) << " sizeof(char)=" << sizeof(c1) << endl;

	/*
	不同于数值数组，打印字符串数组名并不给出地址，而是直接打印出内容
	这是因为cout被提供给1个字符的地址，就会打印该字符，然后继续下去直到遇见结束符/0
	如果一定想要打印字符串的地址，则需要int* 类型转换，可以转换数组本身也可以转换指向数组的指针
	在cout和大多数c++表达式中，char数组名、char指针以及引号括起的字符串常量都被解释为第1个字符串的地址*/
	char flower[10] = "flower";
	char* f1 = flower;  // 不会赋值新内存
	cout << "flower=" << flower << " f1="<<f1<<" flower"<< endl;
	cout << "(int*)flower=" << (int*)flower << " (int*)f1=" << (int*)f1 << endl;//地址相同
	cin >> flower;
	f1 = new char [strlen(flower) + 1]; // 使用new可以动态分配内存，更改f1的指向，指向新内存
	
	strcpy_s(f1,strlen(flower)+1,flower); // 输入的值复制到新内存
	cout << "(int*)flower=" << (int*)flower << " (int*)f1=" << (int*)f1 << endl;//地址不同

	c1 =  Study_pointer_getname();//该函数new的内存在本函数中delete
	cout << "(int*)c1=" << (int*)c1 << endl;
	delete [] c1;
	

}
char* Study_pointer_getname(void)
{
	char temp[3];
	cin >> temp;
	char* p = new char[strlen(temp) + 1];
	strcpy_s(p, strlen(temp) + 1,temp);
	return p;
}