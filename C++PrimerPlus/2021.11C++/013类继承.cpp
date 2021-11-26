#include "类继承.h"
//Person :: Person() // 不使用默认构造
//{
//}
//Person :: Person(const std::string& name, const std::string address, int age) // 不使用有参构造
//{
//	this->_address = address;
//	this->_age = age;
//	this->_name = name;
//}
Person::Person(const std::string& name , const std::string& address, const int age)// 列表构造
	: _name(name) , _address(address) , _age(age)//列表构造的注意事项是实参必须在实现文件中指明传递给那个参数
{} 
Person :: Person(const Person & p) // 复制构造
{
	_address = p._address;
	_age = p._age;
	_name = p._name;
}
void  Person::show_person() const
{
	std::cout <<"基类："<< "name = " << _name << "   address=" << _address << "   age = " << _age << " years" << std::endl;
}
void Person::show_person_v() const
{
	std::cout << "基类：" << "name = " << _name << "   address=" << _address << "   age = " << _age << " years" << std::endl;
}


// 派生类的默认构造只能使用基类的默认构造或列表构造或有参构造
// 否则派生类使用Person()构造时不知使用列表构造还是默认构造
// 即Person()可以对应Person()也可以对应Person(const std::string& name = "none", const std::string& address = "beijing",const int age = 18);
// 还可以对应Person(const std::string& name, const std::string address, int age); 

// 推荐基类使用列表构造，因为如果使用有参构造，则基类没有了默认构造，也就是派生类也不再有默认构造

//派生类的有参构造使用了基类的默认构造
CB::CB()   // 不显示指定何种基类构造默认使用 Person() ，: Person() 加不加都可以
{
	// 基类成员以列表构造初始化
	// 派生类成员默认初始化
	_favorite_fruit = "none";
	_favorite_sport = "none";
	_has_cars = 0;
	_has_girlfriend = false;
}

//派生类的有参构造使用了基类的列表构造
CB::CB(const std::string& ff, const std::string& fs, double height, int has_cars, bool has_girlfriend,
	const std::string& name, const std::string& address, int age=18) : Person(name, address, age),_favorite_fruit(ff)
{ // 基类列表构造传参,派生类也可以使用列表法传参
	_favorite_sport = fs; // 不使用列表法传参
	_height = height;
	_has_cars = has_cars;
	_has_girlfriend = has_girlfriend;
}

// 派生类的有参构造使用了基类的复制构造
CB::CB(const std::string& ff, const std::string& fs, double height, int has_cars, bool has_girlfriend, 
	const Person& p) : Person(p),_favorite_fruit(ff) // 基类复制构造传参,派生类也可以使用列表法传参
{
	_favorite_sport = fs; // 不使用列表法传参
	_height = height;
	_has_cars = has_cars;
	_has_girlfriend = has_girlfriend;
}
void CB::show_cb() const // void CB::show_person() const是非法的,不可继承
{
	this->show_person(); // 但是可以使用
	std::cout  << "	favorite_fruit = " << _favorite_fruit << "   favorite_sport = " << _favorite_sport
		<< "   has " << _has_cars  << " cars" << "   hasgirlfriend? " << _has_girlfriend << std::endl;
	std::cout << temp << std::endl; // 可以访问基类protected成员
// std::cout << age << std::endl; invalid不可访问基类私有成员
}
void CB::show_person_v() const
{
	//this->show_person(); // 虚函数也可以使用
	std::cout << "派生类："<<  "favorite_fruit = " << _favorite_fruit << "   favorite_sport = " << _favorite_sport
		<< "   has " << _has_cars << " cars" << "   hasgirlfriend? " << _has_girlfriend << std::endl;
}
