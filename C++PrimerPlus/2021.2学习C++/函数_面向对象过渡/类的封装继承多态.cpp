#include <iostream>
using namespace std;
#include "quote_pointer.h"
/*
1.�﷨  :  < class ������ : �̳з�ʽ ������ >
2.�̳з�ʽ : �����̳С������̳к�˽�м̳�
    class A{public : int a ; private : int b ;  protected : int c ;};
    2.1 class B : public A {} 
        ����Ĺ���Ȩ��-->���๫��Ȩ��
        ����ı���Ȩ��-->���ౣ��Ȩ��
        �����˽��Ȩ��-->������Ȩ����
    2.2 class B : protected A{}
        ����Ĺ���Ȩ��-->���ౣ��Ȩ��
        ����ı���Ȩ��-->���ౣ��Ȩ��
        �����˽��Ȩ��-->������Ȩ����
    2.3 class B : private A{}
        ����Ĺ���Ȩ��-->����˽��Ȩ��
        ����ı���Ȩ��-->����˽��Ȩ��
        �����˽��Ȩ��-->������Ȩ����
3.�̳��еĶ���ģ��
    3.1 ���������зǾ�̬��Ա���Զ��ᱻ����̳� ֻ���ܷ���ʵ�����
        output :  sizeof rustClass : 16
    3.2 �鿴��ṹ 
        cd C:\Users\chenbei\Documents\Visual Studio 2019\��Ŀ�ļ�\����_����������
        cl /d1 reportSingleClassLayoutjavascriptClass "��ķ�װ�̳ж�̬.cpp"
4. ����͸���������͹���˳�� : �ȹ��������
    4.1 �����ȹ��� Ȼ�����๹��
    4.2 ���������� Ȼ��������
5. ͬ����Ա�̳д���ʽ : 
    5.1 ͬ����Ա���� : 
        5.1.1 ��������ͬ����Ա �Ȳ��������ٲ��Ҹ��� ����Ḳ�Ǹ���
        5.1.2 ���һ��Ҫ���ʸ���ͬ����Ա ��Ҫ��������  rust.baseClass::_a 
    5.2 ͬ����Ա���� :  
        5.2.1 rust.up();  �������� ���า�Ǹ��� 
        5.2.2 һ��Ҫ���ʸ���ͬ������ : rust.baseClass::up(); ���ø���
6. ͬ����̬��Ա����ʽ  : 
    6.1 ��̬��Ա���� : ����ʽ��Ǿ�̬��Ա��ͬ
    6.2 ��̬��Ա����  : ����ʽ��Ǿ�̬������ͬ
7. ��̳��﷨ : class ������ : �̳з�ʽ ����1,����2,...
    ��̳п�������������ͬ����Ա ��Ҫ���������� ʵ���в�����ʹ��
    ����������������� ����ͬ������ ��ô��Ҫ����������
8. ���μ̳� : virtual �����ָ�� ����ֻ��һ�� ��̳з�ֹ������
    �﷨ : class Sheep : virtual public Animal
9. ��̬ : �������ÿ���ָ��������� ͨ��virtual��д�����麯��
    9.1 ��̬��̬ : �������� ��������������ھ�̬��̬ ���ú�����
    9.2 ��̬��̬ : ��������麯��ʵ������ʱ��̬
    9.3. ���� : 
        9.3.1. ��̬��̬�ĺ�����ַ��� - ����׶�ȷ��������ַ
                  �������Ը�������ú�����Ȼִ�и��� �����ᱻ������д
        9.3.2. ��̬��̬�ĺ�����ַ��� - ���н׶�ȷ��������ַ
                  �ڸ���ĺ���ǰ�߼���virtual���� ��Ϊ�麯�� 
                  ��ô������ø�������ú���ʱ�Ϳ�����д������麯��
                   ע : �����Ǹ����ָ��������ú���
    9.4 �ṹʾ��ͼ : ����Animal���ֻ��һ����ͨ����ռ���ֽ�Ϊ1,����virtual�ͱ��4
         9.4.1 Animal���ڲ��ṹ : 
                  vfptr (virtual function pointer)
                     |
                     |
                    V
                    vftable(�麯����)  ���ڼ�¼�麯���ĵ�ַ 
                    ------------------------------
                  |     &Animal  :: speak       |     (������麯����û�з����ı�)
                  |                                          |
                    ------------------------------
 ************************************************************************************
                    ������ģʽ :  cl /d1 reportSingleClassLayoutAnimal "��ķ�װ�̳ж�̬.cpp"
                    class Animal    size(8):
                        +---
                    0      | {vfptr}
                    4      | _age
                        +---
                Animal::$vftable@:
                        | &Animal_meta
                        |  0
                    0      | &Animal::speak
        
        9.4.2 Cat���ڲ��ṹ :
                  �ȼ̳�
                  vfptr (virtual function pointer)
                     |
                     |
                    V
                    vftable(�麯����)  ���ڼ�¼�麯���ĵ�ַ                               (���ຯ�����麯�������ı�)
                    ------------------------------        ������ͬ������������д              ------------------------------
                  |     &Animal  :: speak        |    ----------------------------------------->   |        &Cat  :: speak        |
                    ------------------------------         ��ô�麯����ĵ�ַ����д         ------------------------------
  ************************************************************************************
                    ������ģʽ :  cl /d1 reportSingleClassLayoutCat "��ķ�װ�̳ж�̬.cpp"
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

        9.4.3 �������ָ���������ָ���������ʱ :  ������̬
                 ------>void polymorphic(Animal& animal){ animal.speak();}
                  ------>Cat cat ;
                  ------>polymorphic(cat);
                  ------>Animal  & animal = cat ;
                  ------> animal.speak() ;
                  ------> ʵ�����ҵ�����Cat����麯����ַ  &Cat  :: speak
                  ------> ���н׶����麯����ַ�����˸ı�
                  ------> ��̬�� : ������Dog����������ȥ��������麯��ʱ�����˲�ͬ������
  
  
  */
