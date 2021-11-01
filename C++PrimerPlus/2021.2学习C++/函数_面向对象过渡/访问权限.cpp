#include <iostream>
using namespace std;
/*
1.public 公共权限 : 成员类可以访问 , 类外也可以访问
2.pretected 保护权限  : 类内可以访问 类外不能访问 子类可以访问父类
3.private 私有权限 : 类内可以访问 类外不能访问 子类不能访问父类
简单来说父亲的手机号其他人可以访问，儿子也可以访问
父亲的车 其他人不能访问，儿子可以访问
父亲的银行卡号 儿子也不能访问
*/
/* struct 和 class 的区别
struct默认权限为公共  class默认权限为私有
*/
class  Person
{
    string  _id = "cb"; // 在不赋予关键字时类属性默认私有 person1_id不能访问
public: 
    //外部可以访问公共权限属性
    string _PhoneNumer = "13651116327";  
protected :
    // 外部不能访问保护权限属性
    string  _Car = "benchi";  
private  :
    // 外部不能访问私有权限属性
    int _Password = 123;
/*<------------------------------------------------------------------------------------------->*/
public :
     // 外部接口设置
    // 年龄的写权限
    void setAge(int  age) 
    {
        _age = age;  //提供给外部函数设置内部的私有属性_age
    }
    // 年龄的读权限
    int getAge()
    {
        return  _age;//提供给外部函数获取内部的私有属性_age
    }
    // 情人的只读权限
    string getLover()
    {
        return _lover;
    }
    // 品牌的只写权限
    void setBrand(string brand)
    {
        _brand = brand;
    }
private :
    // 如果外部需要访问私有属性可以外部提供接口设定不同的权限去访问
    // 在python中类属性默认是可读可写的,可以通过_numer来设置不可读不可访问,只能通过类方法提供接口
    // 可读可写
    int _age = 10;
    // 只读
    string _lover = "xishi";
    // 只写
    string _brand = "huawei";
/*<------------------------------------------------------------------------------------------->*/
public :
    void  func1()
    {
        //内部也可以访问公共权限属性
        _PhoneNumer = "19801279791"; 
        cout << "内部可以访问公共权限属性_PhoneNumer(手机号) : " << _PhoneNumer <<endl;
        // 内部也可以访问保护权限属性
        _Car = "baoma"; 
        cout << "内部可以访问保护权限属性_Car(车) : " << _Car << endl;
        // 内部也可以访问私有权限属性
        _Password = 456;
        cout << "内部可以访问私有权限属性_Password(密码) : " << _Password << endl;
    }
};
int Access_Right()
//int main() 
{
    Person  person1;
    cout << "外部可以访问公共权限属性person1._PhoneNumer(手机号) : " <<person1._PhoneNumer << endl;
    cout << "外部不可以访问保护权限属性person1._Car(车)" << endl;
    cout << "外部不可以访问私有权限属性person1._Password(密码)" << endl;
    person1.func1();
    
    // 测试获取年龄的读写权限
    // 年龄的读权限
    int age = person1.getAge();
    cout << "测试获取年龄的读权限, age = " << age <<endl;
    // 年龄的写权限
    person1.setAge(20);
    cout << "测试获取年龄的写权限, age = " << person1.getAge() << endl;
    // 情人的只读权限
    string lover = person1.getLover();
    cout << "测试获取情人的只读权限, age = " << lover << endl;
    // 品牌的只写权限
    person1.setBrand("oppo");
    system("pause");
    return 0;
}