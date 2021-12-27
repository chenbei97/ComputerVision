## 1.结构体字符串数组赋值

结构体内部定义的char s[]={} 数组是不能直接进行等号赋值的，代码如下

这是因为C风格中字符串本身是个数组，将数组赋给数组是不允许的，只能借助拷贝

C++风格string类是允许等号赋值的，所以相比C更加方便

```c++
struct s 
{
    int age ;
    double length;
    char name[20] = {};
};
struct s s1 ;
// C风格只能使用拷贝或者初始化定义
//  s1.name = "cb"; 非法
// 解决方案：可以在初始化时就赋值,也可以使用strcpy进行拷贝赋值
struct s s2 = {18,1.5,"cb"};
strcpy_s{s1.name,"cb"};
// C++风格允许等号运算符
string str;
str = "cb";
cout << "str=" << str << endl;
```

衍生的注意事项：数组名是数组的地址，引号引起的字符串常量也是地址，对于C风格的字符串不能直接比较字符串数组是否相等，

如下方例子，实际上比较的是两个地址是否相等，答案是否定的，如果需要比较应当使用strcmp函数

如果使用了cstring类，则可以直接进行比较

```c++
word == "mate" ; // 实际上word表示的是存储word的地址，"mate"是该字符串常量的地址,只在C++风格正确
strcmp(word,"mate") !=0 // 相等会返回0
```

## 2.++i和i++的区别

i++;和++i对于表达式而言有区别，对于i的最终值没有区别，但是有先后的不同，先后的不同是表达式有区别的原因

i++先计算表达式，此时i没有变化，之后再自增，所以第一条表达式输出为5

++i先自增，i发生变化，之后计算表达式，所以表达式值为6

在循环中使用++i和i++区别不大，因为并不使用到表达式的值，一般而言++i的效率更高一些，因为后者先复制一个i的副本，这个副本再加1，再返回复制的副本，前者则是直接+1返回结果

```c++
int x1=5,x2=5, y;
y = x1++;
cout << "先计算表达式x1++=" << y << "，然后自增x1=" << x1 << endl;
//先计算表达式x1++ = 5，然后自增x1 = 6
y = ++x2;
cout << "先自增然后计算表达式x2++=" << y << "，此时x2=" << x2 << endl;
//先自增然后计算表达式x2++ = 6，此时x2 = 6
```

## 3.while实现时间延迟

```c++
float secs = 5.0; // 延迟秒数
clock_t delay = secs * CLOCKS_PER_SEC; // 延迟的系统时间
clock_t start = clock(); // 开始的系统时间节点
clock_t end = delay + start;
cout << "start" << endl;
while (clock() < end) //当前时间没有超出结束的系统时间节点
{
    ; // 什么也不做
}
cout << "end" << endl;
```

## 4.字符串的const限定（C和C++风格）

### 4.1字符串的定义

可以使用C风格的 char 也可以使用C++风格的String对象 去定义，分别看成是字符数组和单个变量对象

#### 4.1.1C风格

【1】首先说明C风格的值、地址、解引用的特点

​	<1>值的获取

​	char定义的name对象数组名本身可以看成一个指针，可以执行算术运算，打印的字符是当前指针后面的所有元素

```c++
char name[10] = "name"; // 打印字符串或者打印字符串的一部分 cout << name << name + 1 << endl ; // name , ame，看成指针
```

​	如果想要索引单个字符，需要使用索引，或者对指针解引用，就会得到对应的值

```c++
cout << name[0] << name[2]<< endl; // 直接索引, n、m 
cout << *(name) << *(name+2) << endl; // 指针解引用, n、m
```

<2> 地址的获取

​	name数组名不仅能看成指针，还可以看成值，所以可以对name取地址

​	但是不能对对name+1取地址，因为name+1是看成了指针，指针不能取地址

​	但是指针运算后解引用再取地址是可以的，**<u>这充分说明name本身可以看成指针也可以看成值，</u>**指针

也就是指向了字符数组的首位，cout流会将指针后的内容全部打印出来；同样name+2解引用取地址也

是打印出后面所有的字符

