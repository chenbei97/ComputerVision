#include "contanter.h"
/*
<1>string 的概念
     string 是一个类 char*是一个指针
     string内部封装了char* 管理这个字符串 是一个 char*的容器
     string内部有find、copy、delete、replace和insert等方法
<2>string的构造函数
     2.1 string(); ---->使用一个空的字符串 如 string str;
     2.2 string(const char* s) ;---->使用字符串s初始化
     2.3 string(const string & str) ;---->使用一个string对象初始化 另一个string对象
     2.4 string(int n ,char c) ;----> 使用n个字符c初始化
<3>string的赋值操作(运算符重载)
    3.1 string& operator = (const char *s) ; // 指向固定字符的指针 赋给字符串
    3.2 string& operator = (const string &s) ; // 指向固定字符串的引用 赋给字符串
    3.3 string& operator = ( char c) ; // 字符值传递  赋给字符串
    3.4 string& assign = (const char *s) ; // 把字符串s 赋给字符串
    3.5 string& assign = (const char *s ,int n) ; // 指向固定字符的指针 前n个字符 赋给字符串
    3.6 string& assign = (const  string &s) ; // 指向固定字符串的引用 赋给字符串
    3.7 string& assign= (int n , char s) ; // 字符值传递  赋给字符串
<4>string的字符串拼接
    4.1 string& operator += (const char *str) ; // 直接拼接常量字符串
    4.2 string& operator += (const char s) ; // 拼接常量字符(值传递)
    4.3 string& operator += (const string& str) ; // 拼接变量字符串(引用传递)
    4.4 string& append (const char *s) ; // 拼接常量字符(地址传递)
    4.4 string& append (const char *s ,int n) ;// 拼接前n个常量字符(地址传递)
    4.5 string& append (const string &s) ;// 拼接变量字符串(引用传递)
    4.6 string& append (const string &s , int pos , int n) ;// 拼接变量字符串从pos开始的n个字符(引用传递)
<5>string的查找和替换(函数声明后边跟着const表示该函数不能修改类成员属性或函数)
    5.1 int find(const string & str , int pos=0) const ;// 查找str第一次出现位置 从pos查找
    5.2 int find(const char * s , int pos=0) const ; // 同 5.1
    5.3 int find(const  char * s , int pos=0, int n) const ; 从pos位置出现的前n个字符第一次出现位置
    5.4 int find(const  char c , int pos=0) const ; // 常量字符
    5.5 int rfind(const string &str , int pos=npos ) const ; // 从右边开始数的pos位置查找最后一次位置
    5.6 int rfind(const char *s , int pos=npos ) const ;  //常量字符串指针
    5.7 int rfind(const char c , int pos=npos ) const ; // 常量字符
    5.8 string& replace(int pos, int n , const string& str) ; //  替换为变量字符串
    5.9 string& replace(int pos , int n , const char *s) ;  //  替换为常量字符串
<6>字符串比较 ： 按ASCII码逐个比较
    6.1 int compare(const string &s) const ; // 与变量字符串进行比较
    6.2 int compare(const  char *s) const ; // 与常量字符串进行比较
<7>字符存取
    7.1 char & operator[] (int n) ; // 通过[]方式获取字符
    7.2 char & at(int n) ; // 通过at 方法获取
<8>字符串插入和删除
    8.1 string & insert(int pos , const char *s) // 插入常量字符串
    8.2 string & insert(int pos , const string & str) // 插入变量字符串
    8.3 string & insert(int pos , int n ,char c ) // 指定位置插入n个字符
    8.4 string & erase(int pos , int n = npos)  // 删除从pos开始的n个字符
<9>字串获取
    9.1 string substr(int pos = 0 , int n = npos) // 从pos开始截取n个字符
 */