class  baseClass
{
public:
    int _base = 110; // ���ڶ�̳�
    int _a = 100 ;
    static int _e  ; // ��̬��Ա����ֻ���ⲿ��ʼ��Ϊ���� �����ڲ�����
    void up(){cout << "ͬ������baseClass�����µ�up��������" << endl;}
    void down() { cout << "baseClass�����µ�down��������" << endl; }
    static void func() { cout << "baseClass�����µ�ͬ����̬����func()����" << endl; }
    baseClass()
    {
        cout << "-------------baseClass���캯������һ��-------------" << endl;
    }
    ~baseClass()
    {
        cout << "-------------baseClass������������һ��-------------" << endl;
    }
protected:
    int _b;
    void left() { cout << "baseClass�����µ�left��������" << endl; }
private:
    int _c;
    void right() { cout << "baseClass�����µ�right��������" << endl; }
};
int baseClass::_e = 60; // ֻ�������ʼ����̬���� ����ȫ����
class  baseClass1 { public: int _base = 200; };
class javaClass : public baseClass 
{
public:
    void print()
    { 
        cout << "--------------java--------------" << endl; 
        // ����Ȩ���ⲿ���ڲ������Է���
        up(); 
        down();
        // ����Ȩ��ֻ���ڲ�����
        left(); 
        // û������˽��Ȩ��
        // ����˽��Ȩ���ڲ����ⲿ�����ܷ���
        //right();
    }
};
class pythonClass : protected baseClass
{
public:
    void print() 
    {
        cout << "--------------python--------------" << endl; 
        // û�й���Ȩ��
        // ����Ȩ��ֻ���ڲ�����
        up();
        down();
        left();
        // û������˽��Ȩ��
        // ����˽��Ȩ���ڲ����ⲿ�����ܷ���
        //right();
    }
};
class cppClass : private baseClass
{
public:
    int _cpp;// ���ڶ�̳�
    void print() 
    { 
        cout << "--------------cpp--------------" << endl; 
        // û�й���Ȩ��
       // û�б���Ȩ��
        // ����˽��Ȩ��ֻ���ڲ�����
        up();
        down();
        left();
        // ����˽��Ȩ���ڲ����ⲿ�����ܷ���
        //right();
    }
};
class rustClass : public baseClass
{
public: 
    int _a = 1000; //ͬ������ ��ֵͬ
    int _d;
    static int _e;  // ͬ����̬����
    void up() { cout << "ͬ������rustClass�����µ�up��������" << endl; }// ͬ������
    static void func() { cout << "rustClass�����µ�ͬ����̬����func()����" << endl; }
    rustClass()
    {
        cout << "-------------rustClass���캯������һ��-------------" << endl;
    }
    ~rustClass() 
    {
        cout << "-------------rustClass������������һ��-------------" << endl;
    }
};
int rustClass::_e = 120;// ֻ�������ʼ����̬���� ����ȫ����
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
        cout << "----------------������˵��----------------" << endl;
    }
};
// ����virtual ��Ϊ��̳� Animal��Ϊ�����ָ��
class Sheep : virtual public Animal{};
class Camel : virtual public Animal{};
class Alpaca : public Sheep, public Camel
{};
class Cat  : public Animal
{
public:
    void speak()
    {
        cout << "----------------è����˵��----------------" << endl;
    }
};
class Dog : public Animal
{
public:
    void speak()
    {
        cout << "----------------С����˵��----------------" << endl;
    }
};
void compare_inherit_method()
{
    javaClass java;
    java.print();
    // �ⲿ���Է���up��down
    //java.down();
    //java.up(); 

    pythonClass python;
    // �ⲿ�����ܷ���
    python.print();

    cppClass cpp;
    // �ⲿ�����ܷ���
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
    cout << "ͬ����Ա������������(rust._a)_a = " <<rust._a << endl;
    cout << "ͬ����Ա�����ڸ�����(rust.baseClass::_a)_a = " << rust.baseClass::_a << endl;
}
void sameName_func_rustClass()
{
    rustClass rust;
    rust.up(); // ͬ������
    rust.baseClass::up(); // ��������ø���
}
void static_sameName_attribute_rustClass()
{
    rustClass rust;
    // 1.ͨ��������� : 
    cout << "ͨ��ʵ����������ʾ�̬��Ա " << endl;
    cout << "\tͬ����̬��Ա������������(rust._e)_e = " << rust._e << endl;
    cout << "\tͬ����̬��Ա�����ڸ�����(rust.baseClass::_e)_e = " << rust.baseClass::_e << endl;
    // 2.ͨ���������� : 
    cout << "ͨ���������ʾ�̬��Ա" << endl;
    cout << "\tͬ����̬��Ա������������(rustClass ::_e)_e = " << rustClass ::_e << endl;
    cout << "\tͬ����̬��Ա�����ڸ�����(baseClass::_e)_e = " << baseClass::_e << endl;
    cout << "\tͬ����̬��Ա����������-������(rustClass::baseClass::_e)_e = " << rustClass ::baseClass::_e << endl;
}
void static_sameName_func_rustClass()
{
    rustClass rust;
    // 1.ͨ��������ʾ�̬����
    cout << "ͨ��ʵ����������ʾ�̬���� " << endl;
    rust.func();
    rust.baseClass::func();
    // 2.ͨ���������� : 
    cout << "ͨ���������ʾ�̬����" << endl;
    rustClass::func();
    baseClass::func();
}
void multiple_Inheritance_javascriptClass()
{
    javascriptClass javascript;
    cout << "sizeof javascriptClass :" <<sizeof(javascriptClass)<< endl;
    //cout << "_base = " << javascript._base<<endl; // ��ʾ����ȷ
    cout << "����baseClass�µ�����_base = " << javascript.baseClass ::_base << endl;
    cout << "����baseClass1�µ�����_base = " << javascript.baseClass1::_base << endl;
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
    // ���μ̳� ������̳���ͬһ������ ��һ�������ּ̳�����������
    Alpaca alpaca;
    alpaca.Sheep::_age = 18; // ԭ�����ڶ�����
    alpaca.Camel::_age = 28;
    alpaca._age = 38;
    cout << alpaca._age << endl;
    cout << alpaca.Camel::_age << endl;
    cout << alpaca.Sheep::_age << endl; // ���ֻ��һ������ 38
    cout << "------------------���μ̳�ģ��-------------------"<< endl;
    alpaca.speak();
    alpaca.Sheep::speak();
    alpaca.Camel::speak();
    /*
    * �ж����� ͬһ������
    ----------------������˵��----------------
    ----------------������˵��----------------
    ----------------������˵��----------------
    */
}
// ��ַ��� �ڱ���׶�ȷ���˺����ĵ�ַ
// ���Դ˺������۴�ʲô����ִ��Animal���speak����
// ���ϣ��ִ��Cat���speak������Ҫ�����н׶ν��а�(���)
// ֻ��Ҫ��Animal��speak����ǰ�߼���virtual ���� ���麯�� ������Dog�����
// ע : �����Ǹ�������û���ָ�뺯�� �·������ú���
void polymorphic(Animal& animal){ animal.speak();}
void doSpeak()
{
    cout << "------------------��̬ģ��-------------------" << endl;
    Cat cat;
    polymorphic(cat);// -----------------è����˵��----------------
    Dog dog;
    polymorphic(dog); // ----------------С����˵��----------------
}
int class_Inheritance()
//int main()
{
    // �Ƚϲ�ͬ�̳з���
    compare_inherit_method();
    // ����ȫ���̳�
    sizeof_rustClass();// sizeof rustClass : 20
    // �����͹���˳��
    construction_rustClass();
    /* �Ƚ����
    -------------baseClass���캯������һ��-------------
    -------------rustClass���캯������һ��-------------
    -------------rustClass������������һ��-------------
    -------------baseClass������������һ��-------------
    */
    // �̳�ͬ����Ա���Դ��� _a = 100 or 1000?
    sameName_attribute_rustClass();
    /*
    ͬ����Ա������������(rust._a)_a = 1000
    ͬ����Ա�����ڸ�����(rust.baseClass::_a)_a = 100
    */
    // �̳�ͬ���������Դ���
    sameName_func_rustClass();
    // ��̬��Ա���Դ���
    static_sameName_attribute_rustClass();
    // ��̬��Ա��������
    static_sameName_func_rustClass();
    // ��̳�
    multiple_Inheritance_javascriptClass();
    // ���μ̳� 
    diamond_Inheritance();
    // ��̬ �������ÿ���ָ���������
    doSpeak(); //----------------������˵��----------------
    return 0;
}


