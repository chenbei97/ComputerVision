#include "all.h"
/*
引用变量使用&定义，但不是取址符号，而是看成一种类型，即 int & 是一种引用类型
int a = 0 ;
int & q = a ;

需要注意的是，引用必须在声明中即初始化，不可以先声明，后赋值，这也是与指针的区别
int* p ;
p = &a ; // 指针先声明后赋值可以

x -> int &q ;
× -> q = a ; // 必须声明即初始化，这也是为了避免引用赋值和值的赋值冲突

int & q = a ; // √ 正确

引用的指向一经声明，就不可以再更改，但是可以改变值，所以引用更像是指针常量
int & q = a ;
int * const p = &a; // p和q隐式等价

如果试图更改引用的指向，实际上，只是改变引用的值
int & q = a ;
int b = 1 ;
q = b ; // 试图把q引用指向b,事实上这只是更改了q的值为b,所以结果是q和b都为1

如果使用一个普通指针指向变量，一个引用指向该指针，当指针改变指向时，引用也是否会更改指向呢？答案是否定的
int * p = a ; // 指针指向a
int & q = *p ; // 引用指向指针
p = &b ; // 指针指向b
cout << p << a << q << endl; // 结果p和a的地址仍然相同,q的地址指向了b,q依然通过声明初始化时的传递与a绑定

*/

/*
C语言中是不允许按引用传递的，只能按值传递，即主程序中创建1个变量，函数调用此变量时创建了一个副本去执行，从而是2个变量2个名称；如果希望避免拷贝内存，可以通过传递指针的方式来迂回实现

​而C++中允许引用传递，传递的是变量的别名，有着指针传递的效果，无需创建内存副本

交换函数的比较，一共三种方法：
按变量值值传递的交换方法；
按变量引用传递的交换方法；
按变量指针值传递的方法；
其中按变量值值传递的方法是不能交换原始数据的，只能对副本进行交换，下方代码进行演示。
*/

