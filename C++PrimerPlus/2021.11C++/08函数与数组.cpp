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
	int const n = 5; // �ȼ�const int n = 5;
	int arr[n] = {10,20,30,40,50}; // arr[n]��n�����ǲ��ɱ��,������Ҫconst�޶�n
    cout << "arr=" << arr << "   " << "&arr[0]=" << &arr[0] << endl;// C++������������Ϊ���һ��Ԫ�صĵ�ַ
    cout << "main��sizeof(arr)=" << sizeof(arr)<<endl; // main��sizeof(arr)=20�����鳤��
	int total = Study_Sum_Arr(arr, n);  // ���ݵ�arr�ǵ�ַ
    cout << "total=" << total << endl;

    int sum1 = Study_Sum_Arr(arr+2, n-2);
    cout << "sum1=" << sum1 << endl; // 120

    int sum2 = Study_Sum_Arr(&arr[2], n - 2);
    cout << "sum2=" << sum1 << endl; // 120

    Study_revalue(2, arr, n); // �����ڲ��޸���ԭ����
    // ���ֻ��Ϊ�˴�ӡ����,Ϊ�˷�ֹ�����ڲ��޸�����,���Դ���const
    Study_display(arr, n); // arr�����ǳ���ָ��,���ǿ��Դ��� : 20  40  60  80  100

    //  ��ȻҲ���Զ��峣��ָ�봫��
    int  ar[n] = { 0,1,2,3,4 };
     int const* arp = ar;
    Study_display(arp,n); 

    // ʹ��˫ָ��ȷ��ԭ�������Ϣ,�Ӷ����м���
    int sum3 = Study_Sum_Arr__(arr, arr+n);
    cout << "sum3=" << sum3 << endl; // 150*2=300

    // ��ά������int(*)[4]���ͣ�int(*)��ʾ��һ��ָ��(����),����4��Ԫ��
    int arr_2d[3][4] = { {1,2,3,4},{5,6,7,8},{9,10,11,12} }; // �����ά��ֵ����
    int(*p)[4] = arr_2d;  
    cout << "p=" << p << "   *p=" << *p << "   p+1=" << p + 1 << "   *(p+1)="<< *(p+1)<<endl;
    // p=000000AD9B73F368   *p=000000AD9B73F368   p+1=000000AD9B73F378   *(p+1)=000000AD9B73F378
    cout << "**p=" << **p <<"   *(*(p + 1))="<< * (*(p + 1)) << endl;
    // **p = 1    * (*(p + 1))=5 , ��2��һά�������Ԫ��
    cout << "arr_2d=" << arr_2d << "   *arr_2d="<<*arr_2d << "   arr_2d[0]="<<arr_2d[0] <<"   *arr_2d[0]="<< * arr_2d[0] << endl;
    // ��ά�������ǵ�ַ�������û��ǵ�ַ(��ΪԪ��ʵ������3��һά����ĵ�ַ)��Ҳ����Ԫ�صĵ�ַ
    // arr_2d=000000E68D4FFA48   *arr_2d=000000E68D4FFA48   arr_2d[0]=000000E68D4FFA48   *arr_2d[0]=1
    int sum_2d = Study_Sum_Arr_2D(arr_2d,4);
    cout << "sum_2d=" << sum_2d << endl;
    int* arr2p1 = arr_2d[1]; // 1��ָ�룬ָ���ά����Ĵ�Ԫ��
    int* arr2p2[4] = { arr_2d[0],arr_2d[1],arr_2d[2],arr_2d[3] };// 4��ָ���ָ������
    // ����arr2p1����arr2p2[4]������arr_2d������Study_Sum_Arr_2D��������ʹ��int *arr[4]�����β�
    // Ӧ��ʹ��int (*arr)[4]����

    // ������C����ַ���
    char name[10] = "chenbei";
    char const* n1 = "chenbei"; // �����ַ�������ʹ��const ����ָ��ָ��
    int num1 = Study_Str_Count(name, 'e'); // ����ֱ�Ӵ���������name����Ϊ����nameҲ��ָ��
    int num2 = Study_Str_Count(n1, 'e'); // Ҳ��ֱ�Ӵ���ָ��
    cout << "num1=" << num1 << "   num2=" << num2 << endl;

    const int n2 = 10;
    int c2 = '+';
    char* p2 = Study_return_strs(c2, n2);
    cout << "p2="<<p2 << "  *p2="<<*p2<< endl; // ����ֱ�Ӵ�ӡָ�룬��������������
    char p3[n2+1]; // p2��Ҫ����,��p3���
    for (int i = 0; i < n2; i++ )
    {
        p3[i] = *p2;
        p2++; // 0--->10
    }
    for (int i = 0;  i < n2; i++) 
    {
        cout << p3[i] ;
        p2--;//����p2λ��
    }
    
    delete[] p2; // �����ڴ�



    system("pause");
}

