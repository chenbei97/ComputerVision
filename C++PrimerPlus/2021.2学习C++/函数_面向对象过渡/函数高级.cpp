#include <iostream>
using namespace std;
// 1.函数声明和实现只能有一个带有默认参数
// 2.占位符  返回值类型 函数名 (数据类型)
void func1(int a, int)
{
    cout << a << endl;
}
// 3.重载函数 : 允许函数名相同但是参数不同  即Qt中的过载函数@Pyqt_Slot
// 函数的返回类型不能作为函数重载的条件 int func() 和 void func() 是不行的
//3.1 引用作为重载条件
void func1(int& a)
// 固定地址不固定值 传入10非法 int&a 等价于int * const a = &c 指针常量
// int & a =10 等价于int * const a = &10; 是非法的,所以常量10不能进入该函数
// 引用必须是一个合法的内存空间
{
    cout << "引用传递——过载函数" << endl;
}
void func1(const int& a)
// 固定值不固定地址 传入10是可以的 常量指针
 // 等价于 const int* p = &a 
// const int &a = 10 ; <----->  const int * p = &10是合法的  
// 本质是常量 指针 与上述不同  值不能修改 指向可以
{
    cout << "常量引用——过载函数" << endl;
}
//3.2函数重载与函数默认参数
void func2(int a, int b = 10);
void func2(int a);  // 在main中func2(10) 报错出现二义性要避免
void super()
//int main()
{
    func1(10, 10); // 占位参数必须给定



    int a = 10;
    //const int* p = &a;  // 固定数不固定地址
    //cout << "p的地址为 : " << p << endl;
    //p++;
    //cout << "p++的地址为 : " << p << endl;

    func1(a);  // 引用常量
    func1(10); // 常量引用



    //system("pause");
   // return 0;
}