void Study_Quote_Swap_VariableValueTransfer(int ta, int tb)
{
	cout << "		1.函数内部变量值值传递交换前：" << "  ta=" << ta << "  tb=" << tb << endl;
	int c ;
	c = ta;
	ta = tb;
	tb = c;
	cout << "		2.函数内部变量值值传递交换后：" << "  ta=" << ta << "  tb=" << tb << endl;
}
void Study_Quote_Swap_QuoteTransfer(int& qa, int& qb)
{
	// 传递进来的是qa和qb
	cout << "		1.函数内部引用传递交换前：" << "  qa=" << qa << "  qb=" << qb << endl;
	//int &c = qa; // c->qa->a,创建了新的引用
	//qa = qb; // 不要认为是改变引用指向,这是改变值,主程序中qa与a绑定了
	//qb = c; // a一旦改变,c->a也改变为2,故qb为2而不是1达不到交换的效果
	
	int c;  // 应当创建新的变量,而不是创建新的引用
	c = qa; // 把qa的值给c
	qa = qb; 
	qb = c; 
	cout << "		2.函数内部引用传递交换后：" << "  qa=" << qa << "  qb=" << qb << endl;

}
void Study_Quote_Swap_PointerValueTransfer(int* pa, int* pb)
{
	cout << "		1.函数内部变量指针的值传递交换前：" << "  *pa=" << *pa << "  *pb=" << *pb << endl;
	/*
	int* p;
	p = pa;// 创建了新的指针p->pa->a   *p=a=2
	cout << "  *p=" << *p << endl;//*p=2
	pa = pb; // 改变了指针指向，*pa=*pb=b=1,但是此时p不发生改变,依然指向pa之前指向的地址也就是a-
	cout << "  此时*p=" << *p << endl;// 此时*p=2
	pb = p; // 又改变了指向 , *pb = *p= b
	cout << "*pb="<< * pb << endl;//*pb=2
	// 内部确实交换了2个指针地址,造成了交换的假象,但是原数据没有交换,
	*/
	// 应当交换2个指针指向的值
	int c;
	c = *pa;
	*pa = *pb;
	*pb = c;
	cout << "		2.函数内部变量指针的值传递交换后：" << "  *pa=" << *pa << "  *pb=" << *pb << endl;
}
double Study_Temp_Quote(double& q)
{
	return q * q * q;
}
double Study_Temp_Value(double q)
{
	return q * q * q;
}
struct Person
{
	int age;
	string name;
};
void Study_Quote()
{
	int a = 1, b = 2;
	cout << "(1)按变量值的值传递：" << endl;
	cout << "	1)主程序变量值值传递交换前：" << "  a=" << a << "  b=" << b<<endl;
	Study_Quote_Swap_VariableValueTransfer(a,b);
	cout << "	2)主程序变量值值传递交换后：" << "  a=" << a << "  b=" << b<<endl;
	cout << "结论：按变量值的值传递进行交换不改变原有数据，只交换函数内部创建的副本" << endl;
	cout << endl;
	int& qa = a;
	int& qb = b;
	cout << "(2)按引用传递：" << endl;
	cout << "	1)主程序引用传递交换前：" << "  a=" << a << "  b=" << b << endl;
	Study_Quote_Swap_QuoteTransfer(qa, qb);
	cout << "	2)主程序引用传递交换后：" << "  a=" << a << "  b=" << b << endl;
	cout << "结论：引用传递进行交换改变原有数据，函数内部也改变" << endl;
	cout << endl;

	int* pa = &a;
	int* pb = &b;
	cout << "(3)按变量指针的值传递：" << endl;
	cout << "	1)主程序变量指针的值传递交换前：" << "  a=" << a << "  b=" << b << endl;
	Study_Quote_Swap_PointerValueTransfer(pa, pb);
	cout << "	2)主程序变量指针的值传递交换后：" << "  a=" << a << "  b=" << b << endl;
	cout << "结论：按变量指针的值传递进行交换改变原有数据，函数内部也改变" << endl;

	// 常量引用
	double z = 1.2;
	double* pz = &z;
	double& qz = z;
	const double& cqz = 1.2;
	long y = 5L;
	double z_arr[3] = { 1.5,2.5,3.5 };
	// 按值传递加入const与否都是合法的
	double v0 = Study_Temp_Value(cqz);//合法
	double v1 = Study_Temp_Value(qz);//合法
	double v2 = Study_Temp_Value(z);//合法
	double v3 = Study_Temp_Value(*pz);//合法
	double v4 = Study_Temp_Value(2);//合法
	double v5 = Study_Temp_Value(z + 2);//合法
	double v6 = Study_Temp_Value(z_arr[2]);//合法
	double v7 = Study_Temp_Value(y);//合法
    
	// 引用传递引入const才全部是合法的,否则部分非法
	// double x0 = Study_Temp_Quote(cqz);非法,不能使用常量引用
	double x1 = Study_Temp_Quote(qz);//合法
	double x2 = Study_Temp_Quote(z);//合法
	double x3 = Study_Temp_Quote(*pz);//合法
	// double x4 = Study_Temp_Quote(2);非法,不能使用常量引用
	// double x5 = Study_Temp_Quote(z + 2);非法,z+2虽然不是常量引用,但是没有名称
	double x6 = Study_Temp_Quote(z_arr[2]);//合法
	//double x7 = Study_Temp_Quote(y);非法,类型不正确

	// 上述3种错误,一种是使用常量引用,非常量引用但没有名称,类型不正确
	// 实参类型正确时但不是左值(可被引用的对象),使用const可以生成临时变量指向它,如z+2没有名称但是可以生成匿名变量
	// 实参类型不正确,但是可以转换为正确的类型,也会产生临时变量
	cout << "hello" << endl;
	// 引用与结构体，可以使用3种方法定义处理结构体的函数
	Person  Study_Quote_Struct0(Person p);
	Person& Study_Quote_Struct1(Person & p);
	Person& Study_Quote_Struct2(const Person & p);
	system("pause");
}