## 1.数组

### 1.1数值数组

​	初始化的方式，可以不指定值，也可以指定值

```c++
int arr1[4];
int arr2[3] = {0,1,2};
int arr3[4] = {}
int arr[] = { 0,1,2 }; // 自动推断
```

​	直接打印数组名arr与对数组首元素取地址&arr[0]是相同的，数值上也等于直接取数组的地址&arr

​	&arr本身实际上是包含了整个数组arr的地址，可以理解为是一个装满所有地址的数组，打印&arr实际上打印的是第1个地址，所以数值上表现相同，但是本质上是不同的

​	对数组索引、数组地址解引用、指向数组的指针解引用都是等价的

```c++
int arr[] = { 0,1,2 };
int* p = &arr[0];
cout << "arr=" << arr <<" &arr[0]="<<&arr[0]<<" &arr="<<&arr<<endl;
cout << "*(arr+1)=" << a << " arr[1]="<< arr[1] << " *(p+1)="<<*(p +1) << endl;// *(arr+1)和arr[1]和*(p+1)等价
```

#### 1.1.1二维数组

```c++
int temp[3][2] = { {0,1}, {2,3}, {3,4} }; // 使用逗号隔开
```



#### 1.1.2数组和指针的sizeof

​	整型arr占据了3个字节，每个字节8位，所以sizeof(arr)=24

​	sizeof(arrp)返回的是指针的长度,1个字节8位,所以sizeof(arrp)=8

​	其实不仅仅整型数组int的指针长度为8，对于short、char、double数组的指针长度也是8

```c++
int arr[] = { 0,1,2 };
int* arrp = &arr[0];
cout << "sizeof(arr)=" << sizeof(arr) << " sizeof(arrp)=" << sizeof(arrp) << endl;
```



### 1.2字符数组

​	不同于数值数组，打印字符串数组名并不给出地址，而是直接打印出内容

​	这是因为cout被提供给1个字符的地址，就会打印该地址上的 字符，然后继续下去直到遇见结束符/0

​	如果一定想要打印字符串的地址，则需要int* 类型转换，可以转换数组本身也可以转换指向数组的指针

​	在cout和大多数c++表达式中，char数组名、char指针以及引号括起的字符串常量都被解释为第1个字符的地址

```c++
char name[20]={};
char dog[4] = { 'd','o','g','\0'}; //  C风格字符串必须加结束符号才是字符串
char str[] = "chenbei"; // C++ 风格，隐含了结束符

char flower[10] = "flower";
// !! 双引号和单引号不能互换，"s",'s'是不同的，后者是字符，前者除了还隐式的包含了/0
char* f1 = flower; // 不会赋值新内存
cout << "flower=" << flower << " f1="<<f1<<" flower"<< endl; // 都是flower 
cout << "(int*)flower=" << (int*)flower << " (int*)f1=" << (int*)f1 << endl;// 地址相同
cin >> flower;
f1 = new char [strlen(flower) + 1]; // 使用new可以动态分配内存，更改f1的指向，指向新内存
strcpy_s(f1,strlen(flower)+1,flower); // 输入的值复制到新内存
cout << "(int*)flower=" << (int*)flower << " (int*)f1=" << (int*)f1 << endl;// 地址不同
```

### 1.3动态数组

​	可以使用new创建动态数组，而非事先声明分配内存创建数组

```c++
int* name = new int [10] ;//name保存的是第1个元素的地址
delete [] name ; // 动态数组也需要delete [] 进行释放
```

​	动态数组的访问类似于数组，但是又有区别；指针+1运算是字节数+1

​	对数组索引、数组地址解引用、指向数组的指针解引用都是等价的：

​	如果直接使用数组索引下标也是可以的，但是C++内部会将其转换为指针运算，即arr[1]--->*(arr+1)

​	等价于p[1]--->*(p+1)，其中p是指向arr首地址的指针，可以认为此时arr和p是等价的，但是略有又不同，例如直接对arr+1运算是错误的,p+1运算是可以的

```c++
// 访问动态数组：指针和数组在某些情况是等价的
int* p = new int[10];
p[0] = 1;
p[1] = 2;
p[2] = 3;
int arr[3] = {0,1,2};
int* ap = &arr[0];
// 对数组索引、数组地址解引用、指向数组的指针解引用都是等价的
cout << "arr=" << arr <<" &arr[0]="<<&arr[0]<< endl;// arr和&arr[0]相同
cout << "*(arr+1)=" << a << " arr[1]="<< arr[1] << " *(ap+1)="<<*(ap +1) << endl;// *(arr+1)和arr[1]和*(ap+1)等价

cout << "before p[0]=" << p[0] << endl;
// 指针与数组的不同处,指针是变量可以移动
p = p + 1; // 指针移动到下1个元素的地址
// arr = arr +1 ; 非法,但是解引用是合法的
int a = *(arr+1) ;
cout <<"*(arr+1)="<<a << endl;
cout << "after p[0]=" << p[0] << endl;
p = p - 1; // 返回正确的地址再进行delete
delete [] p;
```



## 2.结构体/共用体

### 2.1结构体struct

```c++
struct Person
{
    int age = 0;
    double len = 0.1;
}person1; // 可以在分号前实例化1个对象
```

#### 2.1.1动态结构

​	结构是一种数据类型，如果需要创建指向这种数据类型的指针，也要用该结构去定义指针

```c++
struct Person
{
    int age = 18;
    char name[10] = "cb";
}wife;
Person* w = &wife; // 这里w指向结构体实例wife本身的地址，也要用Person去定义指针
cout << "&wife=" << &wife << endl;
// cout << "*(w)" << *(w)<< endl; 非法,结构体不能解引用
cout << "*(w->name)" << *(w->name+1) << endl;// c  结构体成员可以解引用，"cb"的地址为c的地址,+1解引用为b
cout << "w->wife=" << w->name << endl;
```

​	结构本身也可以定义数组

```c++
Person wifes[3];
cout << "(wifes+1)->name" << (wifes + 1)->name << endl;
```

​	还可以创建指针数组,每个指针都指向结构体

```c++
wifes[1].age = 100;
Person* pwifes[3] = { &wifes[0], &wifes[1] ,&wifes[2] };
cout << "pwifes[1]->age=" << pwifes[1]->age << endl;//pwifes[1]->age=100
```

​	还可以创建指向该指针数组的指针,需要使用**

​	如果直接定义类型容易出错,可以使用auto

```c++
Person** ppwifes = pwifes;//pwifes是个数组，也就是指针数组的首个指针的地址
cout <<"(*(ppwifes + 1))->age="<< (*(ppwifes + 1))->age << endl;
// (ppwifes + 1)是个指向指针数组第2个元素指针,解引用后还是指针,且必须多加个括号,直接使用*(ppwifes + 1)->age是错误的
// 如果直接定义类型容易出错,可以使用auto
auto ppwifes_ = pwifes;
```



#### 2.1.2箭头和句点运算符的使用

```c++
// 也可以使用动态new创建指针,指针都需要箭头运算符→指向成员,使用句点运算符也可以,需要先解引用
Person* w1 = new Person; 
// 访问成员的2种方式
cout << "w1->name=" << w1->name << " (*w1).name=" << (*w1).name << endl;
```



### 2.2共用体union

​	结构体和共用体都可以存储的不同的数据类型，但是共用体使用的时候只能存在1种类型

​	常见的使用情况是函数的参数有2种类型，可以传入字符串，也可以传入整型，但是只能是其中1种，可以在结构体依据类型判断

```c++
struct Person
{
    int age = 0 ;
    double len = 0.1 ;
    int id_type = 0 ;
    union id 
    {
        id_int = 101;
        // char id_str[20] = "123"; 非法,只能初始化1个
        char id_str[20];
    }id1; // 也可以直接初始化1个实例
}p1;
if (p1.id_type==0)
{
    strcpy_s(p1.id.id_str,  "chenbei"); // 不能直接使用p1.id.id_str="cb"赋值
    cout << p1.id.id_str << endl;
}
```

## 3.枚举类型

​	enum 初始化有2种方式：默认初始化、显式初始化

​	默认初始化方式是每个枚举值依次从0,1,2,..开始赋值

​	显式初始化可以指定相同的枚举值，枚举实例化时可以实例化在枚举值的范围内（不过从调试结果来看范围限制不遵循下述规则）

```c++
enum color1 {blue,red,green} // 枚举类型color可以看成1个类,还需要这个类创造实例
// 定义枚举类型,默认blue=0,red=1,green=2
color1 c11 =  red ; // 实例化并赋值
// color1 c12 = 1; 非法 不能使用整型作为枚举型进行赋值
// c11 = c11 + 1; 非法 枚举类型自身没有算术运算
//color1 c14 = blue + red; 枚举之间的算术计算也是非法的
cout <<"c11="<< c11 << endl; // c1 = 1 
int c13 = red + 4 ; // 枚举型可以参与整型运算

enum color2 { blue1 = 0, red1 = 2, green1 = 8 };// 显式的定义枚举值,指定值必须是整数
color2 c21;
c21 = color2(-65536); // 虽然6不是color1的枚举值,但是在范围内也是合法的
/*
	枚举值范围的计算：
	上限：找到1个2的最小幂数使之大于最大枚举值+1，然后再减去1，如2^4>8+1，上限为16-1=15
	下限：如果枚举值没有小于0的则下限为0，否则找到1个负的2的最大幂数使之小于最小枚举值，然后+1,如-2^3<-6-1,下限为-8+1=-7
	不过从调试结果来看，范围似乎没有上下限
*/

enum color3 {blue2,red2,green2=1,gray1=1}; // 枚举值相同也可以，也可以不指定某些值

```

## 4.指针

### 4.1定义指针

​	定义指针有2种方式，一种是直接定义，一种是借助地址运算符&定义

​	直接定义：int*p; 有2种理解方式，侧重点含义不同

```c++
int  *p1 ; // C风格定义指针，强调*p1是一个int类型
int* p2 ; //  C++风格 要将int*看成一种数据类型, 强调p2是一个指针类型
int  *p3, p4=5; // 同时定义时使用C风格更容易理解 , p4是整型,*p3也是整型 

```

​	间接定义：指向某个变量的指针需要事先定义变量，否则指针不指向内存成为野指针

```c++
int a = 5 ;
int* p1 = &a ;
int* p2 ;
// *p2 = 1000 ; 非法,p2不指向任何内存,1000不能存储

```

### 4.2指针赋值

#### 4.2.1强制类型转换赋值

 	直接赋予16进制值在C_98之前允许，但是现在必须要强制转换类型才能赋值

```c++
int* p ;
// pt = 0xB80000 ; 不允许
pt = (int*) 0xB80000 ; // 必须类型转换为 整型指针类型
```

#### 4.2.2使用new赋值

​	还可以使用new运算符给指针分配地址,规则为 *typeName* * *pointer_name* = *new* *typeName*

​	不过new的内存是没有名称的，只有指针可以访问，存储在堆区heap或自由存储区free store

```c++
int* p = new int ;
*p = 5 ;
delete p ;
// delete p ; 不可再次删除,delete删除的不是p本身,而是p指向的内存
int* p1 = p ; // 虽然没有错误,但是最好不要2个指针指向同一个内存,因为delete p1会导致二次释放内存

int a = 0 ;
int* p2 = &a;
// delete p2 ; 非法,delete只用于删除new分配的内存

int* name = new int [10] ;//name保存的是第1个元素的地址
delete [] name ; // 动态数组也需要delete [] 进行释放

```

