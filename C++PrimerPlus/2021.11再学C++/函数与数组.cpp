#include "all.h"
int Study_Sum_Arr(int arr[], int n);
int Study_Sum_Arr_(int* arr, int n);
int Study_Sum_Arr__(int const* begin, int const* end);
void Study_revalue(int c, int* arr, int n);
void Study_display(int const *arr, int n);
int Study_Sum_Arr_2D(int arr[][4], int r); 
unsigned int Study_Str_Count(const char* str, char ch);
char* Study_return_strs(char c, int n);
void Study_Func_Arr()
{
	int const n = 5; // 等价const int n = 5;
	int arr[n] = {10,20,30,40,50}; // arr[n]的n必须是不可变的,所以需要const限定n
    cout << "arr=" << arr << "   " << "&arr[0]=" << &arr[0] << endl;// C++将数组名解释为其第一个元素的地址
    cout << "main：sizeof(arr)=" << sizeof(arr)<<endl; // main：sizeof(arr)=20，数组长度
	int total = Study_Sum_Arr(arr, n);  // 传递的arr是地址
    cout << "total=" << total << endl;

    int sum1 = Study_Sum_Arr(arr+2, n-2);
    cout << "sum1=" << sum1 << endl; // 120

    int sum2 = Study_Sum_Arr(&arr[2], n - 2);
    cout << "sum2=" << sum1 << endl; // 120

    Study_revalue(2, arr, n); // 函数内部修改了原数组
    // 如果只是为了打印数组,为了防止函数内部修改数组,可以传递const
    Study_display(arr, n); // arr并非是常量指针,但是可以传递 : 20  40  60  80  100

    //  当然也可以定义常量指针传递
    int  ar[n] = { 0,1,2,3,4 };
     int const* arp = ar;
    Study_display(arp,n); 

    // 使用双指针确定原数组的信息,从而进行计算
    int sum3 = Study_Sum_Arr__(arr, arr+n);
    cout << "sum3=" << sum3 << endl; // 150*2=300

    // 二维数组是int(*)[4]类型，int(*)表示是一个指针(数组),具有4个元素
    int arr_2d[3][4] = { {1,2,3,4},{5,6,7,8},{9,10,11,12} }; // 定义二维数值数组
    int(*p)[4] = arr_2d;  
    cout << "p=" << p << "   *p=" << *p << "   p+1=" << p + 1 << "   *(p+1)="<< *(p+1)<<endl;
    // p=000000AD9B73F368   *p=000000AD9B73F368   p+1=000000AD9B73F378   *(p+1)=000000AD9B73F378
    cout << "**p=" << **p <<"   *(*(p + 1))="<< * (*(p + 1)) << endl;
    // **p = 1    * (*(p + 1))=5 , 是2个一维数组的首元素
    cout << "arr_2d=" << arr_2d << "   *arr_2d="<<*arr_2d << "   arr_2d[0]="<<arr_2d[0] <<"   *arr_2d[0]="<< * arr_2d[0] << endl;
    // 二维数组名是地址，解引用还是地址(因为元素实际上是3个一维数组的地址)，也是首元素的地址
    // arr_2d=000000E68D4FFA48   *arr_2d=000000E68D4FFA48   arr_2d[0]=000000E68D4FFA48   *arr_2d[0]=1
    int sum_2d = Study_Sum_Arr_2D(arr_2d,4);
    cout << "sum_2d=" << sum_2d << endl;
    int* arr2p1 = arr_2d[1]; // 1个指针，指向二维数组的次元素
    int* arr2p2[4] = { arr_2d[0],arr_2d[1],arr_2d[2],arr_2d[3] };// 4个指针的指针数组
    // 无论arr2p1还是arr2p2[4]都不是arr_2d，所以Study_Sum_Arr_2D函数不能使用int *arr[4]定义形参
    // 应当使用int (*arr)[4]定义

    // 函数与C风格字符串
    char name[10] = "chenbei";
    char const* n1 = "chenbei"; // 常量字符串必须使用const 常量指针指向
    int num1 = Study_Str_Count(name, 'e'); // 可以直接传入数组名name，因为这里name也是指针
    int num2 = Study_Str_Count(n1, 'e'); // 也可直接传入指针
    cout << "num1=" << num1 << "   num2=" << num2 << endl;

    const int n2 = 10;
    int c2 = '+';
    char* p2 = Study_return_strs(c2, n2);
    cout << "p2="<<p2 << "  *p2="<<*p2<< endl; // 可以直接打印指针，看成数组名即可
    char p3[n2+1]; // p2需要销毁,用p3存好
    for (int i = 0; i < n2; i++ )
    {
        p3[i] = *p2;
        p2++; // 0--->10
    }
    for (int i = 0;  i < n2; i++) 
    {
        cout << p3[i] ;
        p2--;//纠正p2位置
    }
    
    delete[] p2; // 销毁内存




}