```c++
// &(name+1) 是非法的 , 不能对指针取地址 
cout << &name << " "<<&(*(name+2)) << " " << endl; // 可以对name取地址，和指针解 引用的取地址 
// &name=0x7ffeb5448906 &(*(name+2))=me
```

​	如果一定要得到name+1的地址，需要先定义一个指针n1指向它，再取地址

​	&n1合法，&(name+1)非法，是因为n1一定是指针，name可能是值，可能是指针，这里是指针，所以非法

```c++
// char* n1 = &name 是非法的，因为name这里是指针而非值，只有cout打印时才看成值 
char* n0 = &name[0] ; // 合法，name[0]是值，可以取地址 
char* n1 = name + 1 ; 
char* n2 = name; // 如果打印n1和n2，和直接打印name+1和name是相同的，但是可以取地址了，另外n0和n2也是等价的 // n1和n2可以进行加减运算 
cout << &n1 << &n2 << eendl; // n1和n2差8个位
```

#### 4.1.2C++风格

【2】其次说明C++风格的值、地址和解引用的获取，相比C风格更好理解

​	相比于C风格的name可以是值也可以是指针，string定义的对象age只能看成值

​	<1>值的获取

```c++
string age = "age"; 
cout << age << endl ; 
// cout << age+1 << endl; 是非法的，age是值不是指针，不能运算
```

​	<2> 地址的获取

​	同样可以对值age直接取地址，但是不能对age+1取地址，相应的解引用也是不合法的

```c++
cout << &age << endl; 
// &(age+1)非法 
// *(age+1)非法
```

​	如果希望得到指定字符的地址，同样需要先定义指针来获取，**<u>不过该指针是普通的变量指针而非数组指针</u>**，所以不同于char的n1和n2，加减运算没有意义，string对象是一个整体，n1+1是一个字符，a+1什么也不是

```c++
string* a = &age ; 
cout << a << endl; // 地址 
cout << *a << endl; // 值=age 
cout << *(a+1) << endl ; // 虽然不非法，但是指向的指针是空的没有值，打印不出来 
// 在这里说明了string和char[]虽然都可以定义字符串，但是一个是字符数组，一个是普通变量
```

#### 4.1.3案例

​	从语句3可以看出直接打印string对象和char[]对象的内容是一样的，此时char的数组名看成值

```c++
// <1>char的单数组类型或string的单对象类型 
// ① char和string 
char shanghai[30] = "shanghai"; 
char beijing[30] = "beijing"; 
char tianjin[30] = "tianjin"; 
char nanjing[30] = "nanjing";// 语句1 
string ShangHai = "shanghai"; 
string BeiJing = "BeiJing"; 
string NanJing = "NanJing"; 
string TianJin = "TianJin";// 语句2 
cout << "shanghai = " << shanghai << " ShangHai=" << ShangHai << endl;// 语句3
```

​	定义指针可以指向shanghai，也可以指向shanghai[0]的地址，一个看成指针，一个看成值的地址，如语句4和5

​	对于string对象只能使用&ShangHai，因为ShangHai是单个变量，不是指针，所以语句7，8都是非法的

```c++
// ②char*和string* 
char* sh = shanghai; // 语句4,shanghai是变量,值可以更改所以使用char*定义即可 
char* sh1 = &shanghai[0];// 语句5,和语句4等价 
string* SH = &ShangHai; // 语句6,只能使用&ShangHai 
// string* SH1 = &ShangHai[0]; 语句7,非法 
// string* SH1 = ShangHai ; 语句8，非法 
cout << "sh=" << sh << " sh1=" << sh1 << " SH=" << SH << endl; // 语句9,sh,sh1 依然字符串而不是地址,sh=sh1 
cout << "sh+2=" << sh + 2 << " sh1+2=" << sh1 + 2 << " SH+2=" << SH + 2 << endl;//语句10,输出anghai,其实也说明char[]字符串本身在cout流下就是地址，只是表现为值；但SH+2 打印出来的是内存地址，而不是值
```

### 4.2引入const后的区别

​	首先说明，char* const 和 const char* 是一样的，const的顺序没有影响

​	但是char const * 和 char* const是不同的，前者是常量指针，后者是指针常量，没有const为普通指针

