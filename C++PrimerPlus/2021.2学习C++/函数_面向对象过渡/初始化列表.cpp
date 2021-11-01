#include <iostream>
using namespace std;
#include "quote_pointer.h"
// 格式 List() : a(5) , b(10),c(20)
class List 
{
public :
	int _a;
	int _b;
	int _c;
	List() : _a(5), _b(10), _c(20) {}//初始化列表属性
	List(int a, int b, int c) : _a(a), _b(b), _c(c) {} // 还可以不写死 灵活参数
		void print()
	{
		cout << "a = " << _a << "\nb = " << _b<<"\nc = "<<_c <<endl;
	}

};
int initialList()
//int main()
{
	//copy_Construct(); // 拷贝构造函数运行
	//Deep_Shallow_Copy(); // 深拷贝与浅拷贝
	
	List L1; // 有参构造1 : 利用了初始化列表属性 
	L1.print();

	List L2(1, 2, 3);//有参构造2  : 灵活列表参数
	L2.print();
	//system("pause");
	return 0;


}