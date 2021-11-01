#include <iostream>
using namespace std;
#include "quote_pointer.h"
/*
1.语法  :  < class 子类名 : 继承方式 父类名 >
2.继承方式 : 公共继承、保护继承和私有继承
    class A{public : int a ; private : int b ;  protected : int c ;};
    2.1 class B : public A {} 
        父类的公共权限-->子类公共权限
        父类的保护权限-->子类保护权限
        父类的私有权限-->子类无权访问
    2.2 class B : protected A{}
        父类的公共权限-->子类保护权限
        父类的保护权限-->子类保护权限
        父类的私有权限-->子类无权访问
    2.3 class B : private A{}
        父类的公共权限-->子类私有权限
        父类的保护权限-->子类私有权限
        父类的私有权限-->子类无权访问
3.继承中的对象模型
    3.1 父类中所有非静态成员属性都会被子类继承 只是能否访问的问题
        output :  sizeof rustClass : 16
    3.2 查看类结构 
        cd C:\Users\chenbei\Documents\Visual Studio 2019\项目文件\函数_面向对象过渡
        cl /d1 reportSingleClassLayoutjavascriptClass "类的封装继承多态.cpp"
4. 子类和父类的析构和构造顺序 : 先构造后析构
    4.1 父类先构造 然后子类构造
    4.2 子类先析构 然后父类析构
5. 同名成员继承处理方式 : 
    5.1 同名成员属性 : 
        5.1.1 访问子类同名成员 先查找子类再查找父类 子类会覆盖父类
        5.1.2 如果一定要访问父类同名成员 需要加作用域  rust.baseClass::_a 
    5.2 同名成员函数 :  
        5.2.1 rust.up();  调用子类 子类覆盖父类 
        5.2.2 一定要访问父类同名函数 : rust.baseClass::up(); 调用父类
6. 同名静态成员处理方式  : 
    6.1 静态成员属性 : 处理方式与非静态成员相同
    6.2 静态成员函数  : 处理方式与非静态函数相同
7. 多继承语法 : class 子类名 : 继承方式 父类1,父类2,...
    多继承可能引发父类有同名成员 需要作用域区分 实际中不建议使用
    如儿子类有两个父类 都是同名属性 那么需要作用域区分
8. 菱形继承 : virtual 虚基类指针 数据只有一份 虚继承防止二义性
    语法 : class Sheep : virtual public Animal
9. 多态 : 父类引用可以指向子类对象 通过virtual重写父类虚函数
    9.1 静态多态 : 函数重载 和运算符重载属于静态多态 复用函数名
    9.2 动态多态 : 派生类和虚函数实现运行时多态
    9.3. 区别 : 
        9.3.1. 静态多态的函数地址早绑定 - 编译阶段确定函数地址
                  正常而言父类的引用函数仍然执行父类 而不会被子类重写
        9.3.2. 动态多态的函数地址晚绑定 - 运行阶段确定函数地址
                  在父类的函数前边加上virtual即可 变为虚函数 
                  那么子类调用父类的引用函数时就可以重写父类的虚函数
                   注 : 必须是父类的指针或者引用函数
    9.4 结构示意图 : 对于Animal如果只有一个普通函数占据字节为1,加上virtual就变成4
         9.4.1 Animal类内部结构 : 
                  vfptr (virtual function pointer)
                     |
                     |
                    V
                    vftable(虚函数表)  表内记录虚函数的地址 
                    ------------------------------
                  |     &Animal  :: speak       |     (父类的虚函数表没有发生改变)
                  |                                          |
                    ------------------------------
 ************************************************************************************
                    开发者模式 :  cl /d1 reportSingleClassLayoutAnimal "类的封装继承多态.cpp"
                    class Animal    size(8):
                        +---
                    0      | {vfptr}
                    4      | _age
                        +---
                Animal::$vftable@:
                        | &Animal_meta
                        |  0
                    0      | &Animal::speak
        
        9.4.2 Cat类内部结构 :
                  先继承
                  vfptr (virtual function pointer)
                     |
                     |
                    V
                    vftable(虚函数表)  表内记录虚函数的地址                               (子类函数的虚函数表发生改变)
                    ------------------------------        子类有同名函数发生重写              ------------------------------
                  |     &Animal  :: speak        |    ----------------------------------------->   |        &Cat  :: speak        |
                    ------------------------------         那么虚函数表的地址被重写         ------------------------------
  ************************************************************************************
                    开发者模式 :  cl /d1 reportSingleClassLayoutCat "类的封装继承多态.cpp"
                    class Cat       size(8):
                        +---
                    0      | +--- (base class Animal)
                    0      | | {vfptr}
                    4      | | _age
                        | +---
                        +---
                Cat::$vftable@:
                        | &Cat_meta
                        |  0
                    0      | &Cat::speak

        9.4.3 当父类的指针或者引用指向子类对象时 :  发生多态
                 ------>void polymorphic(Animal& animal){ animal.speak();}
                  ------>Cat cat ;
                  ------>polymorphic(cat);
                  ------>Animal  & animal = cat ;
                  ------> animal.speak() ;
                  ------> 实际上找到的是Cat类的虚函数地址  &Cat  :: speak
                  ------> 运行阶段中虚函数地址发生了改变
                  ------> 多态性 : 体现在Dog或者其他类去调用这个虚函数时体现了不同的特性
  
  
  */