void test_0025()
{
    // 6.1 int compare(const string & s) const; // 与变量字符串进行比较

    string str1 = "hello";
    string str2 = "hello";
    string str3 = "xello";
    cout << str2.compare(str1) << endl;
    cout << str2.compare(str3)<<endl;
    if (str1.compare(str2) == 0)
    {cout << "相等" << endl;}else { cout << "不相等" << endl; }
    //6.2 int compare(const  char* s) const; // 与常量字符串进行比较
    // 7.1 char& operator[] (int n); // 通过[]方式获取字符
    cout <<str2[2]<< endl;
    // 7.2 char& at(int n); // 通过at 方法获取
    cout << str3.at(2) << endl;
    // 8.1 string & insert(int pos , const char *s) // 插入常量字符串
    str1.insert(3,"chenbei");
    cout << str1 << endl;
    // 8.4 string & erase(int pos , int n = npos)  // 删除从pos开始的n个字符
    str1.erase(3, 7);
    cout << str1 << endl;
    // 9.1 string substr(int pos = 0, int n = npos) // 从pos开始截取n个字符
    cout << str1.substr(3, 2) << endl;
}
void test_0024()
{
    //5.1 int find(const string & str, int pos = 0) const;// 查找str第一次出现位置 从pos查找
    string str1 = "0123456789";
    int pos = str1.find("h", 0);// -1
    cout <<pos <<endl; //d的位置从0数为3
    //5.5 int rfind(const string & str, int pos = npos) const; // 从pos位置查找最后一次位置
    int pos1 = str1.rfind("8", 8);
    cout << pos1  << endl; // 8 虽然从右往左找 但是返回的位置还是从左往右的顺序
    //5.9 string & replace(int pos, int n, const char* s);  //  替换为常量字符串
    str1.replace(2, 4, "chen"); // 2345被替换chen ：01chen6789
    cout << str1 << endl;
    str1 = "0123456789"; // 234被替换为chen ： 01chen56789
    str1.replace(2, 3, "chen");
    cout << str1 << endl;

}
void test_0023()
{
    //4.1 string & operator += (const char* str); 
    string str1 = "playing ";
    str1 += "game ";
    //4.2 string & operator += (const char s); 
    str1 += '!';
    //4.3 string & operator += (const string & str); 
    string str2 = "I am ";
    str2 += str1;
    //4.4 string & append(const char* s);
    string str3 = "I love ";
    str3.append("basketball");
    //4.4 string & append(const char* s, int n);
    string str4;
    str4.append("I love basketball" , 6);
    //4.5 string & append(const string & s);
    string str5;
    str5.append(str3, 6);
    //4.6 string & append(const string & s, int pos, int n);
    string str6;
    str6.append(str3, 6, 7);
    cout << str1 << endl;
    cout << str2 << endl;
    cout << str3 << endl;
    cout << str4 << endl;
    cout << str5 << endl;
    cout << str6 << endl;

}
void test_0021()
{
    // 2.1 默认构造
    string s1;
    // 2.2 使用字符串构造
    const char *  str = "chenbei"; // pointer to const char  一个指向常量字符地址str的指针
    string s2(str);
    cout << s2 << endl;
    // 2.3 使用一个字符串拷贝构造(字符串的常量引用)
    string s3(s2);
    // 2.4 初始化n个字符
    string s4(10, 'a');
    cout << s4 << endl; 
}
void test_0022()
{
    //3.1 string & operator = (const char* s); 
    string str1;
    // 将 "hello world"看成char的常量数组,也即常量指针指向char数组地址
    str1 = "hello world"; 
    //3.2 string & operator = (const string & s); 
    // 把str1看成整体的字符串 引用传递
    string str2 = str1;
    //3.3 string & operator = (char c); 
    string str3 ; // 直接 string str3 = 'a' ;是不行的 构造函数没有char到string‘的隐式转换
    str3 = 'a';
    //3.4 string & assign = (const char* s); 
    string str4;
    str4.assign("hello c++"); // 与3.1是没什么区别的 就是函数直接构造了
    //3.5 string & assign = (const char* s, int n); 
    string str5;
    str5.assign("hello c++", 5);
    //3.6 string & assign = (const  string & s); 
    string str6;
    str6.assign(str4, 5); // 与3.5的区别只在于对象是字符串和字符串变量
    //3.7 string & assign = (int n, char s); 
    string str7;
    str7.assign(5, 'a'); 
    cout << str1<< endl;
    cout << str2 << endl;
    cout << str3 << endl;
    cout << str4 << endl;
    cout << str5 << endl;
    cout << str6 << endl;
    cout << str7 << endl;
}
int string_containter()
//int main()
{
    //vector_containter();
    test_0021();
    test_0022();
    test_0023();
    test_0024();
    test_0025();
    return 0;
}