int Study_Sum_Arr(int arr[], int n)
{
    int total = 0;
    cout << "func��sizeof(arr)=" << sizeof(arr) << endl; // func��sizeof(arr) = 8,ָ���������ĳ�����8��һ���ֽ�8λ
    // ��Ҳ��Ϊ����Ҫ��ʾָ��nΪ���鳤�ȣ�������ʹ��sizeof�����ж�
    for (int i = 0; i < n; i++)
    {
        total = total + arr[i]; 
    }
    return total;
}
// ���ҽ�������ͷ����ԭ����ָ���ʾ��int * arr �� �����ʾ��int arr[]�ǵȼ۵�
// �ں������в���ʹ��int arr[]˵��arr��һ��ָ��
int Study_Sum_Arr_(int* arr, int n)
{
    int total = 0;
    // arrΪ������������Ϊָ�룬nΪ����Ԫ�ظ���
    for (int i = 0; i < n; i++)
    {
        total = total + arr[i]; // ����arr��������ʹ��
    }
    return total;
}
void Study_revalue(int c, int* arr, int n)
{
    // ���ֻ��Ϊ�˴�ӡ����,Ϊ�˷�ֹ�����ڲ��޸�����,���Դ���const
    for (int i = 0; i < n; i++)
        arr[i] *= c;
}
void Study_display(const int* arr,  int n) //int const arr[]Ҳ����,int const *arr<=>const int *arr,
{
    //arr[0] = 1; //const�޶���ֵ�����޸ģ�����ָ��
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << "  ";
    }
    cout << endl;
}
int Study_Sum_Arr__(int const* begin ,int const* end)
{
    // �������Ϊ����ָ��
    // ���˸����������ʼλ�ú�Ԫ�ظ�����Ҳ���Ը��������������������Ϣ,��Ҫ2��ָ��
   // ע��ĩβָ�����������һ��Ԫ�صĺ��棬��arr[5]����arr[4]��������arr��arr+n����
    // ѭ����Ҳ��STL��׼ģ�����廯�ĳ���
    int const* p; // ָ����Ըı�,p++�Ϸ�
    int total = 0;
    for (p = begin; p != end; p++)
    {
        total = total + *p; // ֻ��,������
    }
    return total;
}
int Study_Sum_Arr_2D(int arr[][4], int r_size)
{
    // ���廹����ʹ�� int (*arr)[4]��������ʹ��int *arr[4]
    // ����int *arr[4] ���������1��ָ�����飬��4��ָ�룬ÿ��ָ��ָ����ֵ��ַ
    //����int (*arr)[4]���������һ��ָ�������ָ�룬ָ��ָ����4��Ԫ�ص�����,��ָ������û��ǵ�ַ��ָ��ķ�Χ������
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
    while (*str) // str��ָ����whileѭ���л��ƶ�,Ϊ������ʱ�˳�
    {
        if (*str == ch)
            total++;
        str++; // �ƶ�ָ��,����Ļ�Ҳ����ָ��
    }
    return total;
}
char* Study_return_strs(char c, int n)
{
    char* p = new char[n + 1]; // ����n+1���ڴ棬���1�����/0
    p[n] = '\0';
    while (n-- > 0)
        p[n] = c;
    return p;
}