class  baseClass
{
public:
    int _base = 110; // 用于多继承
    int _a = 100 ;
    static int _e  ; // 静态成员属性只能外部初始化为常量 不能内部定义
    void up(){cout << "同名函数baseClass父类下的up函数调用" << endl;}
    void down() { cout << "baseClass父类下的down函数调用" << endl; }
    static void func() { cout << "baseClass父类下的同名静态函数func()调用" << endl; }
    baseClass()
    {
        cout << "-------------baseClass构造函数到此一游-------------" << endl;
    }
    ~baseClass()
    {
        cout << "-------------baseClass析构函数到此一游-------------" << endl;
    }
protected:
    int _b;
    void left() { cout << "baseClass父类下的left函数调用" << endl; }
private:
    int _c;
    void right() { cout << "baseClass父类下的right函数调用" << endl; }
};
int baseClass::_e = 60; // 只能类外初始化静态变量 放在全局区
class  baseClass1 { public: int _base = 200; };
class javaClass : public baseClass 
{
public:
    void print()
    { 
        cout << "--------------java--------------" << endl; 
        // 公共权限外部和内部都可以访问
        up(); 
        down();
        // 保护权限只能内部访问
        left(); 
        // 没有子类私有权限
        // 父类私有权限内部和外部都不能访问
        //right();
    }
};
class pythonClass : protected baseClass
{
public:
    void print() 
    {
        cout << "--------------python--------------" << endl; 
        // 没有公共权限
        // 保护权限只能内部访问
        up();
        down();
        left();
        // 没有子类私有权限
        // 父类私有权限内部和外部都不能访问
        //right();
    }
};
class cppClass : private baseClass
{
public:
    int _cpp;// 用于多继承
    void print() 
    { 
        cout << "--------------cpp--------------" << endl; 
        // 没有公共权限
       // 没有保护权限
        // 子类私有权限只能内部访问
        up();
        down();
        left();
        // 父类私有权限内部和外部都不能访问
        //right();
    }
};
class rustClass : public baseClass
{
public: 
    int _a = 1000; //同名对象 不同值
    int _d;
    static int _e;  // 同名静态属性
    void up() { cout << "同名函数rustClass子类下的up函数调用" << endl; }// 同名函数
    static void func() { cout << "rustClass子类下的同名静态函数func()调用" << endl; }
    rustClass()
    {
        cout << "-------------rustClass构造函数到此一游-------------" << endl;
    }
    ~rustClass() 
    {
        cout << "-------------rustClass析构函数到此一游-------------" << endl;
    }
};
int rustClass::_e = 120;// 只能类外初始化静态变量 放在全局区
class javascriptClass : public baseClass,public baseClass1 
{
public:
    int _javascript;
    int _java_script;
    javascriptClass()
    {
        _javascript = -10;
        _java_script = -20;
    }
};
class Animal
{
public:
    int _age;
    virtual void speak()
    {
        cout << "----------------动物在说话----------------" << endl;
    }
};
// 利用virtual 变为虚继承 Animal变为虚基类指针
class Sheep : virtual public Animal{};
class Camel : virtual public Animal{};
class Alpaca : public Sheep, public Camel
{};
class Cat  : public Animal
{
public:
    void speak()
    {
        cout << "----------------猫咪在说话----------------" << endl;
    }
};
class Dog : public Animal
{
public:
    void speak()
    {
        cout << "----------------小狗在说话----------------" << endl;
    }
};
void compare_inherit_method()
{
    javaClass java;
    java.print();
    // 外部可以访问up和down
    //java.down();
    //java.up(); 

    pythonClass python;
    // 外部都不能访问
    python.print();

    cppClass cpp;
    // 外部都不能访问
    cpp.print();
}
void sizeof_rustClass()
{
    cout << "sizeof rustClass : " << sizeof(rustClass) << endl;
}
void construction_rustClass()
{
    rustClass rust;
}
void sameName_attribute_rustClass()
{
    rustClass rust;
    cout << "同名成员属性在子类中(rust._a)_a = " <<rust._a << endl;
    cout << "同名成员属性在父类中(rust.baseClass::_a)_a = " << rust.baseClass::_a << endl;
}
void sameName_func_rustClass()
{
    rustClass rust;
    rust.up(); // 同名函数
    rust.baseClass::up(); // 作用域调用父类
}
void static_sameName_attribute_rustClass()
{
    rustClass rust;
    // 1.通过对象访问 : 
    cout << "通过实例化对象访问静态成员 " << endl;
    cout << "\t同名静态成员属性在子类中(rust._e)_e = " << rust._e << endl;
    cout << "\t同名静态成员属性在父类中(rust.baseClass::_e)_e = " << rust.baseClass::_e << endl;
    // 2.通过类名访问 : 
    cout << "通过类名访问静态成员" << endl;
    cout << "\t同名静态成员属性在子类中(rustClass ::_e)_e = " << rustClass ::_e << endl;
    cout << "\t同名静态成员属性在父类中(baseClass::_e)_e = " << baseClass::_e << endl;
    cout << "\t同名静态成员属性在子类-父类中(rustClass::baseClass::_e)_e = " << rustClass ::baseClass::_e << endl;
}
void static_sameName_func_rustClass()
{
    rustClass rust;
    // 1.通过对象访问静态函数
    cout << "通过实例化对象访问静态函数 " << endl;
    rust.func();
    rust.baseClass::func();
    // 2.通过类名访问 : 
    cout << "通过类名访问静态函数" << endl;
    rustClass::func();
    baseClass::func();
}
void multiple_Inheritance_javascriptClass()
{
    javascriptClass javascript;
    cout << "sizeof javascriptClass :" <<sizeof(javascriptClass)<< endl;
    //cout << "_base = " << javascript._base<<endl; // 提示不明确
    cout << "父类baseClass下的属性_base = " << javascript.baseClass ::_base << endl;
    cout << "父类baseClass1下的属性_base = " << javascript.baseClass1::_base << endl;
    /*
    class javascriptClass   size(28):
        +---
    0      | +--- (base class baseClass)
    0      | | _base
    4      | | _a
    8      | | _b
    12      | | _c
        | +---
    16      | +--- (base class baseClass1)
    16      | | _base
        | +---
    20      | _javascript
    24      | _java_script
        +---
    */
}
void diamond_Inheritance()
{
    // 菱形继承 两个类继承了同一个基类 且一个新类又继承了这两个类
    Alpaca alpaca;
    alpaca.Sheep::_age = 18; // 原本存在二义性
    alpaca.Camel::_age = 28;
    alpaca._age = 38;
    cout << alpaca._age << endl;
    cout << alpaca.Camel::_age << endl;
    cout << alpaca.Sheep::_age << endl; // 变成只有一份数据 38
    cout << "------------------菱形继承模型-------------------"<< endl;
    alpaca.speak();
    alpaca.Sheep::speak();
    alpaca.Camel::speak();
    /*
    * 有二义性 同一个函数
    ----------------动物在说话----------------
    ----------------动物在说话----------------
    ----------------动物在说话----------------
    */
}
// 地址早绑定 在编译阶段确定了函数的地址
// 所以此函数无论传什么对象都执行Animal类的speak函数
// 如果希望执行Cat类的speak函数需要在运行阶段进行绑定(晚绑定)
// 只需要在Animal类speak函数前边加上virtual 即可 即虚函数 这里以Dog类举例
// 注 : 必须是父类的引用或者指针函数 下方是引用函数
void polymorphic(Animal& animal){ animal.speak();}
void doSpeak()
{
    cout << "------------------多态模型-------------------" << endl;
    Cat cat;
    polymorphic(cat);// -----------------猫咪在说话----------------
    Dog dog;
    polymorphic(dog); // ----------------小狗在说话----------------
}
int class_Inheritance()
//int main()
{
    // 比较不同继承方法
    compare_inherit_method();
    // 属性全部继承
    sizeof_rustClass();// sizeof rustClass : 20
    // 析构和构造顺序
    construction_rustClass();
    /* 先进后出
    -------------baseClass构造函数到此一游-------------
    -------------rustClass构造函数到此一游-------------
    -------------rustClass析构函数到此一游-------------
    -------------baseClass析构函数到此一游-------------
    */
    // 继承同名成员属性处理 _a = 100 or 1000?
    sameName_attribute_rustClass();
    /*
    同名成员属性在子类中(rust._a)_a = 1000
    同名成员属性在父类中(rust.baseClass::_a)_a = 100
    */
    // 继承同名函数属性处理
    sameName_func_rustClass();
    // 静态成员属性处理
    static_sameName_attribute_rustClass();
    // 静态成员函数处理
    static_sameName_func_rustClass();
    // 多继承
    multiple_Inheritance_javascriptClass();
    // 菱形继承 
    diamond_Inheritance();
    // 多态 父类引用可以指向子类对象
    doSpeak(); //----------------动物在说话----------------
    return 0;
}


