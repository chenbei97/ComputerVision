#include "contanter.h"
/*
<1>��������set�ص�
		����Ԫ���ڲ���ʱ�Զ�������
		����set/multiset���ڹ���ʽ�������ײ�ṹ�Ƕ�����ʵ��
<2>set���캯���͸�ֵ
		2.1 set<T> st ; // ģ��ʵ����ʵ�� ��Ĭ�Ϲ��캯��  vector<int>  v
		2.2 set(const set &st) ; // �������캯��
		2.3 set &operator = (const set &st) ;
<3>set��С�ͽ���
		3.1 empty() ; // �ж������Ƿ�Ϊ��
		3.2 swap(st);  // ����
		3.3 size(); // ����
<4>set�����ɾ��
		4.1 insertelem) ;   //��������ֻ��insert
		4.2 clear() ;
		4.3 erase(pos) ;
		4.4 erase(beg ,end) ;
		4.5 erase(elem);
<5>set���Һ�ͳ��
		5.1 find(key); // key���ڷ��ظü���Ԫ�ص����� �����ڷ���set.end()
		5.2 count(key) ; // ͳ��key���� = 0 or 1
<6>set��multiset����
		set�������������ظ�Ԫ�أ�multiset������
		set��������ʱ�᷵�ؽ�� ��ʾ�����Ƿ�ɹ�
		multiset���������� ��˿��Բ����ظ�����
<7>pairr����Ĵ���
		�ɶԳ��ֵ����ݿ������ö��鷵����������
		7.1 pair<type,type> p (value1 , value2) ;
		7.2 pair<type,type> p = make_pair (value1 , value2) ;
<8>set��������ָ���������
		setĬ���������÷º������Ըı�������� : ����()
<9>set�Զ�����������ָ���������
		


*/
void spilit_line()
{
	cout << "----------------------------�ָ���----------------------------" << endl;
};
class Person1
{
public:
	int _age;
	string _name;
	Person1(string name,int age)
	{
		
		this->_age = age;
		this->_name = name;
	}
};
class comparePerson
{
public:
	bool operator() (const Person1 & p1, const Person1 & p2) const
	{
		if (p1._age == p2._age) // ��������
		{
			return p1._name < p2._name;
		}
		else
		{
			return p1._age > p2._age;
		}
	}
};
void printSet(const set<int>& st);
class My_Compare
{
public:
	bool operator ()  (int v1, int v2) const
	{
		return v1 > v2;
	}
};
void test_0033()
{
	// 0. ����Ĭ������
	set<int> s1;
	s1.insert(10);
	s1.insert(20);
	s1.insert(30);
	printSet(s1);
	// 1.set��������ָ���������
	set<int , My_Compare> s2; // ���÷º�������
	s2.insert(10);
	s2.insert(20);
	s2.insert(30);
	// printSet(s2); ������ֱ�ӱ���
	// ����֮ǰ���ƶ��ù���
	for (set<int, My_Compare> ::iterator it = s2.begin(); it != s2.end(); it++)
	{
		cout << "�º������������" << *it << " ";
	}
	cout << endl;

	// 2.set�Զ�����������ָ���������
	Person1 p1("A", 18);
	Person1 p2("B", 21);
	Person1 p3("C", 30);
	Person1 p4("D", 18);
	Person1 p5("E", 19);
	Person1 p6("F", 18);
	// �Զ����������Ͳ���ֱ�Ӳ��� �����ƶ�����ȥ�������
	set<Person1, comparePerson>  s;
	s.insert(p1);
	s.insert(p2);
	s.insert(p3);
	s.insert(p4);
	s.insert(p5);
	s.insert(p6);
	for (set<Person1> ::const_iterator it = s.begin(); it != s.end(); it++)
	{
		cout << "������" <<(*it)._name <<" " << "���䣺"<<(*it)._age<<  endl;
	}

}
void printSet(const set<int>& st)
{
	{
		for (set<int> ::const_iterator it = st.begin(); it != st.end(); it++)
		{
			cout << (*it) << endl;
		}
	}
}
void test_0032()
{
	set<int> st;
	// ��������ֻ��insert
	st.insert(10);
	st.insert(10);
	st.insert(11);
	st.insert(12);
	printSet(st);
	set<int> s1(st);
	set<int> s2;
	s2 = s1;
	//5.1 find(key); // key���ڷ��ظü���Ԫ�ص����� �����ڷ���set.end()
	set<int> ::iterator pos = s1.find(10);
	if (pos != s1.end())
	{
		cout << "�ҵ�Ԫ��Ϊ��"<<* pos <<endl;
	}
	else
	{
		cout << "δ�ҵ�" << endl;
	}
	int num = s1.count(10);
	cout << "����Ϊ��" <<num << endl;

	//set��multiset����
	pair<set<int> ::iterator, bool> ret = s1.insert(100);
	if (ret.second)
	{
		cout << "���ݲ���ɹ�" << endl;
	}
	else
	{
		cout << "���ݲ���ʧ��" << endl;
	}
	multiset<int> s5;
	s5.insert(100);
	s5.insert(100);
	s5.insert(100);
	cout << "multiset��100�ĸ���Ϊ" <<s5.count(100)<< endl;
	//�ɶԳ��ֵ����ݿ������ö��鷵����������
	/*	7.1 pair<type, type> p(value1, value2);*/
	pair<string, int> p("tom", 18);
	cout << "������" << p.first <<"���䣺"<< p.second << endl;
	//	7.2 pair<type, type> p = make_pair(value1, value2);
	pair<string, int> p2 = make_pair("tom", 18);
	cout << "������" << p2.first << "���䣺" << p2.second << endl;
}
int set_containter()
//int main()
{
	//list_containter();
	//test_0032();
	 test_0033();
	return 0;
}