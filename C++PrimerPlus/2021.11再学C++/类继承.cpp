#include "��̳�.h"
//Person :: Person() // ��ʹ��Ĭ�Ϲ���
//{
//}
//Person :: Person(const std::string& name, const std::string address, int age) // ��ʹ���вι���
//{
//	this->_address = address;
//	this->_age = age;
//	this->_name = name;
//}
Person::Person(const std::string& name , const std::string& address, const int age)// �б���
	: _name(name) , _address(address) , _age(age)//�б����ע��������ʵ�α�����ʵ���ļ���ָ�����ݸ��Ǹ�����
{} 
Person :: Person(const Person & p) // ���ƹ���
{
	_address = p._address;
	_age = p._age;
	_name = p._name;
}
void  Person::show_person() const
{
	std::cout <<"���ࣺ"<< "name = " << _name << "   address=" << _address << "   age = " << _age << " years" << std::endl;
}
void Person::show_person_v() const
{
	std::cout << "���ࣺ" << "name = " << _name << "   address=" << _address << "   age = " << _age << " years" << std::endl;
}


// �������Ĭ�Ϲ���ֻ��ʹ�û����Ĭ�Ϲ�����б�����вι���
// ����������ʹ��Person()����ʱ��֪ʹ���б��컹��Ĭ�Ϲ���
// ��Person()���Զ�ӦPerson()Ҳ���Զ�ӦPerson(const std::string& name = "none", const std::string& address = "beijing",const int age = 18);
// �����Զ�ӦPerson(const std::string& name, const std::string address, int age); 

// �Ƽ�����ʹ���б��죬��Ϊ���ʹ���вι��죬�����û����Ĭ�Ϲ��죬Ҳ����������Ҳ������Ĭ�Ϲ���

//��������вι���ʹ���˻����Ĭ�Ϲ���
CB::CB()   // ����ʾָ�����ֻ��๹��Ĭ��ʹ�� Person() ��: Person() �Ӳ��Ӷ�����
{
	// �����Ա���б����ʼ��
	// �������ԱĬ�ϳ�ʼ��
	_favorite_fruit = "none";
	_favorite_sport = "none";
	_has_cars = 0;
	_has_girlfriend = false;
}

//��������вι���ʹ���˻�����б���
CB::CB(const std::string& ff, const std::string& fs, double height, int has_cars, bool has_girlfriend,
	const std::string& name, const std::string& address, int age=18) : Person(name, address, age),_favorite_fruit(ff)
{ // �����б��촫��,������Ҳ����ʹ���б�����
	_favorite_sport = fs; // ��ʹ���б�����
	_height = height;
	_has_cars = has_cars;
	_has_girlfriend = has_girlfriend;
}

// ��������вι���ʹ���˻���ĸ��ƹ���
CB::CB(const std::string& ff, const std::string& fs, double height, int has_cars, bool has_girlfriend, 
	const Person& p) : Person(p),_favorite_fruit(ff) // ���ิ�ƹ��촫��,������Ҳ����ʹ���б�����
{
	_favorite_sport = fs; // ��ʹ���б�����
	_height = height;
	_has_cars = has_cars;
	_has_girlfriend = has_girlfriend;
}
void CB::show_cb() const // void CB::show_person() const�ǷǷ���,���ɼ̳�
{
	this->show_person(); // ���ǿ���ʹ��
	std::cout  << "	favorite_fruit = " << _favorite_fruit << "   favorite_sport = " << _favorite_sport
		<< "   has " << _has_cars  << " cars" << "   hasgirlfriend? " << _has_girlfriend << std::endl;
	std::cout << temp << std::endl; // ���Է��ʻ���protected��Ա
// std::cout << age << std::endl; invalid���ɷ��ʻ���˽�г�Ա
}
void CB::show_person_v() const
{
	//this->show_person(); // �麯��Ҳ����ʹ��
	std::cout << "�����ࣺ"<<  "favorite_fruit = " << _favorite_fruit << "   favorite_sport = " << _favorite_sport
		<< "   has " << _has_cars << " cars" << "   hasgirlfriend? " << _has_girlfriend << std::endl;
}