​	指针常量可以改变值，不能改变指向；常量指针相反，可以改变指向，不能该变值

​	一个微妙的问题是，对一个指向a的常量指针p来说，说明的是对自身p而言，a是常量，并不是a就是常量；a可以通过别的普通指针进行修改，但是不能通过这个指针p来修改，这是需要理解的地方！！！

​	指针的定义存在6种情况：

- 将常规变量的地址赋给常规指针
- 将常规变量的地址赋给常量指针
- 将常规变量的地址赋给指针常量
- 将const变量的地址赋给常规指针 （无效），因为能赋值的话意味着常规指针可以修改const变量的值，这与const本身冲突
- 将const变量的地址赋给常量指针
- 将const变量的地址赋给指针常量（无效），指针常量也可以修改值，与const本身冲突

#### 4.2.1C风格

​	对于C风格，在4.1.1的定义指针中，是已经定义了数组name，然后使用指针指向，所以可以使用

char* n = name;，但是直接使用char* n = "name";是不允许的，因为编译器认为这个字符串常量是不

能修改的，不是变量，所以需要const修饰

​	故语句11非法，语句12合法，由常量指针的性质知语句14非法，语句15合法

```c++
// ③const char*/char const* 常量指针 
// 如果直接对常量字符数组定义指针 必须使用const 
// char* sh2 = "shanghai"; 语句11,非法 
const char* sh3 = "shanghai"; //语句12,合法,常量指针的指向可以改变,值不可以改变 
char const* sh4 = "shanghai"; // 语句13,char const* 和const char*等价 
// *sh3= "123"; 语句14,非法,值不能改变 
cout << "sh3+2="<<sh3+2<<" sh4+2="<<sh4 + 2 << endl; // 语句15,指向可以改变,=anghai,类似于语句10
```

​	对指针常量，性质相反，见语句17-18；特别的即使改变值也是用变量，不能用常量，见语句19

```c++
// ④char* const 指针常量 
char* const sh5 = shanghai;//语句16,指向不能改变,值可以改变 
// sh5 = bejjing; 语句17,改变指向非法 
*sh5 = *beijing; // 语句18,可以改变值 
// *sh5 = "sh5"; // 语句19,非法,虽然可以改变值但也不能用常量赋值
```

#### 4.2.2C++风格

​	和C风格的相同点是不能直接定义对字符串的指针，即语句20，不同点是加上const限定也是不行的，

C风格加上限定即可，即语句12。错误原因并非是没用const限定，而是因为编译器认为引号括起的字符

串是const char类型，string*类型是不能去指向字符串的。

​	所以string* 需要指向变量，见语句22-23，语句24说明普通指针可改变值，语句26说明string const */ const string *不能改变值

```c++
// ⑤const string* string const* 常量指针 
//string* SH2 = "ShangHai"; 语句20,非法 
//const string* SH3 = "ShangHai";语句21, 非法 
// "ShangHai"认为是const char* 类型不能使用string*也不能使用
const string* const string* SH1 = &ShangHai; // 语句22 
string const* SH2 = &ShangHai; // 语句23,string const* 和const string*等价 
*SH = "SH"; // 语句24，对应语句6，普通指针可以改变值 
cout << "更改*SH后此时ShangHai=" << ShangHai << endl;//语句25, string对象的值是可以改 变的
// *SH1 = "SH1"; *SH2 = "SH2"; 语句26·,非法const string*值不可更改
```

​	指针常量，值改变，指向不改变，这里还有区别；string的指针常量值改变可以用字符串赋值，char[]

不可以，见语句29和19

```c++
// ⑥string* const 指针常量 
string* const SH3 = &BeiJing; //语句27 
*SH3 = ShangHai;//语句28,值可以改变 
*SH3 = "SH3"; // 语句29,对照语句19,string类的值可以通过赋值常量字符串来改变，char* const 不可以 
// SH3 = &ShangHai; 语句30,指向不能更改
```

### 4.3定义字符串的数组

​	由于C风格字符串本身就是字符数组，所以定义字符串的数组又有很多种方式，同时也与string是不同的

