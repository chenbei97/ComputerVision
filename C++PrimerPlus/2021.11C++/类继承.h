#pragma once
#include <string>
#include <iostream>
class Person // 基类
{
	std :: string _name  ;
	int _age;
	std::string _address;
public:
	// Person(const std::string& name, const std::string address, int age); // : 不使用有参构造,会导致派生类没有默认构造
	//Person(); // 不使用默认构造
	Person(const std::string& name = "none", const std::string& address = "beijing",const int age = 18); // 列表构造
	// 列表构造的注意事项是实参必须在实现文件中指明传递给那个参数
	Person(const Person& p);// 复制构造
	void show_person() const;// 不改变自身
	virtual void show_person_v() const;
protected:
	int temp = 10;
};

class CB : public Person  // 派生类
{
	std :: string _favorite_fruit;
	std :: string _favorite_sport;
	double _height;
	int _has_cars;
	bool _has_girlfriend;
	public :
		CB();
		CB(const std::string& ff, const std::string& fs, double height, int has_cars, bool has_girlfriend,
			const std::string& name, const std::string& address, int age);
		CB(const std::string& ff, const std::string& fs, double height, int has_cars, bool has_girlfriend, const Person& p);
		void show_cb() const; // 使用另一个方法
		virtual void show_person_v() const; // 使用virtul可以重写函数
};