int Study_Sum_Arr(int arr[], int n)
{
    int total = 0;
    cout << "func：sizeof(arr)=" << sizeof(arr) << endl; // func：sizeof(arr) = 8,指针变量本身的长度是8，一个字节8位
    // 这也是为何需要显示指定n为数组长度，而不能使用sizeof进行判断
    for (int i = 0; i < n; i++)
    {
        total = total + arr[i]; 
    }
    return total;
}
// 当且仅当函数头或函数原型中指针表示法int * arr 与 数组表示法int arr[]是等价的
// 在函数体中不能使用int arr[]说明arr是一个指针
int Study_Sum_Arr_(int* arr, int n)
{
    int total = 0;
    // arr为数组名被解释为指针，n为数组元素个数
    for (int i = 0; i < n; i++)
    {
        total = total + arr[i]; // 这里arr当成数组使用
    }
    return total;
}
void Study_revalue(int c, int* arr, int n)
{
    // 如果只是为了打印数组,为了防止函数内部修改数组,可以传递const
    for (int i = 0; i < n; i++)
        arr[i] *= c;
}
void Study_display(const int* arr,  int n) //int const arr[]也可以,int const *arr<=>const int *arr,
{
    //arr[0] = 1; //const限定了值不能修改，常量指针
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << "  ";
    }
    cout << endl;
}
int Study_Sum_Arr__(int const* begin ,int const* end)
{
    // 输入参数为常量指针
    // 除了给定数组的起始位置和元素个数，也可以给定区间来描述数组的信息,需要2个指针
   // 注意末尾指针是数组最后一个元素的后面，即arr[5]而非arr[4]，即传递arr和arr+n即可
    // 循环体也是STL标准模板库广义化的雏形
    int const* p; // 指向可以改变,p++合法
    int total = 0;
    for (p = begin; p != end; p++)
    {
        total = total + *p; // 只读,解引用
    }
    return total;
}
int Study_Sum_Arr_2D(int arr[][4], int r_size)
{
    // 定义还可以使用 int (*arr)[4]，不可以使用int *arr[4]
    // 对于int *arr[4] ，定义的是1个指针数组，有4个指针，每个指针指向数值地址
    //对于int (*arr)[4]，定义的是一个指向数组的指针，指针指向有4个元素的数组,故指针解引用还是地址，指针的范围是行数
    int total = 0;
    for (int r = 0 ; r <r_size;r++ )
        for (int c = 0; c < 4; c++)
        {
            total += arr[r][c];
        }
    return total;
}
unsigned int Study_Str_Count(const char* str, char ch)
{
    unsigned int total = 0;
    while (*str) // str是指针在while循环中会移动,为结束符时退出
    {
        if (*str == ch)
            total++;
        str++; // 移动指针,数组的话也看成指针
    }
    return total;
}
char* Study_return_strs(char c, int n)
{
    char* p = new char[n + 1]; // 开辟n+1的内存，最后1个存放/0
    p[n] = '\0';
    while (n-- > 0)
        p[n] = c;
    return p;
}