​	string本身是普通变量，所以string[]即可定义数组，更符合理解习惯

​	char[]本身不是字符串数组，是字符数组，所以可以使用二维的字符数组来定义，也可使用char*char[]进行定义

#### 4.3.1C风格

##### 4.3.1.1二维字符数组定义

​	直接使用二维数组定义，必须使用常量字符串，不可使用变量

```c++
// <2>char的多数组类型或string的数组类型 
// ① char的多数组类型-->使用二维数组定义 
char cities11[4][10] = { "ab","ac","bc","abc" }; //语句31 
// char cities12[4][10] = { tianjin,"ac","bc","abc" }; 语句32,不能掺杂 
// char cities13[4][10] = { tianjin,tianjin,tianjin,tianjin }; 语句33,不掺杂也不行
```

##### 4.3.1.2普通指针定义

​	语句34定义了由变量字符数组组成的字符串指针cities21-24，不能掺杂常量字符数组，否则非法，见语句35

​	此字符串指针是普通指针，指向了第一个变量字符数组，可以解引用后赋值，*cities23 和 *cities23[0]是相同的；直接使用字符变量解引用的值去赋值也可以，见语句36和37，但不能使用常量字符串去赋值，见语句39

​	cities21是指针，指向的值想要改变要解引用，见语句38

```c++
// ② char的多数组类型-->使用指针定义 （普通指针）只能使用变量不能掺杂常量 
char* cities21[4] = {beijing,nanjing ,tianjin,shanghai }; // 语句34, 
char* cities22[4] = { nanjing , beijing,tianjin,shanghai }; 
char* cities23[4] = { nanjing , beijing,shanghai,tianjin }; 
char* cities24[4] = { beijing,nanjing ,tianjin,shanghai }; 
// char* cities[4] = { "bbbb",nanjing ,tianjin,shanghai }; 语句35,掺杂是非法的,要使用const限定 
*cities23 = *(cities24+1); // 语句36,本身的指向也可以改变，不等价于使用 *cities23[0]=*cities24[0] 
*cities23[0]=*cities24[0]; // 不同于语句36，这是改变值,使用字符串指针成员
cout << "*cities23=" << *cities23 << " *cities24=" << *cities24 << endl; 
*cities21[0] = *nanjing; // 语句37,值可以改变,合法，使用变量字符数组也可 
// cities21[0] = *nanjing; 语句38,值可以改变,非法,需要解引用 
// *cities21[0] = "beijing"; 语句39,值可以改变,非法,不能用常量
```

​	两个指针是不能直接相等赋值的，不论在char*，还是char *[] ，还是string *与 string *[]都是一样的，见语句40

​	字符串指针的成员cities21[0]是可以改变指向的，ciities21本身不能改变，可以指向变量字符数组，见语句41；也可以指向另一个字符串指针的额成员，见语句42

```c++
// cities21 = cities22; 语句40, 直接指向非法 
cities21[0] = tianjin; // 语句41,元素的指向可以改变,元素指向char[]数组 
cout << "cities21[0]=" << cities21[0] <<" cities21[2]="<< cities21[2]<< " cities22[3]="<<cities22[3]<<endl; // tianjin , tianjin ,bhanghai（语句16影响了） 
cities21[2] = cities22[3]; // 语句42,元素的指向可以改变,元素指向char*[]指针的成员 
cout << "*cities21[2]=" << *cities21[2] <<" cities21[2]="<< cities21[2] << endl; // *cities21[2]=b , cities21[2]=bhanghai
```

##### 4.3.1.3常量指针定义

​	常量指针必须使用const定义，掺杂也是

```c++
// ③ char的多数组类型-->使用指针定义（常量指针） 
// char* cities31[4] = { "ab","ac","bc","abc" } ; 语句43,非法,不同于二维数组的定义方式，对于常量指针必须加以const限定 
const char* cities31[4] = { "ab","ac","bc","abc" }; //语句44, 
char const * cities32[4] = { "1","ac","bc","abc" };//语句45,等价 
char const* cities33[4] = { "ab","ac","bc",beijing};//语句46,掺杂也要使用const限定 
// cities31 =cities32 ;语句47,直接指向也非法，见语句40
```