总结：

- 不要使用delete释放不是new分配的内存

- 不要使用delete释放相同内存2次

- 使用new[]为数组分配内存，也要使用delete[]释放内存

- 对空指针使用delete是安全的

  

#### 4.2.3 delete和new可以分开放

```c++
char* Study_pointer_getname(void)
{
    char temp[3];
    cin >> temp;
    char* p = new char[strlen(temp) + 1]; // 局部函数new
    strcpy_s(p, strlen(temp) + 1,temp);
    return p;
}
int main()
{
    char name[5] ;
    char *c1 = name ;
    c1 =  Study_pointer_getname();//该函数new的内存在本函数中delete
	cout << "(int*)c1=" << (int*)c1 << endl;
	delete [] c1; // 主函数必须释放内存
    return 0;
}
```

### 4.3常量指针和指针常量

​	常量指针是指向常量的指针，指针的指向可以改变，但是指向的内容不能改变，它可以指向不同常量

```c++
int const *a; // const限定的是*a，也就是指针解引用的值不能改变，等价于const int *a ;
int b, c;
a = &b; // a的指向可以改变
a = &c; // a的指向可以改变
// *a=20;  a指向的值不能改变
```

​	指针常量是指：指针本身是常量，也就是指向的地址不发生改变，但地址里的内容可以通过指针改变，注意的是指针常量在定义时必须同时赋初值，否则成为野指针

```c++
int a=10 ,b;
int*  const p = &a; // const限定的是p，p是一个指针，也就是指向的地址不能改变，必须赋予初值
// p = &b; p的指向不能改变
// p = NULL; 指向NULL也是非法的
*p = 20 ; // 可以改变a的值
```

​	一个微妙的问题是，**<u>对一个指向a的常量指针p来说，说明的是对自身p而言，a是常量，并不是a就是常量；a可以通过别的普通指针进行修改，但是不能通过这个指针p来修改</u>**，这是需要理解的地方！！！

#### 4.3.1零级指针(指向变量的指针*)

​	指向的变量有2种类型，可定义的指针有3种，所以0级指针（指针与变量之间）的定义存在6种情况：

- 将常规变量的地址赋给常规指针
- 将常规变量的地址赋给常量指针
- 将常规变量的地址赋给指针常量
- 将const变量的地址赋给常规指针 （无效），因为能赋值的话意味着常规指针可以修改const变量的值，这与const本身冲突
- 将const变量的地址赋给常量指针
- 将const变量的地址赋给指针常量（无效），指针常量也可以修改值，与const本身冲突

```c++
// <1> 0级指针(指针与变量之间)
int  a = 0 ,  tem_a =0;
// 1.常规变量地址-->常规指针
int* pa = &a;
pa = &tem_a; // 改变地址合法
*pa = 1; // 改变值合法
// 2.常规变量地址-->常量指针
int const* cpa = &a;
cpa = &tem_a; // 改变地址合法
// *cpa = 1;  改变值非法
// 3.常规变量地址-->指针常量
int* const pca = &a;
// pca = &tem_a; 改变地址非法
*pca = 1; // 改变值合法
// 4. const变量地址-->常规指针(无效)
const int b = 0;
int const c = 0; // int const和const int是等价的
// int* pb = &b;  非法,const变量地址不能改变与普通指针可改变值冲突
// 5.const变量地址-->常量指针
int const* cpb = &b;
const int* cpb_ = &b;// int const* 和const int*等价
cpb = &c; // 改变地址合法
//*cpb = 1; 改变值非法
// *cpb_ = 1 ; 改变值非法
//6.const变量地址-->指针常量(无效)
// int* const pcb = &b; 非法,const变量地址不能改变与指针常量可改变值冲突
```

#### 4.3.2一级指针(指向指针变量的指针*)

​	指向的指针有3种情况，定义指针也有3种可能，所以指向指针变量的指针存在9种情况：

​    <u>**一级常规指针的指向和值均可改变，无论指向常规指针还是指针常量**</u>

- 一级常规指针指向0级常规指针,改变值和指向合法（前者值可变，后者值可变；前者方向可变，后者方向可变）

- 一级常规指针指向0级常量指针（无效）（前者值可变，后者值不可变，冲突！）

- 一级常规指针指向0级指针常量.改变值和指向合法（前者值可变，后者值可变；前者方向可变，后者方向不可变，**<u>前者决定后者</u>**）

  

  **<u>一级常量指针指向常规指针和常量指针时改变指向合法，改变值非法，前者决定后两者</u>**

  **<u>一级常量指针指向指针常量时，改变指向非法，改变值合法，后者决定前者</u>**

- 一级常量指针指向0级常规指针,改变指向合法,改变值非法（前者值不可变，后者值可变，前者决定后者；前者方向可变，后者方向可变）

- 一级常量指针指向0级常量指针,改变指向合法,改变值非法（前者值不可变，后者值不可变；前者方向可变，后者方向可变）

- 一级常量指针指向0级指针常量,改变指向非法,改变值合法（前者值不可变，后者值可变，后者决定前者；前者方向可变，后者方向不可变，后者决定前者）

  

  <u>**一级指针常量指向常规指针和指针常量时改变指向非法，改变值合法，前者决定后两者**</u>

  <u>**一级指针常量指向常量指针，改变指向合法，改变值非法，后者决定前者**</u>

- 一级指针常量指向0级常规指针,改变指向非法,改变值合法（前者值可变，后者值可变，后者决定前者；前者方向不可变，后者方向可变，前者决定后者）

- 一级指针常量指向0级常量指针,改变指向合法,改变值非法（前者值可变，后者值不可变，后者决定前者；前者方向不可变，后者方向可变，后者决定前者）

- 一级指针常量指向0级指针常量,改变指向非法,改变值合法（前者值可变，后者值可变；前者方向不可变，后者方向不可变）

  

  从结果来看，可以总结出规律~：

- 一级常规指针<<>>常规指针（一致）

- 一级常规指针<<!>>常量指针（冲突）

- 一级常规指针>>指针常量（有常规指针参与的不同指针之间，指向的决定被指向）

- 一级常量指针>>常规指针（有常规指针参与的不同指针之间，指向的决定被指向）

- 一级常量指针<<>>常量指针（一致）

- 一级常量指针<<指针常量（指针常量和常量指针之间，被指向的决定指向）

- 一级指针常量>>常规指针（有常规指针参与的不同指针之间，指向的决定被指向）

- 一级指针常量<<常量指针（指针常量和常量指针之间，被指向的决定指向）

- 一级指针常量<<>>指针常量（一致）

```c++
int a1 = 0, a2 = 0;
int const b1 = 0, b2 = 0;
//<2> 一级指针(指向指针的指针与指向变量的指针)
int* pa1 = &a1; // 常规指针指向常规变量a1
int* pa2 = &a2; // 常规指针指向常规变量a2
int const* pca1 = &a1; // 常量指针指向常规变量a1
int const* pca2 = &a2; // 常量指针指向常规变量a2
int* const cpa1 = &a1; // 指针常量指向常规变量a1
int* const cpa2 = &a2; // 指针常量指向常规变量a2

// 常规指针指向const变量b1,b2(非法)
// 指针常量指向const变量b1,b2(非法)
int const* pcb1 = &b1; // 常量指针指向const变量b1
int const* pcb2 = &b2;// 常量指针指向const变量b2

// 一级常规指针：ppa1_1、ppa1_2、ppa1_3
// 1.一级常规指针指向0级常规指针(pa1,pa2)
cout << "1.一级常规指针指向0级常规指针(pa1,pa2)" << endl;
int* ppa1_1 = pa1;
ppa1_1 = pa2; // 改变指向合法,指向其他指针
ppa1_1 = &a2; // 改变指向合法,指向1个地址
*ppa1_1 = 2; // 改变值合法,指向指针的指针,可以改变常规指针指向的值
cout << "	一级常规指针，可以改变指向，指向0级常规指针pa1的ppa1_1可指向pa2和&a2" << endl;
cout << "	*ppa1_1=" << *ppa1_1 << "  *pa2=" << *pa2 << "  a2=" << a2 <<
    "   .一级常规指针，可以改变0级常规指针指向的值"<< endl;//*ppa1_1=2  *pa2=2  a2=2
// 2. 一级常规指针指向0级常量指针(pca1,pca2) 非法
cout << "2. 一级常规指针指向0级常量指针(pca1,pca2) 非法" << endl;
// int* ppa1_2 = pca1; 非法,一级常规指针可以改变值与0级常量指针不可改变值冲突
cout << "	一级常规指针，不能指向0级常量指针，一级常规指针可以改变值与0级常量指针不可改变值冲突" << endl;
// 3.一级常规指针指向0级指针常量(cpa1,cpa2)
cout << "3.一级常规指针指向0级指针常量(cpa1,cpa2)" << endl;
int* ppa1_3 = cpa1;
ppa1_3 = cpa2; // 改变指向合法,指向其他指针
ppa1_3 = &a2;  //改变指向合法,指向1个地址
*ppa1_3 = 3; // 改变值合法,指向指针的指针,可以改变指针常量指向的值
cout << "	一级常规指针，可以改变指向，指向0级指针常量cpa1的ppa1_3可指向cpa2和&a2" << endl;
cout << "	*ppa1_3=" << *ppa1_3 << "  *cpa2=" << *cpa2 << "  a2=" << a2 <<
    "   一级常规指针，可以改变0级指针常量指向的值" << endl;//*ppa1_1=3  *pa2=3  a2=3
cout << endl;

// 一级常量指针：ppca1_1、ppca1_2、ppca1_3
// 4.一级常量指针指向0级常规指针(pa1,pa2)
cout << "4.一级常量指针指向0级常规指针(pa1,pa2)" << endl;
int const *ppca1_1 = pa1;
ppca1_1 = pa2; // 改变指向合法,指向其他指针
ppca1_1 = &a2; // 改变指向合法,指向1个地址
cout << "	一级常量指针，指向0级常规指针pa1的ppca1_1可指向pa2和&a2，可以改变指向，不可改变值" << endl;
// *ppca1_1 = 1; 改变值非法
// 5.一级常量指针指向0级常量指针(pca1,pca2) 
cout << "5.一级常量指针指向0级常量指针(pca1,pca2) " << endl;
int const* ppca1_2 = pca1; 
ppca1_2 = pca2; // 改变指向合法,指向其他指针
ppca1_2 = &a2;// 改变指向合法,指向1个地址
// *ppca1_2 = 1; 改变值非法
cout << "	一级常量指针，指向0级常量指针pca1的ppca1_2可指向pca2和&a2，可以改变指向，不可改变值" << endl;
// 6.一级常量指针指向0级指针常量(cpa1,cpa2)
cout << "6.一级常量指针指向0级指针常量(cpa1,cpa2)" << endl;
int* const ppca1_3 = cpa1;
// ppca1_3 = cpa2; 改变指向非法
*ppca1_3 = 1; // 改变值合法
cout << "	一级常量指针，指向0级指针常量cpa1的ppca1_3不可指向cpa2和&a2，不可改变指向，可改变值" << endl;
cout << "	*ppca1_3=" << *ppca1_3 << "  *cpa1=" << *cpa1 << "  a1=" << a1 <<
    "   一级常量指针，可以改变0级指针常量指向的值" << endl;//*ppca1_3=1  *pa1=1  a1=1
cout << endl;

// 一级指针常量：pcpa1_1、pcpa1_2、pcpa1_3
// 7.一级指针常量指向0级常规指针(pa1,pa2)
cout << "7.一级指针常量指向0级常规指针(pa1,pa2)" << endl;
cout << "	一级指针常量，指向0级常规指针pa1的pcpa1_1不可指向pa2和&a2，不可改变指向，可改变值" << endl;
int* const pcpa1_1 = pa1;
// pcpa1_1 = pa2; 改变指向非法
*pcpa1_1 = 4; // 改变值合法
cout << "	*pcpa1_1=" << *pcpa1_1 << "  *pa1=" << *pa1 << "  a1=" << a1 <<
    "   .一级指针常量，可以改变0级常规指针指向的值" << endl;//*pcpa1_1=4  *pa1=4  a1=4

// 8.一级指针常量指向0级常量指针(pca1,pca2) 
cout << "8.一级指针常量指向0级常量指针(pca1,pca2) " << endl;
int const* pcpa1_2 = pca1;
pcpa1_2 = pca2; // 改变指向合法,指向其他指针
pcpa1_2 = &a2;// 改变指向合法,指向1个地址
// *pcpa1_2 = 5; 改变值非法
cout << "	一级指针常量，指向0级常量指针pca1的pcpa1_2可指向pca2和&a2，可以改变指向，不可改变值" << endl;
// 9.一级指针常量指向0级指针常量(cpa1,cpa2)
cout << "9.一级指针常量指向0级指针常量(cpa1,cpa2)" << endl;
int* const pcpa1_3 = cpa1;
// pcpa1_3 = cpa2; 改变指向非法
cout << "	一级指针常量，指向0级指针常量cpa1的pcpa1_3不可指向cpa2和&a2，不可改变指向，可改变值" << endl;
*pcpa1_3 = 6;
cout << "	*pcpa1_3=" << *pcpa1_3 << "  *cpa1=" << *cpa1 << "  a1=" << a1 <<
    "   一级指针常量，可以改变0级指针常量指向的值" << endl;//*pcpa1_3=6  *pa1=6  a1=6
cout << endl;
```

