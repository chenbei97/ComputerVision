#include <iostream>
using namespace std;
//引用作为交换函数的参数
//1、值传递
void swap1(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
    cout << "\n值传递swap1函数a1=10 , a2 =20 , 值传递交换操作后 : \n" << "a1 = " << a << "\na2 = " << b << endl;
}

//2、地址传递
void swap2(int* a, int* b)
// 与引用传递的区别在于 : 
// 引用传递的形参是指针常量 / 地址常量 ,把实参的地址给了一个指针且固定为常量 此时指向不能再改变
//地址传递 的形参是指针变量  只是把实参的地址给了指针变量 在内部中仍然可以改变指针/地址指向
{
    int temp = *a;
    *a = *b;
    *b = temp;
    cout << "\n地址传递swap2函数a1=10 , a2 =20 , 地址传递交换操作后 : \n" << "a1 = " << *a << "\na2 = " << *b << endl;
    cout << "指针变量修改前a1地址 : " << a << endl;//009DFAC8
    cout << "指针变量修改前a1值 : " << *a << endl; //20
    a++;  // a 是地址
    cout << "指针变量修改后a1地址 : " << a << endl;//009DFACC + 4子节
    cout << "指针变量修改后a1值 : " << *a << endl;//-858993460 指针+1的值不确定了
}
//3、引用传递
void swap3(int& a, int& b)
// 这里外部实参c1,c2传递进来后做的工作是 :
// int * const a = &c1 ; int * const  b =& c2; 指针常量 或者说地址常量
{
    // &a,&b实际上是main函数中c1,c2的别名
    int temp = a;  // 本质上交换地址
    a = b;
    b = temp;
    cout << "\n引用传递swap3函数a1=10 , a2 =20 , 引用传递交换操作后 : \n" << "a1 = " << a << "\na2 = " << b << endl;
    cout << "指针变量修改前a1地址 : " << &a << endl;//009DFAB0
    cout << "指针变量修改前a1值 : " << a << endl; //20 
    int* ref = &a;
    *ref++;
    cout << "指针变量修改后a1地址 : " << ref << endl;//009DFAB4  指针地址+4子节
    cout << "指针变量修改后a1值 : " << *ref << endl;//-858993460 指针+1的值不确定了
    a++; // 值加1 ,a不是指针/地址
    cout << "指针变量修改后a1地址 : " << &a << endl; //009DFAB0 与39行代码地址相同 不发生改变
    cout << "指针变量修改后a1值 : " << a << endl; //21
}

//引用作为函数的返回值
//int & test01()
//{
//    int a = 10;
//    return  a;  // 不能返回局部变量的地址和引用
//}

// 如果是引用的返回,则函数的调用可以作为左值
int& test02()
{
    static int a = 10; //静态变量 存放在全局区(程序运行结束系统才释放)
    return a;
}


// 常量引用
void showValue(const int& val)
{
    // val = 1000;  可以使用常量引用/指针 避免内部改变了外部的实参
    cout << "\nval = " << val << endl;
}
void quote()
//int main()
{

    //引用的作用 : 给变量起别名
    // 语法 ： &别名 = 原名
    // 引用必须初始化,且int & b 非法 ;
    int a = 10;
    int& b = a;
    // 且初始化后不能再改变  int &b = c 非法 ; 
   // 引用本质上是指针常量 int * const p  值可以改变,指针指向不能改变
    int c = 20;
    b = c; // 只是赋值操作
    cout << b << endl;
    cout << a << endl;//可以看出b的指向不变,a的值也改变


    //引用做函数参数 : 利用引用的技术形参修饰实参 可以简化指针修改实参
   // 1.值传递
    int a1 = 10;
    int a2 = 20;
    swap1(a1, a2);
    cout << "main函数a1=10 , a2 =20 , 值传递交换操作后 : \n" << "a1 = " << a1 << "\na2 = " << a2 << endl;
    cout << "值传递main函数的值不发生交换" << endl;
    //2.地址传递
    swap2(&a1, &a2);
    cout << "main函数a1=10 , a2 =20 , 地址传递交换操作后 : \n" << "a1 = " << a1 << "\na2 = " << a2 << endl;
    cout << "地址传递main函数的值发生交换" << endl;
    //3.引用传递
    int c1 = 10;
    int c2 = 20; // 先交换回来
    swap3(c1, c2); // c1,c2送到函数后立刻被别名替代了,引用传递
    cout << "main函数a1=10 , a2 =20 , 引用传递交换操作后 : \n" << "a1 = " << c1 << "\na2 = " << c2 << endl;
    cout << "引用传递main函数的值发生交换" << endl;


    // 引用做函数返回值 : 不要返回局部变量的引用
    //int& ref1 = test01(); //会报错
    //cout << "引用传递的返回值为" << ref1 << endl;
   // 类似于局部变量的地址不能返回

    // 如果是引用的返回,则函数的调用可以作为左值
    int& ref2 = test02();//静态变量 存放在全局区(程序运行结束系统才释放)
    //或者说 静态变量的局部引用是全局的,不是局部,所以可以返回
    cout << "\n引用传递作为左值前的返回值为" << ref2 << endl;
    test02() = 1000; //相当于41行代码的静态变量a赋值为1000
    // 而ref2又是静态变量的引用,所以ref2值也是1000
    cout << "引用传递作为左值后的返回值为" << ref2 << endl;

    // 引用的本质 : 指针常量 int * const p  = &c 编译器做了该部分工作
    // 这里外部实参c1,c2传递进来后做的工作是 :
     // int * const a = &c1 ; int * const  b =& c2; 指针常量 或者说地址常量


    //常用引用 :  类似于常量指针,值不能修改,指向可以改变
    // 不能引用常量,只能引用内存区
    // int & ref = 10 ; 非法
    const int& ref = 10; //等价于 int tem = 10 ;const int &red =temp ;
    // ref = 20 ; 非法 不能修改值
    int a3 = 100;
    showValue(a3);
    cout << "常量引用后的a3值为 : " << a3 << endl;
    cout << "常量引用后的a3值不发生改变" << endl;

    //system("pause");
   // return 0;
}