​	值不可以改变，指向可以改变，依然针对的是成员，但成员的值是不能改变的

​	因为成员都是常量字符串，所以值在成员层面上都是不能修改的，字符串指针更不能进行改变，这也是为何定义常量指针只能选用常量字符数组的原因，用const char *成员组成的数组必然也是const

```c++
cities31[0] = cities33[3]; //语句48，类似语句42，指向可以改变 
cout <<"cities31[0]= "<< cities31[0]<<" cities33[3] = " << cities33[3] << endl; // neijing,neijing , 可以改变指向（语句37影响） 
cout << *cities31 <<" " << *cities32<<endl; // ab , 1 
*cities31 = *(cities32+1);// 语句49,指向可以改变，指向另一个字符串指针的成员 
// *cities31[0] = *cities32[0]; 值不能改变 
cout << *cities31 <<" " << *cities32<<endl;// ac, 1 
*(cities31+1) = "2";// 语句50其实这样也是改变指向，而不是值，从指向1个常量字符串变为指向另1个常量字符串 
cout << *(cities31+1) << endl; // 2
```

​	总结也就是常量指针定义的字符数组的数组不能改变值，但是可以改变地址。特别强调的是语句50，语句50很像是把一个值赋给了一个变量，但是这是错误的认识，*(cities31+1)实际上是指针，右边只是把字符串2的地址为了它，还是因为"2"可以看成值，也可以看成地址

​	如果希望字符串数组不仅不能改变值，也不能改变指向呢？还可以加入const限定

```c++
const char* const cities31[4] = { "ab","ac","bc","abc" }; // 语句44的基础上加了const
// 从右往左读，cities31[4]="abc"整体是一个指针，const继续限定了方向，也就是指针常量
// 之后const char *是对指针常量cities31[4]的解引用限定，所以还是常量指针
// 只不过这里是常量指针定义，一经初始化值就不能更改，再用const限定方向，如果初始化没用常量字符串..？
// 对普通指针定义的字符串数组，分别加上2个const限定，更加符合认识，从值、地址均可修改变为均不可修改
const char* const cities21[4] = {beijing,nanjing ,tianjin,shanghai}; // 语句34使用双const限定
```



##### 4.3.1.4指针常量定义

​	指向字符串数组指针定义时就必须使用变量字符数组而非常量字符数组，这样就可以保证字符串数组

指针可以修改值而不能修改指向,见语句51

```c++
// ④ char的多数组类型-->使用指针定义（指针常量） 
char* const cities41[4] = { beijing,nanjing ,tianjin,shanghai }; 
char* const cities42[4] = { nanjing , beijing,tianjin,shanghai }; 
//cities41 = cities42; 语句50,直接指向非法
// cities41[0] = cities42[3]; 语句51,[]指向不能改变 
//*cities41 = *(cities42+1); / 语句51,*指向不能改变 
*cities41[0] = *cities42[0] ;// 语句52,值可以改变 
*(cities41[0]) = *(cities42[0]) ; // 和语句52等价 
cout << *cities41[0] <<" " << *cities42[0] <<endl; // 3, 3
```

#### 4.3.2C++风格

​	对于C++风格，可以使用常量字符串也可以使用变量字符数组定义string[]数组，更加符合习惯

```c++
// ⑤ string的数组类型-->使用单数组定义 
string cities51[4] = {"a","b","v","d"}; // 语句53, 
string cities52[4] = { shanghai,beijing,tianjin,nanjing }; //语句54,不同于语句30,可以用变量
```

​	string[]无需二维对象才能存储多个字符串，string[ ] [ ]可以变成不同形状了

```c++
string a ="1";
string b ="2";
string c ="3"; 
string A[3] = {a,b,c}; 
string B[3][2]= {a,b,c,c,b,a};
```

##### 4.3.2.1普通指针定义

​	注意，对于string*是不能直接使用char[]类型的数组初始化，无论是常量还是变量，见语句55-56

​	因为字符数组名字可以是地址也可以是值，所以才能定义时直接存放数组名，见语句34和语句44

​	但是string* 只能使用string对象的地址初始化，见语句57