#### 4.3.3二级指针(指向指针地址的指针**)

​	二级指针指向的是一级指针的地址，而不是一级指针的值，必须使用**，关于这种情况的可能更加复杂，不再叙述

```c++
int a1 = 0;
int* pa1 = &a1 ;
// int** pt = &a1; 非法
// int** pt = pa1; 非法
int** pt = &pa1;
```

## 5.内存模型和名称空间

### 5.1存储类型

​	存储主要分为自动存储、静态存储和动态存储，C++11还引入了线程存储

- 自动存储：函数内部定义的常规变量通常存储在栈中，遵循后进先出原则，函数调用时内存存在，函数调用结束返回main时消失
- 静态存储：这种变量可以在函数外部定义，也就是main函数中定义，也可以使用static定义，这种变量可以存在于整个程序生命周期，也可以只存在于特定的函数执行，目前只能初始化静态数组和静态结构，对于自动数组和自动结构只在C++_Release2.0支持
- 动态存储：即利用new和delete实现，根据4.2.3节的函数可以知道new和delete可以在不同函数中使用，这样变量或者内存不受程序或者函数的生存时间控制，更加自由，但是可能造成内存不连续，这是因为存储在heap堆或者free store自由存储区中，与栈连续的内存单元不同，这使得跟踪内存位置更加困难。new和delete不受链接性和作用域限制，关于链接性的内容见[5.3静态持续变量](#5.3静态持续变量)

### 5.2作用域和链接

​	最简单的情况是函数内部创建的变量不能在其他函数中使用，如果同文件的不同函数想要共享变量，需要定义在最前边；如果不同文件想要共享同个变量或者函数，则需要包含头文件；这就涉及链接性的概念，链接性为内部，则文件内共享，链接性为外部则不同文件之间共享

​	自动变量没有链接性，作用域为局部；静态变量作用域取决于如何定义；类函数、变量作用域为整个类；

​	C++函数作用域只能是整个类或者整个名称空间，名称空间可以是全局的，例如std，是名称空间的一个特例；函数作用域不能是局部的，因为代码块内无法定义函数，不同于python，如果可以则只对自己可见而无法被其他函数调用，这是没有意义

### 5.3静态持续变量

​	利用关键字static可定义2种类型的变量：用于代码块外部定义,含义是内部链接性，变量已经是静态持续性；代码块内部定义，则是为了说明变量是静态持续性；不使用static的普通变量则是外部链接性，是否使用extern都可以。

```c++
extern int global1 ; // 外部链接性
int globa2 ; // 外部链接性,不加extern也没事
static only_current_file ; // 内部链接性,且变量静态持续性
void func1();
void func2();
int main()
{
    ...
}
void func1()
{
    static int no_link_1 ;  // 无链接性但静态持续型,即使func1没有调用,no_link_1也存在于内存
    int no_link_2 ;// 自动变量,未调用时不存在,只在调用时存储于栈中
}
```

#### 5.3.1静态变量的初始化

​	可以使用3种方式，默认的0初始化、常量表达式初始化和动态初始化

```c++
void func(double x);
int x ; // 0初始化
int y =5 ; // 常量表达式初始化
int z = sizeof(long) + 1 ;// 常量表达式初始化
const int a = 13  * 13 ;// 常量表达式初始化
const double pi = 4.0 * func(1.0); // 动态初始化
```

#### 5.3.2外部链接性

​	定义和使用外部变量需要外部关键字extern，函数也可以定义为外部函数用于使用。但调用的时候务必事先声明变量是外部的或者函数是外部的，然后再使用。

```c++
// a.cpp
#include <iostream>
using namespace std;
int CB;
extern  char const * weeks[7] = { "Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday" };
// 可以注意到初始化weeks时就必须使用const了，这是因为定义时就使用了常量字符串(指针)初始化
// char const * weeks[7] <=> const * char weeks[7]，记住const在前永远说明值不可变
// weeks的成员是C风格字符数组,也是地址;weeks本身也是首个字符数组的地址
char const*const weeks1[7] = { "Monday","Tuesday","Wednesday",
                              "Thursday","Friday","Saturday","Sunday" };//不加extern也没事
// 第一个const限定的是值 ,且const必须加; 第2个const限定的是地址，可以不加
// weeks1[7]整体可以看成一个指针,const直接限定，所以是指针常量
// char const* 表示继续对指针常量解引用的值进行限定不能修改
extern int CHENBEI=10;
extern void show()
{
	cout << "here..." << endl;
	cout << CHENBEI << CB<<endl;
}
// main.cpp
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;
// int CB; 不可重复定义，违反单定义规则
static int CB; // 使用static是可以的
extern int CHENBEI;
extern const char* weeks[7];// 值一经初始化就不能改，但是地址可以改
extern  char const* const weeks1[7]; // 值、地址不可修改
int main()
{
    extern int CB;
    CB = CB+15;
    CHENBEI = 5;
    cout << CHENBEI << CB << endl;
    extern void show(); // 使用外部函数的声明
    show(); // 调用-->这个变量确实共享,值发生了改变，为15
    // 这里如果使用了static int CB 覆盖了外部的CB，外部的值就不会更改了,还是0而不是15

    cout << weeks << endl;//地址
    cout << weeks[6] << endl;// sunday
    weeks[6] = "456"; //地址可以修改,指向其它字符串,这里"456"不是值,而是字符串456的地址
    weeks[6] = weeks[2]; //地址可以修改,指向另一个成员字符数组,
    //*(weeks[6]) = '2'; 值不可修改,这里不是因为const限定的,而是因为weeks初始化时用了常量字符串(指针),
    // 所以可以注意到初始化weeks时就必须使用const了
    cout << weeks[6] << endl;// Wednesday
    weeks[5] = weeks[5] + 1;//地址可以修改,指向自身的下一位,记住weeks[5]也是指针,但是这个移动是第6个字符数组内部的移动
    cout << weeks[5] << endl;// aturday

    // 也就是说已经初始化就不能修改值了，如果希望地址也禁止修改需要再加限定const
    // weeks1就是不能修改地址,相同的操作下述代码是非法的
    //weeks1[5] = weeks1[5] + 1; 非法
    //weeks1[6] = weeks1[2];非法
    //weeks1[6] = "456";非法
    // weeks = weeks + 1; 无论如何这样一定是非法的
    // 因为weeks在这里不被解读为weeks[0],不是成员(字符串)指针,而是字符串数组指针,移动了位置不知道指向哪里
    system("pause");
    return 0;
}
```

​	使用全局变量具有风险性，一般用于声明常量数据，例如月份\星期字符串、原子量数组、化学元素符号等，并使用const限定防止更改。这里需要说明的是，右边const限定方向，左边const限定值不能更改，只是因为打一开始使用了常量指针定义字符串数组，所以左边的const初始化即自带。

​	**<u>关于这部分内容，若不理解，详细见<遇到的bug.md><4.3.1.4指针常量定义>的上方说明。</u>**

```c++
const char * const weeks[7]={"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"}; 
```

​	继续说明外部链接性的问题，总结来说：一个文件已经定义了一个普通变量，定义时<u>无论加不加extern都是可以的</u>，都是具有外部链接性的；另一个文件引用时，必须使用extern先声明这是1个外部的变量，在进行使用。

​	<u>声明可以在代码块前，也可以在代码块后，因为变量是所有文件所有函数共享，只要声明了，任何地方都可以使用；但是内部链接性不行，必须在代码块前声明</u>。

​	注意：两个文件不能重复定义一个变量，除非是用了static，那么本文件就会覆盖掉外部定义的同名变量，因为标识static指明了变量是内部链接性，也就是5.3.3的内容

#### 5.3.3内部链接性

​           <u>内部链接性使用static声明，但是也是在代码块之前声明，可以保证当前文件的任何函数都可以使用它</u>。因为在<u>代码块内部声明，既不是外部链接也不是内部链接了，而是没有链接性，只在当前文件的当前函数内部使用</u>。

```c++
// file1.cpp
int CB;
// file2.cpp
int CB; // 非法！！！
static int CB ; // 合法
void func1() // 代码块之前声明
{
    ...
}
void func2() // func1,func2都可以使用static定义的变量CB
{
    ...
}
```

​	内部链接性的另一个表现形式是const的限定，即在代码块之前使用const int CB也认为是内部链接性的

```c++
const int CB ; // 也是内部链接性
int main()
{
    ...
}
```

​	之所以这样定义，主要是有3个原因，来源于工程实践的经验而定义的。

1. 有时候需要一组常量字符串或者常量值的定义放在头文件中在不同文件内共享，如果const是外部链接性的，每个文件都包含这些定义，基于单定义规则，会报错，所有只能一个文件包含这个头文件，其它文件都必须使用extern来引用；<u>为了避免每个文件都使用extern声明造成的麻烦，所以将const认为是内部链接性的，这样所有文件都可使用一组声明，即这个头文件</u>；
2. 如果希望每个文件都有自己定义的const常量呢，所以const作为内部链接性也是十分重要的，否则冲突
3. 如果希望一个文件既有内部链接性又有外部链接性呢，可以<u>使用extern覆盖const的影响即可</u>，而且必须使用；在[5.3.2外部链接性](#5.3.2外部链接性)中提过普通变量加不加extern都是可以的，但是const类型必须要加



​	[5.3.2外部链接性](#5.3.2外部链接性)还提过外部函数的声明使用，默认情况下函数都是可以外部链接的，如果设置为内部链接函数，也是加入static即可。这也意味着别的文件中可以定义同名的函数，静态覆盖了外部函数

```c++
static void func(int x); // 函数原型
....
static void func(int x)
{
    ...
}
```

​	最后就是new和delete创建的动态内存，虽然不受链接性的影响，但是别的函数想要使用动态分配的内存，必须在本函数返回动态内存的指针。

​	如果声明为外部变量呢，则声明后边的其它所有函数都可以使用它

```c++
float * func11()
{
	float * p = new float [20];
    // extern float * p = new float[20];
    return p
}
void func12() // 无需返回*p
{
	//float * p = new float [20];
    extern float * p_extern = new float[20];
    ...
}
void func21(float * p)
{
    float * p = func1();
    delete p;
}

void fun22()// 直接使用外部链接的动态内存指针而无需传递
{
    delete p_extern; 
}
```

#### 5.3.4无链接性

​	虽然static在内部函数定义是没有链接性的，但是他仍然是不同于普通的变量，当前函数无论调用与否，内存都有该变量，见[5.3静态持续变量](#5.3静态持续变量)

​	两次函数调用之间，static的值是不会改变的，这是static变量只初始化一次，再次调用时不会像自动变量那样重新初始化。这也就是意味着这个变量可以起到续接的作用

```c++
void strcount(const char * str)
{
    static int total = 0;
    int count = 0;
    while(*str++)
        count++;
    total += count ;
    cout << "count="<<count << "   total="<<total<<endl;
}
// 主程序
strcount("123456");//count=6   total=6
strcount("123456"); //count = 6   total = 12
```

#### 5.3.5语言链接性

​	对于C风格来说，每个函数只能用一个名称，如func函数在编译器内部需要一个符号名来指代func函数，不能直接使用func，可能使用的是_func；但是C++函数可以重载，所以需要对同一个函数不同版本指定不同的符号，例如func(int)使用 _func_i，func(double,double)使用 _func_d_d，这就是语言链接性；

​	例如对于一个外部的函数show，引用时可以使用2种方式引用函数

```c++
 extern void show(); // 使用外部函数的声明，隐式，在5.3.1中使用
// 等价于
 extern "C++" void show(); // 使用外部函数的声明,显示
// 如果使用C风格也可以
 extern "C" void show();
```



### 5.4说明符和限定符

```c++
// 说明符
register // 说明是寄存器变量
static // 说明是内部或无链接性的静态变量
extern // 说明是外部链接性变量
thread_local // 说明是线程局部变量
mutable // 用于在结构体或者类中取消const的限制

struct person
{
    int age;
    mutable int salary ;
};
const person p;
p.age = 1;// not allowed
p.salary = 2 ; // allowed

// 说明符不能使用多个，thread_local除外，可以和static/extern 2个一起使用
    
// 限定符
const // 限定不可修改
volatile // 定义一个程序不修改也可能更改值的变量(可能是硬件引起)
    
// 其它
auto // 自动推导，C++11之前认为是说明符
    
    
```

	### 5.5名称空间

​	名称空间是为了避免多个名称使用相同的函数名或变量名引起冲突

```c++
#include <ostream>
using namespace std ;//std包含的所有函数都在这里到本文件结束使用,std若有func函数会有冲突
void func();
int main()
{
    ...
}
void func(){}
```

​	为了 避免std包含的函数和func冲突

```c++
#include <ostream>
void func();
int main()
{
    using namespace std ;//只在main中作用
    ...
}
void func(){}
```

​	如果只想使用std的几个函数，可以使用作用域语法

```c++
#include <ostream>
void func();
int main()
{
    using std :: cin ;
    using std :: cout ;
    using std :: endl; // 单独使用也是可的
    ...
    using namespace cb ; // 从声明处下方使用cb的名称空间
}
void func(){}
```

​	名称空间的定义使用namespace即可

```c++
namespace cb
{
    int age ;
    char name[10];
    void func();
    struct CB{...};
}
```

​	还可以定义嵌套名称空间

```c++
namespace CB 
{
	namespace cb1
    {
        ...
            namespace cb11
        {
            ...
        }
    }
    namespace cb2
    {
        ...
    }
    ...
}
```

​	还可以定义一个使用了不同名称空间的某些函数的集合名称空间，并取别名；如果不使用名称，也就是默认使用潜在作用域。

```c++
namespace mynamespace
{
    using std :: cout ;
    using cb :: CB;
}
namespace mns = mynamespace; // 别名
namespace {int age ; double s ;} // 潜在作用域声明处开始到结尾，特点是不能显示的使用using来作用于别处
```



## 6.模板类

### 6.1vector类

​	模板类vector类似于string类，是一种动态数组，内部使用了new和delete管理内存，是new创建动态数组的替代品

​	模板类可以运行阶段设置vector的长度，可以末尾添加数据或者中间插入数据，而无需事先声明指定内存大小的数组

​	需要加入头文件 #include <vector>，创建动态数组格式为 vector<typeName> v_t(n_elem) ,n_elem可以是变量也可以是常量

### 6.2array类

​	如果使用的数组长度固定，为了提高效率，可以使用array模板类，需要加入头文件 #include <array>，创建动态数组格式为 vector<typeName,n_elem> arr ，n_elem只能是常量

- 相同点：都可以通过索引来访问
- 不同点：
  - 普通数组只能通过复制数据来赋值给另一个对象，array和vector可以直接赋值
  - 普通数组和array对象存储在栈区，vector存储在自由存储区或堆区
  - 普通数组不会检查越界错误，vector/array可以使用at函数禁止越界

```c++
void Study_compare_arr_vector_array()
{
    double arr1[4] = { 1.2,2.4,4.8,9.6 };
    double arr1_[4];
    vector<double> arr2(4);
    vector<double> arr2_(4);
    array<double, 4> arr3 = {1.1,1.2,1.3,1.4};// 可以初始化也可以不初始化
    array<double, 4> arr3_;
    // vector的必须单独初始化
    arr2[0] = 1.0 / 3; arr2[1] = 1.0 / 5; arr2[2] = 1.0 / 7; arr2[3] = 1.0 / 9;

    // 相同点都可以使用索引进行访问
    cout << "arr1[0]=" << arr1[0] << "  arr2[0]=" << arr2[0] << "  arr3[0]=" << arr3[0] << endl;

    // 区别普通数组不能直接赋值，array/vector对象可以
    // arr1_ = arr1; 非法
    arr2_ = arr2;
    arr3_ = arr3;

    // 普通数组不会检查越界错误.vector/array可以使用at函数禁止越界
    arr1[-2] = 20.1; // 实际上就是*(arr1-2),这块内存不属于arr1
    cout << "&arr1[-2]=" << &arr1[-2] << "  !=  &arr1=" << &arr1 << endl;
    //arr2.at(-2) = 20.1; at检测到非法索引之后中断
    arr2.at(2) = 20.1; arr3.at(2) = 20.3;// 合法
    cout << "arr2[2]=" << arr2[2] << "arr3[2]=" << arr3[2]<< endl;

}
```

## 7.循环和关系表达式

### 7.1for循环

```c++
for(int i = 0 ; i < 10; i++)
{
    cout << i << endl;
    cout << 2*i << endl;
}
// 如果省略花括号，则for语句的后一句作为循环语句
for (int j =5 ; j > 5; --j )
    cout << j << endl; // 循环体
cout << 2*j << endl; // 非循环体
```

​	如果不使用for(初始条件;循环条件;条件更新){循环体}的表达式，也可以将初始条件写在for语句之前，循环条件和条件更新语句写在花括号内部，然后执行循环体也是可以的

```c++
int i = 0;
for ( ; ; )
{
    cout << i << endl ; // 循环体
    i++ ; // 条件更新
    if ( i > 10) break ; // 循环条件
}
```

​	for也支持范围循环

```c++
int ages[6] = { 0,1,2,3,4,5 };
for (int x : ages)
    cout << x << endl;
// 也可以直接省略定义的步骤
for (int y : { 0, 1, 2, 3, 4, 5 })
    cout << y << endl;
```

### 7.2while循环

```c++
string name = "chenbei";
int i = 0;
while (name[i] != '\0')
{
    cout << name[i];
    i++;
}
cout << endl;
```



### 7.3do_while循环

​	循环至少执行一次

```c++
int n ;
do
{
    cin  >> n ; // 至少输入一次
}
while (n!=0);// 不等于0就一直输入
```

### 7.4 break和continue

​	break语句用于switch和循环中，当满足条件即退出语句或者循环

​	continue用于循环，循环的过程中可能需要跳过一些循环，或者该次循环满足某种条件时忽略，可以使用continue跳过余下的代码新型

下一次循环，而非退出循环

## 8.声明别名

​	支持两种方式，一种是使用预定义#define，一种是使用关键字typedef

```c++
typedef int INT;
typedef float*  FLOAT_POINTER;
// C++ 现在不支持预处理器的宏定义
// #define INt int ; -->不支持
```

## 9.逻辑运算符

```c++
if (x>3 && x<5){}else{};
if (x>3 || x<0){}
if (!(x>5)){}
```

## 10.条件运算符

### 10.1三元判断(condition? v1 : v2)

```c++
5 > 3 ? 10 : 5 ; // condition ? express1 : express2 如果条件为真 取表达式1否则取表达式2
```

### 10.2switch语句

​	case标签必须是一个单独的整数值或者char，无法处理浮点测试，如case1.2；另外integer_num也必须是常量。

​	如果涉及取值范围、浮点测试或者两个变量的比较应当使用if_else语句

```c++
switch(integer_num)
{
    case num1 : express1 ;
        	    break ; 
    case num2 : express2 ;
       		  	break ; 
    ...
    default : default_express ;
}
// 常见的应用是选择菜单栏，下方代码提供了大致思路,可以穿插枚举值进行判断
// 用户的输入不能识别自定义的枚举值，可以通过整数和枚举值进行桥接，即将枚举值提升为整型
void showmenu(); // 0，1，2...等多个菜单选择，-1为退出
void func(int choice); // 不同菜单执行的功能
void exit(); // 退出
enum {red ,blue,green,yellow,orange,violet};
int main()
{
    showmenu();
    int choice ;
    cin >> choice ; // 选项
    while (choice != -1 && choice >= red && choice <= violet) // -1为退出选项
    {
        case red : func(red) ; // 相关操作
        		
        		break;
        case blue : func(blue) ; // 相关操作
        		break;
        ...
        default : exit();
    }
    showmenu(); // 退出后也要显示菜单
    cin >> choice ; 
    return 0 ;
}
```

## 11.简单文本输入输出

### 11.1文本写入流ofstream

​	输出流用于给文本写入值，注意默认的情况下open将会清楚文本文件的所有内容去覆盖写入

​	需要包含头文件fstream，然后使用ofstream定义输出流，用流打开文件，流类似于cout，同样具备endl，<<等方法

​	open方法可以直接输入字符串也可以先用char[]定义，使用C风格字符串传入

```c++
ofstream OutFile; // 定义写入流
OutFile.open("test.txt");
OutFile << "hello world!" << endl; // 覆盖写入文本
OutFile.close();
```

### 11.2文本读取流ifstream

​	使用ifstream定义文本读取流

```c++
char filename[20];
ifstream InFile; // 定义文本读取流
cin.getline(filename, 81); // 输入文件名 "test.txt"
InFile.open(filename);
//  InFile.open("test.txt"); // 直接输入也可
```

	#### 11.2.1逐个读取字符

​	逐个读取字符，有2种方法，一种使用>>，一种使用get获取字符

​	对于>>不能读取空格，get是可以的

​	可以使用输入流的eof()函数判断是否读到结尾

​	InFile.fail()判断文件是否成功打开，打开失败返回1

​	InFile.good()判断流的状态，未成功读取文本时返回0

```c++
// 逐个读取字符
if (InFile.is_open())
{
    char value; // 存放读取的字符变量

    int count = 0; // 统计字符个数
    // （1）可以>>先读取1个字符，在while判断输入状态后再>>value
    InFile >> value; // 先读取1个字符
    while (InFile.good()) // 最后一次读取输入是否成功，需要先输入一条语句
    {
    	++count;
    	InFile >> value; // 持续读取字符
     cout << value ;
    }
    // （2）还可以使用简化的>>表达式，因为进入条件判断时就会执行依次字符读取了
    while (InFile >> value)  // InFile.get(value)也可以,可以读取空格符
    {
        ++count;
        cout << value;
    }
    cout << endl;
    // （3）使用InFile.get(value)，与（2）代码相同，可以读取空格符
    if (InFile.eof()) // 读到最后的eof结束符时
    {
        cout << "end of file reached.\n";
    }
    if (count == 0)
    {
        cout << "there is no data.\n ";
    }
    else
    {
        cout << "文本有" << count << "个字符" << endl;
    }
    InFile.close();
}
else if (InFile.fail()) // 失败时返回1，默认返回0
{
    cout << "InFile.fail()=" << InFile.fail() << endl;
    cout << "file is fail to open.\n";
    exit(EXIT_FAILURE);// 原型在cstdlib中定义
}
else
{
    cout << "unknown reason failed!" << endl;

}
```

#### 11.2.2逐行读取字符

```c++
// 读取整行
char strs[30]; // 用于存放所有字符
InFile.open("test.txt");
InFile.getline(strs, 80);
// （1）先读取再判断
while (InFile.good())
{
    cout << strs << endl;
    InFile.getline(strs, 80);
}
// （2）直接判断
while (InFile.getline(strs, 80))
{
	cout << strs << endl;
}
InFile.close();
```

## 12.函数定义

​	在C++中，函数的返回值不能是数组，但是可以返回整型、浮点型、指针、结构体和对象，也可以返回数组作为成员的结构或对象

​	另外，返回值和定义函数的类型必须相同，或者可以强制转换的类型，如返回表达式为int，但是函数定义类型为double，那么int就会强制转换为int

​	main之前要给出函数原型，main调用该函数时即可查找对应的函数；如果不给出原型，函数在main后边定义，先执行main的编译才能查找该函数，这使得效率低下，另一方面是有的函数未必在本文件当中，main的编译可能无权访问函数。

### 12.1形参和实参（变量的值传递）

​	实参，是实际参数，在main中定义的实际参数

​	值传递就是直接传递实例，但是实例在函数中会产生副本，函数执行完毕会释放

​	形参是函数中的参数列表，一般按值传递时都是使用了实际参数的副本

```c++
double func(double x); // 原型
int main()
{
    double width = 5.0; // width是实参
    double v = func(width) ; 
}
double func(double x)
{
    // x 是 形参，按值传递时x实际上是width的副本
    return x * x * x
}
```

### 12.2函数与数组（指针的值传递）

​	 传递的参数虽然是数组名，但是实际上解释为指针，但函数体内部仍当作数组使用，指针和数组某些情况是等价的

```c++
int sum_arr(int arr[] , int n)
{
    cout << "func：sizeof(arr)=" << sizeof(arr) << endl; // func：sizeof(arr) = 8
    int total = 0 ;
    for (int i = 0 ; i < n ; i++)
    {
        total = total + arr[i] ; 
    }
    return total;
}
// 等价于
int Study_Sum_Arr_(int* arr, int n)
{
    int total = 0 ;
    // arr为数组名被解释为指针，n为数组元素个数
    for (int i = 0 ; i < n ; i++)
    {
        total = total + arr[i] ; // 这里arr当成数组使用
    }
    return total;
}
```

​	C++中将数组名解释为数组第一个元素的地址，从而sum_arr函数中传递的arr实际上是地址

```c++
int const n = 5; // 等价const int n = 5;
int arr[n] = {10,20,30,40,50}; // arr[n]的n必须是不可变的,所以需要const限定n
cout << "arr=" << arr << "   " << "&arr[0]=" << &arr[0] << endl;// C++将数组名解释为其第一个元素的地址
int total = sum_arr(arr, n); // 传递的arr是地址
cout << "total=" << total << endl;// 150
```

​	**<u>当且仅当函数头或函数原型中指针表示法int * arr 与 数组表示法int arr[]是等价的</u>**，在函数体中不能使用int arr[]说明arr是一个指针

​	那么可以知道，实际上内部将函数int sum_arr(int arr[] , int n) 解释为 int sum_arr(int* arr , int n)

```c++
int sum_arr(int arr[] , int n);
int sum_arr(int* arr , int n) ; // 函数头或函数原型中是等价的
```

​	在函数体中无论使用上述的哪种函数头，都可以使用数组表示法访问数组元素，这是因为，存在两个恒等式

​	对数组使用下标等价于使用指针做加减法，对指针取地址；对指针成员取地址等价于指针指向该成员

```c++
arr[i] == *(arr + i); 
arr == &arr[0] ;
&arr[i] == arr + i ;
```

​	既然两者等价，那么实际上可以看到这里的值传递虽然是值传递，但传递的不是实际值而是地址值，也就是引用传递，可以看到这种方式在数组很大时是很有效的，避免了复制数组消耗的时间和内存

​	引用传递的地址不一定传递数组，也可以使用下述两种方式，计算的实际上是后3个元素30+40+50的和，注意n不要越界，可以知道arr+2和&arr[2]是等价的

```c++
int sum1 = Study_Sum_Arr(arr+2, n-2);
cout << "sum1=" << sum1 << endl; // 120

int sum2 = Study_Sum_Arr(&arr[2], n - 2);
cout << "sum2=" << sum1 << endl; // 120
```

​	由于传递的是原数组的地址，所以函数内部是可以对原数组进行修改的，下列函数实际上就修改了原数组的值，虽然没有返回任何值

```c++
void revalue(int c , int* arr, int n)
{
   for (int i = 0; i < n; i++)
   	   arr[i] *= c ;
}
// 主函数中
Study_revalue(2, arr, n); // 函数内部修改了原数组
```

​	如果不希望改变原数组的值，例如只打印数组元素，可以在打印函数使用const限定，即常量指针，通过传递int* const arr或者const int *arr或者int const arr[]进行限定

```c++
void Study_display(int* const arr, int n) //int const arr[]也可以,int const *arr<=>const int *arr,
{
    //arr[0] = 1; //const限定了值不能修改，常量指针
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << "  ";
    }
    cout << endl;
}
// 主函数中
// 如果只是为了打印数组,为了防止函数内部修改数组,可以传递const
Study_display(arr, n); // arr并非是常量指针,但是可以传递 : 20  40  60  80  100

//  当然也可以定义常量指针传递
int  ar[n] = { 0,1,2,3,4 };
int const* arp = ar;
Study_display(arp,n); 
```

​	最后还需要注意的问题是，sizeof在main和func中是不同的，主程序计算的整个数组占据的字节，每个int占据4字节，5个元素，所以占据20个字节；函数中计算的是指针变量本身的长度，这却决于计算机，指针移动最小长度为1个字节也就是8位

​	**<u>这也是为何需要显示指定n为数组长度，而不能使用sizeof进行判断</u>**

```c++
cout << "main：sizeof(arr)=" << sizeof(arr)<<endl; // main：sizeof(arr)=20=4*5，数组长度
// 在sum_arr函数中
cout << "func：sizeof(arr)=" << sizeof(arr) << endl; // func：sizeof(arr) = 8，指针变量本身的长度是8，一个字节8位
```

​	除了给定数组的首地址的元素个数以外，也可以使用双指针确定原数组的全部信息，双指针是STL标准模板库广义化的雏形

```c++
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
// 主函数中
// 使用双指针确定原数组的信息,从而进行计算
int sum3 = Study_Sum_Arr__(arr, arr+n);
cout << "sum3=" << sum3 << endl; // 150*2=300
```

### 12.3函数与二维数组

​	二维数组是int( * )[c]类型，int( * )表示是一个指针(数组),具有c个元素

```c++
int arr_2d[3][4] = { {1,2,3,4},{5,6,7,8},{9,10,11,12} }; // 定义二维数值数组
```

​	二维数组arr_2d是1个指针，负责在几个元素之间移动，所以arr_2d是地址；元素又是具有4个数值的数组(地址)，或者说指向数组地址的指针，所以对arr_2d解引用还是地址，且是首元素的地址，所以下述代码的结果是一样的

```c++
cout << "arr_2d=" << arr_2d << "   *arr_2d="<<*arr_2d << "   arr_2d[0]="<<arr_2d[0] << endl;
// arr_2d=000000E68D4FFA48   *arr_2d=000000E68D4FFA48   arr_2d[0]=000000E68D4FFA48   *arr_2d[0]=1
```

​	如果定义一个指针来指向二维数组，必须使用 int (*)[4]，**<u>p先和 * 结合，本质上是个指针</u>**，p和*p仍然是相同的，与arr_2d、 *arr_2d相同的含义，指针指向有4个元素的数组，对指针解引用不能得到数值，而是得到地址，如果需要得到值，需要二次解引用

```c++
int(*p)[4] = arr_2d;  
cout << "p=" << p << "   *p=" << *p << "   p+1=" << p + 1 << "   *(p+1)="<< *(p+1)<<endl;
// p=000000AD9B73F368   *p=000000AD9B73F368   p+1=000000AD9B73F378   *(p+1)=000000AD9B73F378
```

​	对指针二次解引用，也要注意，这个本质上还是个指向3个元素的数组的指针，只不过每个元素是数组，还有4个元素，所以指针运算后是两个元素的首地址

```c++
cout << "**p=" << **p <<"   *(*(p + 1))="<< * (*(p + 1)) << endl;
// **p = 1    * (*(p + 1))=5 , 是2个一维数组的首元素
```

​	int * 定义的是整型指针，它可以指向变量也可以指向一个数组地址，arr_2d[1]即一个地址

​	int * [] 定义的是整型指针数组，是int * 的组合，所以要使用花括号初始化多个地址；**<u>arr2p2和[4]先结合，本质上是个数组</u>**,有4个指针，每个指针指向某个数值地址，对指针解引用即可得到数值

```c++
int* arr2p1 = arr_2d[1]; // 1个指针，指向二维数组的次元素
int* arr2p2[4] = { arr_2d[0],arr_2d[1],arr_2d[2],arr_2d[3] };// 4个指针的指针数组
```

​	故在定义1个需要传入二维数组的函数时，形参必须是int ( * )[]类型，而不是int * []类型，前者是指针，后者是数组，在这里数组不等同于指针。。

```c++
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
```

 ### 12.4函数与C风格字符串

​	函数定义中可以使用const限定，防止对原字符串进行修改，因为C风格字符串本身就是个数组

```c++
char name[10] = "chenbei";
char const *n = "chenbei"; // 常量字符串必须使用const 常量指针指向
int num1 = count(name,'e'); // 可以直接传入数组名name，因为这里name也是指针
int num2 = count(n, 'e') ; // 也可直接传入指针
cout <<"num1="<<num1 <<"   num2="<<num2<<endl;
unsigned int count(const char * str , char ch)
{
    unsigned int total =0;
    while (*str) // str是指针在while循环中会移动,为结束符\0时退出
    {
        if (*str == ch)
            total++;
        str++ ; // 移动指针,数组的话也看成指针
    }
    return total ;
}
```

​	**<u>函数不能直接返回数组，所以也不能返回C风格字符串</u>**，但是可以借助返回指针实现，在函数使用new得到一个内存，内存存好值后，返回这个内存的地址，在主程序中可以使用新的变量和内存拷贝这个new的内存值，也可以使用完delete掉这个内存

```c++
char* return_strs(char c , int n)
{
    char * p = new char[n+1] ; // 开辟n+1的内存，最后1个存放/0
    p[n] = '\0';
    while (n-- > 0)
        p[n] = c ;
    return p ;
}
// 主程序中
const int n2 = 10;
int c2 = '+';
char* p2 = return_strs(c2, n2);
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
```

### 12.5函数与结构体

​	结构与数组不同，可以看成一个对象或者一个实体，可以用于函数直接返回

```c++
struct Student
{
	int age = 0;
	char name[20] = {};
};
// 函数与结构体
Student _s1 = { 20,"ggg" };
Student _s2 = { 40,"ddd" };
Student s = Study_Sum_Student_Age(_s1, _s2);
cout << "s.age=" << s.age << endl;
// 定义指向结构体的指针
Student* ps = &s;
Student const* ps1 = &s;// 使用const与否均可
Study_Show_Student(ps);
Study_Show_Student(ps1);
Student Study_Sum_Student_Age(Student s1, Student s2)
{
	Student s ;
	s.age = s1.age + s2.age;
	strcpy_s(s.name,"chenbei" ); // 注意必须使用strcpy，不能直接使用s.name="chenbei";
	return s;
}
Student Study_Show_Student(const Student * s)
{
    cout << "student.age="<< s->age << endl;
    cout << "student name=" << s->name << endl;
}
```

### 12.5函数与C++风格String对象

​	String对象类似于结构体，也可以直接返回，相比char风格的字符串要简单

```c++
void Study_Show_String(string s);
void Study_Show_String_(const string * s);
string name = "chenbei" ;
string* n = &name;
Study_Show_String(name);
Study_Show_String_(n);
void Study_Show_String(string s)
{
    cout << s << endl;
}
void Study_Show_String_(const string *s)
{
    cout << *s << endl;
}
```

### 12.6函数与模板类array对象

​	使用模板类注意指定的函数原型，可以传入地址也可以传入实例

```c++
void Study_Fill_Array(array<double, 4>* p);
void Study_Show_Array(array<double, 4>  p);
// 函数与array对象
array<double, 4> arr;
Study_Fill_Array(&arr); // 传入地址
Study_Show_Array(arr);// 传入对象
void Study_Fill_Array(array<double, 4>* p)//地址
{
    for (int i = 0; i < 4; i++)
    {
        (*p)[i] = i; // p是指针,解引用后才是数组
    }
}
void Study_Show_Array(array<double, 4>  p)// 实例
{
    for (int i = 0; i < 4; i++)
    {
        cout << p[i] << endl;
    }
}
```

### 12.7函数与引用变量(引用传递)

​	这部分内容见第16讲第2节的<函数中的引用变量>

​	Take me to [16.2函数中的引用传递](#16.2函数中的引用传递)

### 12.8 默认参数与重载

#### 12.8.1默认参数

​	默认参数要求从当前开始右边的参数都赋予默认参数，否则是非法的

```c++
void func(int n1 , int n2 = 1 , int n3 =4); // valid
// void func(int n1 , int n2 = 1 , int n3 = 3 , int n4); invalid
```

#### 12.8.2重载

​	重载的本质是特征参数标不同，函数名/返回类型可以相同，但是参数列表必须相同

```c++
void func(const char * s);
void func(int n);
void func(char * s);
void func(long c ; int d = 2);
```

​	参数列表相同，但是返回值不同，这种重载方式是不允许的

```c++
void func(int n);
double func(int n) ; // invalid
```

​	一个特殊的情况是，引用和变量本身也是不允许重载的

```c++
void func(int x);
void func(int & x) ;// invalid
func(x); // 不知使用哪个原型
```

### 12.9函数模板和重载

#### 12.9.1模板定义和重载

​	使用关键字template和typename定义，或者使用class定义

​	单个模板可以适用于不用内置类型，如下方的T可以是int，也可以是double

```c++
template <typename T> // or <class T>
void Study__Func_Template_Swap(T a, T b);// 模板函数
```

​		模板本身也可以重载，可能需要的不是a,b，而是它们的指针或引用

```c++
template <typename T> // or <class T>
void Study__Func_Template_Swap(T &a, T &b);// 重载模板

template <typename T> // or <class T>
void Study__Func_Template_Swap(T *a, T *b , int c);// 重载模板
```

​	函数模板对于一些运算可能是不成立的，例如算术运算、逻辑运算、赋值运算，对于结构体、指针或者数组而言。下方的运算都可能导致错误

```c++
a = b ;// 数组不成立
T c = a * b ;// 数组、指针、结构体不成立
if (a > b ){};// 结构不成立
```

​	2种解决方案，一种是重载运算符，一种是为特定类型提供具体化的模板定义，下文介绍后者。

	#### 12.9.2具体化的模板定义

​	非模板函数、普通模板函数和显式化模板函数的优先级比较，首先明确**<u>非模板函数调用优先级>显式具体化模板函数>普通模板函数</u>**

​	对于赋值运算，结构体虽然成立，但是只是一个整体赋值，而不是结构体的成员赋值运算,所以为了实现能够同时交换结构体成员，也能交换结构体部分成员，需要重载函数，重载函数可以使用显式具体化。

​	交换结构体可以使用指针传递和引用传递，不能使用值传递，这部分内容见[16.4引用传递与结构体](#16.4引用传递与结构体)

​	这里只是为了说明模板的显式具体化方式，所以只使用引用传递来说明问题，需要注意的是显式化具体模板方式必须在普通模板方式已经定义才能使用

​	显式具体化的函数定义使用原型

```c++
template <> void Swap<job>(job& a, job& b);//显式具体化
// or
template <> void Swap(job& a, job& b);
```

​	由于下文还要区分显式实例化，这里给出实例化的调用方法，可以看出只缺少了1个<>符号（注：这里不是在定义函数，下方代码用在主程序）

```c++
template void Swap<job>(job& a, job& b);//显式实例化
```

​	说明显式实例化之前还要说明默认的隐式实例化：函数模板并不是一个函数定义，而是一个用于函数定义的方案，这个方案在主程序调用时就会立刻实例化1个函数定义，可以是int型，也可以是double型，还可以是job结构体型，也就是普通模板函数实例化的默认方式。根据下文关于显式具体化的说明可以知道，显式具体化允许结构体交换部分成员，而隐式实例化是不能交换部分成员的，是普通模板函数类型的一个实例

```c++
template <typename T>
void Swap(T &a , T &b)； // 隐式实例化：默认
```

​	首先说明显式具体化和隐式实例化，一级非模板函数之间的区别

```c++
struct job
{
    char name[40];
    double salary ;
    int floor ;
}
void Swap(job &a , job & b)// 非模板函数
{
    cout << "非模板类函数被调用..." << endl;
    job c ;
    c = a ;
    a = b;
    b = c ;
}

template <typename T>
void Swap(T &a , T &b)//普通模板函数,如果传入结构体,会交换结构体的全部成员
{
    cout << "普通模板类被调用..." << endl;
    T c ;
    c = a ;
    a = b ;
    b = c;
}
// 下方函数能够定义的前提是已经了普通模板函数,不能脱离而独立存在
template <> void Swap<job>(job& a, job& b)// 显式具体化版本,允许只交换部分成员
{
    cout << "显式化具体模板类被调用..." << endl;
	double s;
	s = a.salary;
	a.salary = b.salary;
	b.salary = s;

	int f;
	f = a.floor;
	a.floor = b.floor;
	b.floor = f;
}
// 非模板函数、普通模板函数和显式化模板函数的优先级比较
// 同时存在时,非模板函数先被调用
job j1 = { "a",1.5,3 }, j2 = { "b",2.4,6 };
cout << "before swap：" << " &j1=" << &j1 << "   &j2=" << &j2 << endl;
Swap(j1, j2); // 非模板类函数被调用...
cout << "j1.salary=" << j1.salary << "   j2.salary=" << j2.salary << endl;

// 如果注销掉非模板函数，则显式话模板函数先被调用
job j1 = { "a",1.5,3 }, j2 = { "b",2.4,6 };
cout << "before swap：" << " &j1=" << &j1 << "   &j2=" << &j2 << endl;
Swap(j1, j2); // 显式化具体模板类被调用...
cout << "j1.salary=" << j1.salary << "   j2.salary=" << j2.salary << endl;
```

​		显式实例化的使用方式是在调用

## 13.递归

​	关于递归不详细说明，只给出简单的形式

```c++
void func(param)
{
    statement1 ; 
    if (condition)
        func(new_param)
    statement2;
}、；
// 例如实现阶乘的函数
void factorial(int n)
{
    if (n>0)
        factorial(n-1);
    cout << n << endl;
}
// 主函数中
factorial(100);
```

## 14.函数指针

​	函数指针的作用是可以在特定时间，选择使用某个函数，例如有些时刻选择一种函数处理事情，另一个时刻用另一个函数处理，所以可以编写一个函数select，select函数有参数时间和函数指针，调用select就可以在不同时刻使用不同的函数

​	特别要注意的是函数指针原型和指向的函数在返回值和输入值都必须相同，这里两个函数都是返回void输入int，那么定义的函数指针也是返回void输入int

```c++
void method_1(int n);
void method_2(int n);
void select(int n, void (*p)(int));
// 主程序
int main()
{
    int n;
    cin >>  n;
    if (n == 1)
    {
        select(n, method_1);// 时刻1使用算法1
    }
    else
    {
        select(n, method_2);// 时刻2使用算法2
    }
    return 0;
}
void select(int n , void (*p)(int))
{
	// double (*p)(int) 和 原型double method_1(int n)是相似的
	// 所以(*p)对照就是函数,那么p就是函数指针
	(*p)(n); // 执行函数
	p(n); // 也可以，C++中认为函数指针p和(*p)等价
}
void method_1(int n)
{
	cout << "method_1 = " << n << endl;
}
void method_2(int n)
{
	cout << "method_2 = " << n << endl;
}
```

## 15.内联函数inline

​	内联函数使用inline即可，正常的函数执行过程是，主程序->函数->跳转函数原型处->搜索函数体->执行函数->返回值->返回主程序

​	这样的跳转机制可能花费较多时间，所以inline的好处是不需要跳转，而是直接顺序执行内敛函数的代码，如果内联函数出现多次，也会多次拷贝内联函数的代码，所以内存开销大

​	是否选择内联函数，取决于跳转机制花费时间和拷贝内存的取舍，一般情况下，小型函数使用内敛速度更快，大型函数拷贝内存影响速度，使用正常的跳转机制即可

## 16.引用变量

### 16.1引用变量的定义

​	引用变量使用&定义，但不是取址符号，而是看成一种类型，即 int & 是一种引用类型

```c++
int a = 0 ;
int & q = a ;
```

​	需要注意的是，引用必须在声明中即初始化，不可以先声明，后赋值，这也是与指针的区别

```c++
int* p ;
p = &a ; // 指针先声明后赋值可以

x -> int &q ;
× -> q = a ; // 必须声明即初始化，这也是为了避免引用赋值和值的赋值冲突

int & q = a ; // √ 正确
```

​	引用的指向一经声明，就不可以再更改，但是可以改变值，所以引用更像是指针常量

```c++
int & q = a ;
int * const p = &a; // p和q隐式等价
```

​	如果试图更改引用的指向，实际上，只是改变引用的值

```c++
int & q = a ;
int b = 1 ;
q = b ; // 试图把q引用指向b,事实上这只是更改了q的值为b,所以结果是q和b都为1
```

​	如果使用一个普通指针指向变量，一个引用指向该指针，当指针改变指向时，引用也是否会更改指向呢？答案是否定的

```c++
int * p = a ; // 指针指向a
int & q = *p ; // 引用指向指针
p = &b ; // 指针指向b
cout << p << a << q << endl; // 结果p和a的地址仍然相同,q的地址指向了b,q依然通过声明初始化时的传递与a绑定

```



### 16.2函数中的引用传递

​	C语言中是不允许按引用传递的，只能按值传递，即主程序中创建1个变量，函数调用此变量时创建了一个副本去执行，从而是2个变量2个名称；如果希望避免拷贝内存，可以通过传递指针的方式来迂回实现

​	而C++中允许引用传递，传递的是变量的别名，有着指针传递的效果，无需创建内存副本

![值传递和引用传递](C:\Users\chenb\Desktop\2021.9.30备份\代码汇总\markdown文件\值传递和引用传递.jpg)

​	交换函数的比较，一共三种方法：按变量值值传递的交换方法；按变量引用传递的交换方法；按变量指针值传递的方法；其中按变量值值传递的方法是不能交换原始数据的，只能对副本进行交换，下方代码进行演示。

```c++
// 变量值的值传递
void Study_Quote_Swap_VariableValueTransfer(int ta, int tb)
{
	cout << "		1.函数内部变量值值传递交换前：" << "  ta=" << ta << "  tb=" << tb << endl;
	int c ;
	c = ta;
	ta = tb;
	tb = c;
	cout << "		2.函数内部变量值值传递交换后：" << "  ta=" << ta << "  tb=" << tb << endl;
}
```

```c++
// 引用传递
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
```

```c++
// 变量指针的值传递
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
```

```c++
// 主程序
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

/*
(1)按变量值的值传递：
        1)主程序变量值值传递交换前：  a=1  b=2
                1.函数内部变量值值传递交换前：  ta=1  tb=2
                2.函数内部变量值值传递交换后：  ta=2  tb=1
        2)主程序变量值值传递交换后：  a=1  b=2
结论：按变量值的值传递进行交换不改变原有数据，只交换函数内部创建的副本

(2)按引用传递：
        1)主程序引用传递交换前：  a=1  b=2
                1.函数内部引用传递交换前：  qa=1  qb=2
                2.函数内部引用传递交换后：  qa=2  qb=1
        2)主程序引用传递交换后：  a=2  b=1
结论：引用传递进行交换改变原有数据，函数内部也改变

(3)按变量指针的值传递：
        1)主程序变量指针的值传递交换前：  a=2  b=1
                1.函数内部变量指针的值传递交换前：  *pa=2  *pb=1
                2.函数内部变量指针的值传递交换后：  *pa=1  *pb=2
        2)主程序变量指针的值传递交换后：  a=1  b=2
结论：按变量指针的值传递进行交换改变原有数据，函数内部也改变
*/
```

​	对于按值传递的方式，传递的参数限制较少，例如按值传递求立方的调用，可以传入一个变量，也可以传递变量加一个常数，还可以传递数组的一个成员

```c++
double cube(double x)
{
    return x * x * x ;
}
double z = 1.2 ;
double r1 = cube(z);//合法
double r2 = cube(z+2.0);// 合法
double z_arr[3] = {1.0,2.0,3.0};
double r3 = cube(z_arr[2]);// 合法
```

​	但是对于引用而言，只有第一种是合法的，不能直接传递z+2.0和数组的成员

```c++
double refcube(const double & x)// const double & x等价于int const &x
{
    return x * x * x
}
```



### 16.3常量引用和引用常量

​	对于上述的引用传递交换函数，可以发现使用引用可以改变原数据，所以类似的如果不希望改变原有数据可以使用const限定，类似一常量指针，定义一个接收常量引用的函数可以保证内部不修改原有数据,const double & x等价于int const &x

​	引用常量本身的含义是不能改变指向,可以改变值,而引用本身的定义就是如此

​	所以不同于指针有3种类型,即不存在普通引用,常量引用和引用常量,**<u>普通引用即引用常量</u>**

​	同时因为不存在引用常量，实际上int & const x也是可以的，所以结论是

​	const double & x等价于int const &x也等价于int & const x，与const的位置无关

#### 16.3.1按值传递和按引用传递const的作用

```c++
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
```

​	所以，尽可能的在函数使用const引用参数声明，理由有3个

- 可以避免无意中修改原始数据的编程错误
- 加入const可以处理const和非const实参，否则只能接受非const数据
- 使用const引用可以使函数生成并使用正确的临时变量

### 16.4引用传递与结构体

​	引用本就是为了处理结构体数据而使用的，并不是为了基本的数据类型，对于普通变量可以使用值传递，也可以使用指针传递，还可以使用引用传递；对于数组只能使用指针传递而不能使用值传递，也不能使用引用传递；结构体可以使用指针传递，也能使用值传递，还可以使用引用传递，引用传递的高效可以避免拷贝数据浪费的内存和时间，使结构体成为一个整体的对象或实体使用，类似于string对象；如果希望不改变原始数据，还可以加入const，更多的规则说明见[16.7如何选择引用、指针和值传递](#16.7如何选择引用、指针和值传递)

```c++
struct job
{
	char name[40];
	double salary;
	int floor;
};
// 3种方式均可以处理结构体相关的函数
void Swap(job j1, job j2);// 要拷贝副本
void Swap(job &j1, job &j2);// 无需拷贝副本,但是可能会修改原结构体数据
void Swap(job *jp1, job *jp2);// 无需拷贝副本,但是可能会修改原结构体数据
void Swap(const job &j1,const job &j2);// 无需拷贝副本,且不会修改原结构体数据
void Swap(job *jp1, const job *jp2)；// 无需拷贝副本,且不会修改原结构体数据
```

​	三种函数方式交换结构体来说明有何不同。

​	第一种方式使用值传递：值传递不能交换结构体的地址，无论在主程序还是在函数内部都是，但是在函数内部打印结构体成员发现确实交换了值；这是因为结构体创建后就代表一个内存块，这个地址不会改变。

```c++
struct job
{
	char name[40];
	double salary;
	int floor;
};
void Swap(job j1, job j2)
{
	cout << "before swap：" << " &j1=" << &j1 << "   &j2=" << &j2 << endl;
	job temp;
	temp = j1;//结构体允许赋值运算符
	j1 = j2;
	j2 = temp;
	cout << "after swap：" << " &j1=" << &j1 << "   &j2=" << &j2 << endl;// 和主程序的地址不同,但也不能交换地址
	cout << "j1.salary=" << j1.salary << "   j2.salary=" << j2.salary << endl;// 内部的值发生了交换
}
job j1 = { "a",1.5,3 },j2 = {"b",2.4,6};
cout << "before swap：" <<" &j1="<<& j1 << "   &j2="<< & j2 << endl;
Swap(j1,j2);
cout << "after swap：" << " &j1=" << &j1 << "   &j2=" << &j2 << endl;// 地址没有改变
cout << "j1.salary=" << j1.salary << "   j2.salary=" << j2.salary << endl;// 值发生交换
```

​	使用引用传递：只有两个改动，第一个函数定义加入&，第二个引用传递内部没有创建副本，所以地址和主程序的地址还是一样的，其他完全一致，结构体交换依然是通过交换值而不是地址实现的

```c++
void Swap(job &j1, job &j2)
{
	cout << "before swap：" << " &j1=" << &j1 << "   &j2=" << &j2 << endl;
	job temp;
	temp = j1;//结构体允许赋值运算符
	j1 = j2;
	j2 = temp;
	cout << "after swap：" << " &j1=" << &j1 << "   &j2=" << &j2 << endl;// 引用传递和值传递的区别和主程序的地址相同,但也不能交换地址
	cout << "j1.salary=" << j1.salary << "   j2.salary=" << j2.salary << endl;// 内部的值发生了交换
}
```

​	使用指针传递：效果和引用传递完全一样，不交换地址但是交换了值

```c++
void Swap(job *jp1, job *jp2)
{
	cout << "before swap：" << " jp1=" << jp1 << "   jp2=" << jp2 << endl;
	job temp;
	temp = *jp1;//结构体允许赋值运算符
	*jp1 = *jp2;
	*jp2 = temp;
	cout << "after swap：" << " jp1=" << jp1 << "   jp2=" << jp2 << endl;// 指针传递和值传递的区别和主程序的地址相同,但也不能交换地址
	cout << "j1.salary=" << jp1->salary << "   j2.salary=" << jp2->salary << endl;// 内部的值发生了交换
}
job j1 = { "a",1.5,3 },j2 = {"b",2.4,6};
cout << "before swap：" <<" &j1="<<& j1 << "   &j2="<< & j2 << endl;
Swap(&j1,&j2);
cout << "after swap：" << " &j1=" << &j1 << "   &j2=" << &j2 << endl;// 地址没有改变
cout << "j1.salary=" << j1.salary << "   j2.salary=" << j2.salary << endl;// 值发生交换
```

​	处理结构体的函数最好返回引用，而不是结构。第一种方式，相当于返回的结构体复制到一个位置，再把这个位置的数据赋值给接收的对象，赋值也只是拷贝值而非交换地址；而第二种方式引用可以直接将返回的结构体赋值到接收的对象而无需中间环节；第三种方式是指针引用，效果和引用传递相同。

​	第四种和第五种方式都是加入const限定，不能赋值，所以也就无法完成交换功能了

```c++
// 常量引用
void Swap(job &j1, const job &j2)
{
    cout << "before swap：" << " &j1=" << &j1 << "   &j2=" << &j2 << endl;
    job temp;
    temp = j1;//结构体允许赋值运算符
    j1 = j2; // valid,非const可更改
    j2 = temp; // invalid ,const不可更改
}
// 常量指针
void Swap(job *jp1, const job *jp2)
{
    cout << "before swap：" << " &j1=" << jp1 << "   &j2=" << jp2 << endl;
    job temp;
    temp = *jp1;//结构体允许赋值运算符
    *jp1 = *jp2; // valid,非const可更改
    *jp2 = temp; // invalid ,const不可更改
}
```

​	上述五种方式都是void函数，下面举例一个返回结构体引用的函数

​	为了不改变原始数据使用const限定，如下方代码所示，目标文件可以修改，源文件不可修改，返回的是目标文件的引用

​	这样可以直接target-->dup赋值，如果返回的不是引用，如定义的是job target，那么target->temp->dup，效率低

```c++
job & func(job & target,const job &source)
{
  ....
  return target ;
}
dup = func(target,source) ; 
```

​	但是需要注意的是返回的是引用，可以作为左值存在，即下方代码是合法的

```c++
dup1 = func(target,source1) ;// source1复制数据到target,dup1是target的引用
func(target,source)= dup1 ;
// 此代码等价于：target使用了source的内容返回dup,之后直接用dup1覆盖了dup
```

​	**<u>但是这个引用必须是调用程序创建的而不是函数中创建的引用，否则函数执行完毕会出现错误</u>**

​	如果不希望返回值是可修改的，所以可以使用返回值限定，对于引用而言，返回类型和函数标头类型可以不同

```c++
const job & func(job & target,const job &source)
{
  ....
  return target ;
}
dup1 = func(target,source1) ;
// func(target,source)= dup1 ; // 非法,因为左值是const不可修改的
```

​	

### 16.5引用传递与类对象

​	这里以string对象举例，其他的ostream、istream、ofstream、ifstream对象是类似的，也可以作为参数

​	注：ostream、istream是基类，ofstream、ifstream是派生类，涉及继承关系，见[16.6引用传递和继承](#16.6引用传递和继承)

```c++
string verson1(const string & s1 , const string & s2)
// const string& verson1(const string & s1 , const string & s2) 如果是下方这种代码不能这样定义函数
{
    string temp; // 这里temp不是引用,是对象
    temp = s2 + s1 +s2 ; // 对象可以使用引用的值
    return temp ;// 返回的可以是对象,也可以是引用
}
// 但是这里必须返回的是对象,即用string接收而不能用 string&接收，因为引用是函数内部创建的,函数执行完毕会消失

```

​	返回引用也是可以的，但是注意传入的引用对象最好加上const限定

```c++
const string& verson1(string & s1 , const string & s2)
// const string& verson1(const string & s1 , const string & s2) 最好这样定义函数
{
    s1 = s2 + s1 + s2; // 引用
    return s1 ; // 可以返回引用,这个引用是主程序创建的,合法,但是会有副作用,s1会被修改
}
```

	 ### 16.6引用传递和继承

​	基类的引用可以指向派生类的对象，而无需进行强制类型转换

​	那么可以定义一个基类的引用函数，调用此函数可以传入基类参数，也可以传入派生类参数

​	father & func(father & f)-----> func(father),father(son)

​	现在定义一个ostream&的函数，此函数可以传入ostream类对象，也可以传入ofstream类对象

​	关于这部分内容，在这里不详细说明，属于高级内容，书P223页和第17章具体说明

```c++
#include <iostream>
#include <fstream>
```

### 16.7如何选择引用、指针和值传递

​		部分内容见[16.4引用传递与结构体](#16.4引用传递与结构体)

- 如果数据对象很小，内置数据类型或小型结构体使用按值传递

- 数据对象是数组，只能使用指针传递，是唯一的选择

- 较大的结构体使用指针或者引用

- 数据对象是类对象，使用引用最好，好于指针

  以上总结：如果不希望修改原始对象使用const限定

##  17.类与对象

### 17.1构造与析构函数

​	在一个头文件提供类的原型，在另一个cpp文件进行实现

​	主要的注意事项有：

1. 构造和析构函数可以重载
2. 构造函数可以列表初始化
3. 类的实例可以组成对象数组
4. 定义一个所有类实例化对象都使用的常量应当使用static，这样所有实例共享一个内存减小开销
5. 类成员函数的参数名不要和私有成员变量名相同
6. 类成员函数如果要求不修改私有成员，应当在函数定义末尾加上const，这样限制的是调用对象隐式的自身不被修改，而在参数名中使用const，是限制显示的访问对象的值不被修改
7. this指针就是当前类实例化的当前对象自身地址，而对于指针类型需要使用箭头而不是句点运算

```c++
// 包含于一个头文件person.h
#ifndef PERSON_H_
#define PERSON_H_
class Person
{
    private :
    const int m_size = 10 ; // 这样定义常量，主程序实例化不同的对象时，并非共享的
    static int m_siz = 10 ; // 可以把常量的作用域变为类内，这样不同的对象使用的都是同一个了
    std :: string m_name;
    int m_age;
    double m_salary ;
    void square_age(){value = m_age * m_age ;}// 简单的私有内连函数
    public:
    	Person();// 默认构造函数
    	Person(int x , double & y);// 构造函数可以重载
    	~Person(); // 默认析构函数
    	// 也可以重载析构函数
    	void func1(const std :: string & name , double age); // 常量引用,值不能改
    	// 注意参数名不要与私有变量成员重名
    	void func2(int x, int y);
    	void show();
    	void show1() const ; // 最好使用这种方法,const成员函数
}
#endif
// 实现文件person.cpp
#include "person.h"
Person :: Person() // 默认构造函数
{
    ... // 可以什么都没有
}
Person :: Person(int x , double & y)//构造函数重载
{
    ...// 实现代码
}
Person :: ~Person() // 默认析构函数
{
    ... // 可以什么都没有
}
void Person::func1(const std :: string & co , double w)
{
    ...// 实现代码
}
void Person::func2(int x , int y)
{
    ... // 实现代码
}
void Person::show() // 不保证是否修改实例
{
    ... // 实现代码
}
void Person :: show1() const // 保证不可修改实例
{
    ... // 实现代码
    this->func1(); // this就是当前类实例化的当前对象自身地址，而对于指针类型需要使用箭头而不是句点运算
}
// 主文件main
// 使用类
#include "person.h"
int main()
{
    Person p1 ; // 默认构造实例化
    Person p11 = {}; // 也是默认构造实例化,可以称为列表初始化，类 名称 = {参数}
    int x = 5 ;
    double & y = x ;
    Person p2(5,y); // 重载构造
    Person p22 = {5,y} ; // 重载构造的列表初始化
    Person p3 = p2(5,y) ;// 注意，这是赋值，如果赋值和构造都可以最好使用构造
    
    // 关于show和show1的不同
    const Person p4 ;
    // p4.show() ; // invalid 无法确保show是否会更改p4
    p4.show1() ; // valid
    
    // 创建对象数组也是可以的
    Person my_person1[4]; // 全部使用默认构造
    Person my_person2[2]={ Person (5,y),Person()} ;// 特定初始化
     
}
```

### 17.2this指针

​	先说结论，this指针是类实例化后的当前对象地址本身，而对于指针类型需要使用箭头而不是句点运算。例如一个类内部实现的比较函数，用于比较Person产生的两个实例p1和p2的年龄大小，比较函数的原型、实现和调用为

```c++
const Person & compare (const Person & p) const ;// 原型
// 实现
const Person & Person :: compare (const Person & p) const
{
    if (p.m_age > this->m_age)// 是p.m_age > m_age 的显示化表达
        return  p ;
    else
        return  * this ;
}
// 调用
Person p1 ,p2 ;
top = p1.compare(p2);// p2被显示访问,p1为自身被隐式访问,this为p1的地址
// or 
top = p2.compare(p1);// p1被显示访问,p2为自身被隐式访问,this为p2的地址
```

​	原型有4个要点：

1. 为了不改变被显示访问的值，compare的参数是const的
2. 类似于结构体，被显示访问的对象最好传递引用，所以 使用的是const  Person & p
3. 被隐式访问的调用对象自身的值也不希望被改变，所以在函数定义末尾加入const
4. 同时要求是比较，返回的是实例，为了节省内存同样使用引用，所以需要对this解引用

### 17.3运算符重载

​	重载运算符使用operator+()，表明重载加号运算符

```c++
// 正常实现两个类的年龄和需要定义函数实现
Person Sum(const Person & p) const ; // 原型
Person operator+(const Person &p)const; // 运算符重载只需要将operator+替换Sum即可
// 实现
Person Person :: Sum(const Person & p) const
{
    // 注意返回的是Person不是引用,因为求和需要返回一个副本
    Peson total ;
    total.m_age = m_age + p.m_age ;
    return total ; // 返回实例
}
Person Person :: operator+(const Person & p) const // 运算符重载只需要将operator+替换Sum即可
{
    // 注意返回的是Person不是引用,因为求和需要返回一个副本
    Peson total ;
    total.m_age = m_age + p.m_age ;
    return total ; // 返回实例
}
// 调用
Person p1(5,y),p2(10,y); // 假设p1和p2的m_age分别为5,10
Person p3 ;
p3 = p1.Sum(p2);// 使用方法求和
// 如果是运算符重载呢？只需要使用加法即可
p3 = p1 + p2;// valid,其实隐式的调用了p1.operator+(p2)

```

1. 重载不能将减法重载为加法
2. 不能修改运算符的优先级
3. 不能创建新的运算符
4. 不能重载特殊运算符，如sizeof、句号成员运算符.、作用域解析符::、指针运算符*、条件运算符？:，以及typeid、const_cast、dynamic_cast、reinterpret_cast、static_cast等
5. 大多数运算符可以通过成员函数也可以通过非成员函数(一般是友元函数)重载，但是赋值运算符=、函数调用运算符()、下标运算符[]、指针访问成员箭头运算→只能通过成员函数重载

### 17.4友元

​	友元包括友元函数、友元类和友元成员函数

#### 17.4.1友元函数

​	让函数成为类的友元，这个函数就可以访问类的私有属性

​	友元函数的问题起源于重载二元运算符的问题，二元运算符要求两侧分别是类对象和数据类型对象(int或double等)，普通二元运算符的重载要求第一个操作数必须是类对象，这就引起一个问题，下方的第3行代码无效的

```c++
Person p1 ;
Person p1 * 3 ; // valid
Person 3 * p1 ; // invalid
```

​	且二元运算符是不能类内声明的，这就导致这个函数不是类内的成员函数，这就意味着类实例化的对象使用此函数不能访问私有变量，也就不能实现目的

```c++
// 声明
class Person
{
private:
	int _age;
	std :: string name;
	double _salary;
// public:
	/*Person operator*(double s, const Person& p);*/
};
Person operator*(const Person& p, double s); // 二元运算符必须类外声明,此函数不是类的成员函数

// 实现
Person operator*(const Person& p, double s) // 类外声明不需要作用域限定
{
	Person result;
	//result._age;// 不能访问私有属性
	//result._name; // 不能访问私有属性
	// 也就提不到重载的问题
}
```

​	解决这个问题的方法是使用friend，friend就可以让二元运算符的重载在类内进行声明了，需要注意的是<u>不使用friend'的类外声明和使用friend的类内声明在定义时都无需作用域限定符，因为这个函数不是类的成员函数</u>

```c++
#pragma once
#include <iostream>
#include <string>
// 声明
// 解决类外声明不能访问私有属性的办法
class Person1
{
private:
	int _age;
	std::string name;
	double _salary;
public:
	Person1();
	Person1(int age);
	friend Person1 operator*(const Person1& p, int s); // 这里需要类内声明,此函数是类的成员函数
	void show() const;
};
// 实现
// 解决类外声明不能访问私有属性的办法
Person1 operator*(const Person1& p, int s)// 类内友元声明也不需要作用域限定
{
	Person1 result;
	result._age = p._age * s;// 可以访问私有属性
	result._salary = p._salary * s; //可以访问私有属性
	return result; // 返回的不是引用而是副本

}
Person1::Person1()
{
	_age = _salary = 0;
}
Person1::Person1(int age)
{
	this->_age = age;
}
void Person1::show() const
{
	std::cout << "p.age=" << this->_age<< std::endl; // 只读
}
```

​	重载<<运算符可以见书321页，可以采用这样的定义

```c++
void operator<<(ostream & os , const Person1 & p)
{
    cout << "age = " <<p._age << "   salary=" << p._salary<<endl;
    return os ; // 返回引用是为了可以重复使用 << 运算符
}
// 调用程序
Person p ;
cout << "p： " << p << "/done" ; // valid
// 如果不返回os的引用,cout << "p： " << p 等价于 (cout << "p： ")<<p
// 因为cout是从左到右读取字符串的，所以要求(cout << "p： ")也是cout重载后的，所以返回引用os
```

#### 17.4.2友元类

#### 17.4.3友元成员函数

### 17.5继承









