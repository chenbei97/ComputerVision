#include <iostream>
using namespace std;
#include "_template.h"
/*
1. 类模板作用： 建立通用类，类中成员、数据类型都不指定，用一个虚拟类型代表
2. 语法： template<typename T> 类
3. 类模板和函数模板的区别：
	3.1 类模板没有自动推导类型
	3.2 类模板参数列表可以有默认参数
4. 类模板成员函数创建时机
	普通类成员函数一开始就可以创建 类模板成员函数在调用时才创建
5. 类模板作为函数参数 ： 类模板实例化的对象 像函数传参的方式
	5.1 指定传入的类型 - 直接显示对象的数据类型(最常用 这样可以避免与template函数模板混淆)
	void printPer2(Per<int,string>& p){};
	5.2 参数模板化 - 将对象的参数变为模板进行传递
	template <class T1 , class T2>
	void printPer2(Per<T1,T2>& p){};
	5.3 整个类模板化 - 将这个对象类型 模板化进行传递
	template <class T>
	void printPer3(T &p){};
6. 类模板与继承
	6.1 子类继承的父类是一个类模板时 子类声明时要指出父类T的类型
	class son1 : public base<int> // base可以指定为int类型
	6.2 不指定 编译器无法给子类分配内存
	6.3 若想灵活指定父类T的类型，子类也需要变为类模板
	template <class T1, class T2>
	class son2 : public base<T1> // base可以指定为T1类型用于定义来自父类的属性 T2用于子类模板自己属性
7. 类模板成员函数类外实现：
	 7.1 类模板的构造函数的类外实现
	 Car<T1,T2>::Car(T1 name, T2 age){};
	 7.2 类模板的普通成员函数的类外实现
	 void Car<T1,T2>::showPerson(){};
*/
template<class NameType , class AgeType = int>//默认参数
class Person
{
public:
	Person(NameType name, AgeType age )
	{
		this->_age = age;
		this->_name = name;
	}
	NameType _name;
	AgeType _age; // _age是AgeType类型 但是这个类型也未指定
	void showPerson()
	{
		cout << "姓名：" <<_name<< endl;
		cout << "年龄：" << _age << endl;
	}
};
void test_0006()
{
	// Person p1("chenbei", 18); // 没有自动类型推导
	Person<string, int> p1("chenbei",18);//必须显式指定类型
	Person<string>p2("cb",20); // 可以不显式指定int默认参数
	p1.showPerson();
	p2.showPerson();
}
class Person1
{
public:
	void showPerson1()
	{
		cout << "Person1调用" << endl;
	}
};
class Person2
{
public:
	void showPerson2()
	{
		cout << "Person2调用" << endl;
	}
};
template<class T>
class myClass
{
public:
	T obj;
	// 类模板中的成员函数
	void fun1()
	{
		obj.showPerson1();
	}
	void fun2()
	{
		obj.showPerson2();
	}
};
void test_0007()
{
	myClass<Person1>  m1;
	m1.fun1();//myClass调用时确定为Person1类型发现能执行
	//m1.fun2(); //Person2类型不能执行

}
// 类模板作为函数参数的传递方式
template <class T1 ,class T2>
class Per
{
public:
	T1 _age;
	T2 _name;
	Per(T2 name, T1 age)
	{
		this->_age = age;
		this->_name = name;
	}
	void showPerson()
	{
		cout << "姓名：" << _name << endl;
		cout << "年龄：" << _age << endl;
	}

};
//	5.1 指定传入的类型 - 直接显示对象的数据类型
void printPer1(Per<int, string> &p)
{
	p.showPerson(); //传入的是指定类型的类模板的地址 该类型的类可以调用该方法
}
//5.2 参数模板化 - 将对象的参数变为模板进行传递
template <class T1 , class T2>
void printPer2(Per<T1,T2>& p)
{
	p.showPerson();//类传入的时候不指定具体的类型
	cout << "T1的数据类型为：" <<typeid(T1).name()<< endl;// int
	cout << "T2的数据类型为：" << typeid(T2).name() << endl; // string
}
//5.3 整个类模板化 - 将这个对象类型 模板化进行传递
template <class T>
void printPer3(T & p)
{
	p.showPerson();
	cout << "T的数据类型为：" << typeid(T).name() << endl;//class Per
}
void test_0008()
{
	//	5.1 指定传入的类型 - 直接显示对象的数据类型
	Per<int, string> p("chenebei",18);
	printPer1(p);
	//5.2 参数模板化 - 将对象的参数变为模板进行传递
	printPer2(p);
	//5.3 整个类模板化 - 将这个对象类型 模板化进行传递
	printPer3(p);
}
// 6.类模板与继承
template <class T>
class base
{
public:
	T _m;
};
// 6.1 指定类型继承
class son1 : public base<int> // base可以指定具体的类型int
{
public:
	son1(int m)
	{
		this->_m = m;
	}

};
// 6.2 灵活指定父类的T类型，则父类也必须成为模板
template <class T1, class T2>
class son2 : public base<T1> // base可以指定为T1类型
{
public:
	T2 _obj;
	son2(T1 a, T2 b)
	{
		this->_obj = b;
		this->_m = a;
	}
	void print()
	{
		cout << "T1的数据类型为：" << typeid(T1).name() << endl;// int
		cout << "T2的数据类型为：" << typeid(T2).name() << endl; // string
		cout << "姓名：" << this->_obj << endl;
		cout << "年龄：" << this->_m<< endl;
	}
};
void test_0009() 
{
	// 6.1 指定类型继承
	son1 s1(10);
	cout<<s1._m << endl;
	// 6.2 灵活指定父类的T类型，则父类也必须成为模板
	son2<int, string> s2(20, "chen");
	s2.print();
	
}
// 7. 类模板成员函数类外实现
template<class T1 , class T2>
class Car
{
public:
	T1 _name;
	T2 _age;
	Car(T1 name, T2 age);
	//{
	//	this->_age = age;
	//	this->_name = name;
	//}
	void showPerson();
	//{
	//	cout << "姓名：" << this->_name << endl;
	//	cout << "年龄：" << this->_age << endl;
	//}
};
// 7.构造函数类外实现
// 7.1类模板的构造函数的类外实现
template<class T1 ,class T2>
//Car ::Car(T1 name, T2 age); 
Car<T1,T2>::Car(T1 name, T2 age)
{
	this->_age = age;
	this->_name = name;
}
// 7.2 类模板的普通成员函数的类外实现
template<class T1, class T2>
void Car<T1, T2>::showPerson()
{
	cout << "姓名：" << this->_name << endl;
	cout << "年龄：" << this->_age << endl;
}
void test_0010()
{
	Car<string,int> car("chenbei",100);
	car.showPerson();

}
int class_template()
//int main() 
{
	//func_template();
	//test_0006();
	//test_0007();
	//test_0008();
	//test_0009();
	test_0010();
	return 0;
}