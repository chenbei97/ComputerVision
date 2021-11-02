#include "类继承.h"
void func_q(Person& q) { q.show_person_v(); };
void func_p(Person* p) { p->show_person_v(); };
void func_v(Person v) { v.show_person_v(); };
void Study_Class_inheritance() // 此函数要单独放在一个文件否则会引发异常
{
	Person p0(); // valid but meanless
	// p0().show_person(); invalid
	Person p1; // 默认构造,不能使用隐式的Person p1构造
	p1.show_person();
	Person p2("xixi","chaoyang",27); // 列表构造
	p2.show_person();
	CB cb0(); // valid but meanless
	// cb0().show_cb(); invalid
	
	CB cb1;// 默认构造,不能使用隐式的CB cb1构造
	CB cb2("banana", "basketball", 1.80, 0, true, "chenbei", "shunyi", 18);// 列表构造&有参构造
	CB cb3("apple", "football", 1.85, 1, true, cb2); // 复制构造

	std :: cout << "cb1：默认构造" << std :: endl;
	std :: cout << "	"  ;
	cb1.show_cb();// 内部使用了show_person()函数

	std::cout << "cb2：" << std::endl;
	std::cout << "	"  ;
	cb2.show_cb();// 内部使用了show_person()函数

	std::cout << "cb3：" << std::endl;
	std::cout << "	"  ;
	cb3.show_cb();// 内部使用了show_person()函数

	Person& qp1 = p1; // 基类对象的引用
	Person* pp2 = &p2;// 基类对象的指针
	qp1 = cb2; // 基类对象的引用可以指向派生类对象
	pp2 = &cb3;// 基类对象的指针可以指向派生类对象
	qp1.show_person(); // valid 
	// qp1.show_person(); invalid 但是指向不意味着有派生类的方法
	pp2->show_person(); // valid
	// pp2->show_cb(); invalid 但是指向不意味着有派生类的方法

	CB &qcb3  = cb3;// 派生类对象的引用
	CB* pcb3 = &cb3;// 派生类对象的指针
	// qcb2 = p1; 不能把基类的对象赋给派生类的引用
	// qvb2 = qp1;也不能把基类的引用赋给派生类的引用
	// pcb3 = &p2; 不能把基类的对象地址赋给派生类的指针
	// pcb3 = pp2; 也不能把基类的指针赋给派生类的指针

	// 有无virtual的区别
	std::cout << "虚函数的区别：" << std::endl;
	Person& qp2 = p2; // 指向基类对象的基类引用
	Person& qcb2 = cb2; // 指向派生类对象的基类引用
	qp2.show_person(); // 调用的是父类的show_person
	qcb2.show_person();// 虽然是指向派生类的，但调用的还是父类的show_person
	qp2.show_person_v();// 调用的是父类的show_person_v
	qcb2.show_person_v();// 加了virtual以后，调用的是派生类的show_person_v

	pp2 = &p2;
	pcb3 = &cb3;
	pp2->show_person();
	pcb3->show_person();
	pp2->show_person_v();
	pcb3->show_person_v();
	// 结论是：没有使用virtual将依据引用或指针类型选择父类或子类的方法
	// 使用virtual后将依据指向的引用或指针类型选择父类或子类的方法

	std::cout << std::endl;
	// 函数中定义处理基类的引用、指针和实例3种情况
	// 传入函数的实际参数为基类或者派生类
	func_q(p2); // 基类引用传入基类实例->调用基类方法
	func_q(cb2);// 基类引用传入派生实例->调用派生类方法
	func_p(&p2);// 基类指针传入基类实例->调用基类方法
	func_p(&cb2);// 基类指针传入派生实例->调用派生类方法
	func_v(p2);// 基类实例传入基类实例->调用基类方法
	func_v(cb2);// 基类实例传入派生类实例->调用基类方法
}