```c++
// ⑥ string的数组类型-->使用指针定义（普通指针） 
// string* cities61[4] = { "a","b","v","d" }; 语句55,非法,不能用char常量初始化 string*对象 
// string* cities61[4] = { shanghai,beijing,tianjin,nanjing }; 语句56, 非法,也不能 用char变量初始化string*对象 
string* cities61[4] = { &ShangHai,&NanJing,&TianJin,&BeiJing }; //语句57, string 数组指针只能存放地址 
string* cities62[4] = { &NanJing,&ShangHai,&TianJin,&BeiJing }; 
// cities61 = cities62; // 语句58,string类也不能直接改变指向，参看语句40和50 
cities61[0] = cities62[2]; // 语句59,元素是地址可以更改指向 
cities61[0] = &BeiJing ; // 改变指向 
*cities61[0] = *cities62[2]; // 语句60,也可以更改值 
*cities61[0] = TianJin ; // 改变值
```

##### 4.3.2.2常量指针定义

​	不同于C风格，string数组的常量指针不需要使用指向string的常量指针组成，定义方式是一样的，还

是直接使用string对象的地址即可

```c++
// ⑦ string的数组类型-->使用指针定义（常量指针） 
// string const* cities71[4] = { "a","b","v","d" }; 不能用char常量初始化string*对 
// string const* cities71[4] = { shanghai,beijing,tianjin,nanjing }; 不能用char常量初始化string*对 
string const* cities71[4] = { &ShangHai,&NanJing,&TianJin,&BeiJing }; // 语句61, 同语句57 
string const* cities72[4] = { &NanJing,&ShangHai,&TianJin,&BeiJing }; 
// cities71 = cities72; 语句62,同语句58 
cities71[0] = cities72[2];// 语句63,可以改指向 
cities71[0] = &TianJin; // 改指向
// *cities71[0] = *cities72[2]; 语句64,不可更改值 
// *cities71[0] = TianJin ; 不可更改值
```

##### 4.3.2.3指针常量定义

​	定义方式不变，使用string对象的地址

```c++
// ⑧ string的数组类型-->使用指针定义（指针常量） 
// string* const cities81[4] = { "a","b","v","d" };同语句55 
// string* const cities81[4] = { shanghai,beijing,tianjin,nanjing };同语句56 
string* const cities81[4] = { &ShangHai,&NanJing,&TianJin,&BeiJing }; // 语句65, 同语句57 
string* const cities82[4] = { &NanJing,&ShangHai,&TianJin,&BeiJing }; 
// cities81 = cities82; 语句66,同语句58 
//cities81[0] = cities82[2]; 语句67,不可以改指向 
// cities81[0] = &TianJin; 不可更改指向 
*cities81[0] = *cities82[2]; // 语句68, 可更改值 
*cities81[0] = TianJin; // 可更改值
```

## 5.值传递和引用传递

​	首先说明引用传递不违反按值传递的规则，只是传递的是地址值而非实际值，这种方式在数组很大时是很有效的，避免了复制数组消耗的时间和内存

### 5.1值传递

​	值传递就是直接传递实例，但是实例在函数中会产生副本，函数执行完毕会释放

```c++
double func(double x); // 原型
int main()
{
    double width = 5.0; // width是实参，值传递
    double v = func(width) ; 
}
double func(double x)
{
    // x 是 形参，按值传递时x实际上是width的副本
    return x * x * x
}
```

### 5.2引用传递

​	当且仅当函数头或函数原型中指针表示法int * arr 与 数组表示法int arr[]是等价的，在函数体中不能使用int arr[]说明arr是一个指针

​	那么可以知道，实际上内部将函数int sum_arr(int arr[] , int n) 解释为 int sum_arr(int* arr , int n)

```c++
int sum_arr(int arr[] , int n)
{
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

​	在函数体中无论使用上述的哪种函数头，都可以使用数组表示法访问数组元素，这是因为，存在两个恒等式

​	对数组使用下标等价于使用指针做加减法，对指针取地址；对指针成员取地址等价于指针指向该成员

```c++
arr[i] == *(arr + i); 
arr == &arr[0] ;
&arr[i] == arr + i ;
```

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

