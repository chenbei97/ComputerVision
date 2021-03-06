#include <iostream>
using namespace std;
#include "quote_pointer.h"
//构造函数和析构函数(初始化和清理)
/*
<1>构造函数: 类名(){}
1.没有返回值 也不写void
2.函数名称和类名相同
3.构造函数可以有参数，因此可以重载
4.程序在调用对象时会自动调用构造，无需手动调用且只调用一次
构造函数的分类和调用
<2>分类方式:
1.按参数分: 有参构造和无参构造
按类型分 : 普通构造和拷贝构造
2.调用方式 ： 括号法、显示法、隐式转换法
*/
/*
析构函数 : ~类名(){}
1.没有返回值 也不写void
2.函数名称和类名相同 加上符号~
3.构造函数不可以有参数，因此不可以重载
4.程序在对象销毁前会自动调用析构，无需手动调用且只调用一次
5.销毁非static成员
*/
class Date
{
public:
    Date()
    { } // 表示什么也不做 初始化就是私有属性 默认构造函数Date(){}
    Date(int day) // 有参构造函数 Date(int a){}
    {
        _year = 1949;
        _month = 10;
        _day = day; 
    }
    Date(const Date& D) // 拷贝构造 Date(const Date & D)
    {
        _year = D._month;
        _month = D._year;
        _day = D._day;
    }
    void print()
    {
        cout << _year << "-" << _month << "-" << _day << endl;
    }
    ~Date()
    {
        cout << "<---------析构函数--------->" << endl;
    }

private:
    int _year = 1990;
    int _month;
    int _day;
};
void test1(Date D5) //D5是值传递
{
    // Date D5 = D;
    cout << "D4值传递后给D5的地址为 : " << (int)&D5 << endl;//  11531732
    //传递的时候D5发生了一次拷贝构造
    D5.print();//-858993460-1990--858993460 所以这里年月也被调换了
}
Date test2()
{
    Date D6; //默认构造拷贝
    cout << "返回局部对象D6的地址为 : " << (int)&D6 << endl; //11531712
    D6.print();//  1990--858993460--858993460
    return D6;
}
//int main()
int copy_Construct()
{
    // "quote_pointer.h" 包含了use_circle_point函数
    //这个函数已经包含了"circle.h"和"point.h" 
    // 而两个头文件又分别已经指向了两个cpp文件 所以可以运行
    //而两个cpp文件都包含了同一个类,然后头文件声明后编译会出现错误
    use_circle_point();
   /*
   构造函数调用规则 ： c++编译器至少给一个类提供3个函数
   1.默认构造函数(无参 函数体为空) 
   2.默认析构函数(无参 函数体为空) 
   3.默认拷贝构造函数 对属性进行值拷贝
   ①若用户定义了有参构造函数 c++不再提供无参构造 但会提供默认拷贝构造 
   ****注**** : 30行代码提供有参构造那么28行不提供 需要自己重新显示的定义
   ****注**** :  123行代码
 ②如果用户定义拷贝构造函数 ，c++不再提供其他构造函数
   ****注**** : 36行代码提供拷贝构造,那么28和30行代码想要使用必须显式定义
   ****注**** :  127行代码
  */
        /*
      构造方法
      1.括号法
      1.1 默认构造     
      Date D ;     √  (类自带)   也可以自定义新的  无参构造函数Date(){}
      1.2  有参构造
      Date D(10) ; 前提是类中存在   只能自定义    有参构造函数 Date(int a){}
      1.3  拷贝构造
      Date D(D0) ;  √  (类自带)   也可以自定义新的   拷贝构造函数 Date(const Date & D){}
      2.显示法
      2.1 有参显示法
      Date D = Date(10) ; <----等价于----> Date D(10) ;
      2.2 拷贝显示法
      Date D = Date (D0) ;  <----等价于----> Date D(D0) ;
      3.  隐式转换法
      3.1 有参隐式转换法
      Date D = 10 ;  <----等价于----> Date D(10)  和 Date D = Date(10) ;
      3.2 拷贝隐式转换法
      Date D = D0 ; <----等价于----> Date D(D0)  和 Date D = Date(D0) ;
     ****注1**** : 不能利用拷贝构造函数初始化匿名对象
     ****注2**** :  当前执行结束后系统会立即回收掉匿名对象
     ****注3**** : Date(10) ---->没有构造变量名 ------> 编译器认为Date (10) === Date 10 ;
     ****注4**** : Date(D0) -----> 即使不匿名 ----->编译器认为Date (D0) === Date D0 ;
     ----> 如果D0是一个已有的对象 利用D0重复拷贝构造就会提示重定义错误
      */
      /*
      * 拷贝构造发生的时机 :
      1.使用一个已经创建完毕的对象来初始化一个对象
      2.值传递的方式给函数参数传值
      3.以值方式返回局部对象
     */
    Date D1; // 默认构造
    D1.print();//1990--858993460--858993460

    Date D2(1); //有参构造 ： 
    // 如果注释掉默认构造 只有有参构造 Date D1;会报错提示没有默认构造
    D2.print();//1949-10-1

    // 1.使用一个已经创建完毕的对象来初始化一个对象
    // 同理注释掉有参和无参构造 ,只有拷贝构造 那么Date D1;和Date D2(1) ; 也会报错 提示没有相应的构造函数
    Date D3(D2);  // 默认拷贝构造 利用已有的D2进行初始化,不过初始化规则把年月调换了
    D3.print();//10-1949-1

    //2.值传递的方式给函数参数传值
    Date D4;
    D4.print();//1990--858993460--858993460
    cout << "值传递前D4的地址为 : " << (int)&D4 << endl; //11531984
    test1(D4); //  11531732

    //3.以值方式返回局部对象
    Date D7 = test2();
    cout << "局部对象D6传递到D7的地址为 : " << (int)&D7 << endl; //11531964
    D7.print();//-858993460-1990--858993460  注意返回后的D7 年月又被调换了 发生了拷贝构造

    /**************************************************************************************/
    int arr[5] = {12,32,23,31,42};
    int* parr = arr;
    cout << "\n数组的地址arr为 : " << arr << endl; //数组本身就是地址
    cout << "\n数组的地址parr为 : " << parr << endl; // 对数组取地址 指针也可以
    cout << "\n数组的第二个元素值arr[1]为 : " << arr[1] << endl;
    cout << "\n数组的第二个元素值*(++parr)为 : " << *(++parr) << endl;
    //cout << "\n数组的第二个元素值++*parr为 : " << ++*parr << endl; //12+1 <----->错误
    cout << "\n数组的第二个元素地址为&arr[1] : " << &arr[1] << endl;
    cout << "\n数组的第二个元素++parr地址为 : " << parr << endl; // 前边parr已经加过了
    //system("pause");
    return 0;
}
