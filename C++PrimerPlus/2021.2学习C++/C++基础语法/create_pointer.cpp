#include <iostream>
#include <string> //2019不会报错 c++20
#include "hello_world.h"
#include <ctime> // 时间头文件
using namespace std;
int create_pointer(){
//int main() {
     //create_func();
    //创建指针:间接访问内存
    // 一个变量记录另一个变量的内存地址.叫指针
    // 数据类型 *指针变量名
    
    //1. 引用地址
    int a = 10;
    int* p = &a; //指针p记录a的地址
    //cout << &a << endl;
    //cout << p << endl; // p和&a是一个东西
    
    //2.解引用 *p 找到指针指向的内存中的数据
    //cout << *p << endl;//*p和a是一个东
    //cout << &(*p) << endl;// &和*可以理解为是相反的操作,抵消为p
    //cout << *(&a) << endl; //抵消为a

    // 指针变量本身的内存大小  存放4位16进制数据
    // 1位16进制 = 16个二进制数 = 2个8位二进制 = 2字节
    //指针在32位系统下占用4字节,64位 8字节
    cout << sizeof(int*) << endl;  // 8
    cout << sizeof(char*) << endl;
    cout << sizeof(float*) << endl;
    cout << sizeof(double*) << endl;

    // 空指针 : 指针变量指向内存中编号为0的空间,不可以访问, 一般用于初始化指针变量,
   //0~255的内存编号为系统占用不可以访问
    //int* p = NULL; //不能重复定义

    //野指针:指向非法的内存空间
    //int* p = (int*)0x1000 ; //把16进制数强制为指针变量赋给这个p
    //cout << *p << endl; // 随便找个地址解引用是非法的
   // system("pause");
    return 0;
}