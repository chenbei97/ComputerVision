#pragma once
#include <string>
#include <iostream>
class Person // ����
{
	std :: string _name  ;
	int _age;
	std::string _address;
public:
	// Person(const std::string& name, const std::string address, int age); // : ��ʹ���вι���,�ᵼ��������û��Ĭ�Ϲ���
	//Person(); // ��ʹ��Ĭ�Ϲ���
	Person(const std::string& name = "none", const std::string& address = "beijing",const int age = 18); // �б���
	// �б����ע��������ʵ�α�����ʵ���ļ���ָ�����ݸ��Ǹ�����
	Person(const Person& p);// ���ƹ���
	void show_person() const;// ���ı�����
	virtual void show_person_v() const;
protected:
	int temp = 10;
};

class CB : public Person  // ������
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
		void show_cb() const; // ʹ����һ������
		virtual void show_person_v() const; // ʹ��virtul������д����
};
