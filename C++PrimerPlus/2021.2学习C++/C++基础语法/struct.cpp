#include <iostream>
#include <string> //2019不会报错 c++20
#include "hello_world.h"
#include <ctime> // 时间头文件
using namespace std;
//创建方式:
//1.struct 结构体名 变量名
//2. struct 结构体名 变量名 = {成员1,成员2}
//3. 定义结构体时顺便创建变量
struct student {
    string name = "cb";
    int age = 24;
    int score = 100;
}s4; //顺便创建结构体变量;
int Struct(){
//int main() {
    //pointer_func();
    // 结构体属于用户自定义的数据类型,允许用户存储不同的数据类型
    // 面向对象的过渡，内置没有函数,结构体不是类
    // struct 结构体名{结构体成员列表};

    // 实例化结构体
    struct student s1;//1.
    student s2; //创建变量可以省略,但是定义时不能
    s2.age = 30; //结构体成员访问
    struct student s3 = {"chenbei",24,100 };//2.
    //3.在创建时就赋予变量值 不常用
    s4.name = "张三";
    s4.age = 20;
    s4.score = 60;
    
    // 结构体数组 : 把创建的属性整体看成一个对象的子属性
    // 每个上一级对象都有下一级的全部属性
    struct student arr[3] = {
    {"张三",18,80},
    {"李四", 39, 45},
    {"王五", 95, 22}
    };
    cout << arr[2].name << endl;

    //结构体指针 : 访问结构体成员的属性
    //int* p = &s3; //报错,因为s3取地址为结构体student不能使用整型指针
    struct student * p = &s3;
    student* p1 = &s2;// 也可以省略

    cout << p->name << endl; //结构体指针访问属性是->符号

    //system("pause");
    return 0;
}