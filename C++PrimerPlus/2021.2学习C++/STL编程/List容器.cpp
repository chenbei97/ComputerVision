#include "contanter.h"
/*
<1>�б�list����
		��������ʽ�洢������������洢��Ԫ�Ϸ������Ĵ洢�ṹ
		����Ԫ�ص��߼�˳���������ָ������ʵ��
		�������ɣ�һϵ�н�����
		������ɣ�һ���Ǵ洢����Ԫ�ص�������һ���Ǵ洢��һ������ַ��ָ����
		���Զ�����λ�ý��п��ٲ����ɾ��Ԫ��
		��������Բ������ݵð������������κ���
		����ֻ��Ҫ�����㣬��һ���ڵ�ָ����ָ��ýڵ㣬�ýڵ�ָ������ָ����һ���ڵ㼴��
		ȱ���Ǳ����ٶ�������Ϊ�����ַ��������ͬʱռ�ÿռ�ܴ�
						 0x01      0x02       0x03      0x04 ...     0x0n
		������[10] ---> [20] ---> [30] ---> [40] ---> [...]
		��ַ��[0x02] ---> [0x03] ---> [0x04] ---> [...] 
		STL��������һ��˫��ѭ������
				�������������ϣ���ַ�򲻽���¼�˺�һ������ַҲ��¼��ǰһ������ַ
				��ѭ����ʾͷ����¼����һ����ַΪ�գ�β����¼����һ����ַҲΪ��
				����ѭ����������β������һ����ַ��¼�����ײ��ĵ�ַ���ײ�����һ����ַ���¼��β���ĵ�ַ
		��������˫���������ֻ֧��ǰ�ƺͺ��ƣ������������ڴ�ռ�
<3>list���캯��
		3.1 list<T> lst;
		3.2 list(beg ,end) ;
		3.3 list(n,elem) ;
		3.4 list(const list &lst) ;
<4>list��ֵ����
		4.1 list & operator=(const list &lst) ; // v2 =v1 ;
	    4.2 assign(beg,end) ; // [beg ,end) ��������
		4.3 assign(n,elem) ; // n��elem������ֵ
		4.4 swap(lst) ; // ����
<5>list��С����
		5.1 empty() ; // �ж������Ƿ�Ϊ��
		5.2 size(); // ����
		5.3 resize(int num) ; // �����䳤����Ĭ��ֵ0�����λ�� �����ɾ��
		5.4 resize(int num ,elem) ;  // �����䳤elem�����λ��,���ɾ��
<6>list�����ɾ��
		6.1 push_back(elem) ; // β������Ԫ��elem
		6.2 pop_back() ; // ɾ�����һ��Ԫ��
		6.3 push_front(elem); // ͷ������Ԫ��elem
		6.4 pop_front() ;// ɾ����һ��Ԫ��
		6.5 insert(pos ,elem) ; // ����������λ��,������ָ��λ��pos����Ԫ��ele
		6.6 insert( pos , int count , ele) ; // ����count��
		6.7 insert(pos ,beg ,end) ; // �޷���ֵ
		6.8 erase(beg ,end) ;  // ɾ����[beg,end)֮��Ԫ��
		6.9 erase(pos) ;  // ɾ��ָ���λ��Ԫ��
		6.10 clear(); // ���
		6.11 remove(elem) ; // �Ƴ����к�elemƥ���Ԫ��
<7>list���ݴ洢 (��֧��������ʣ���֧��[]��at����,����Ҫ�����м�Ԫ��ֻ֧��++��--,��֧��+1)
		7.1 front() ; // ��һ������Ԫ��
		7.2 back() ; // ���һ������Ԫ��
<8>list��ת������
		8.1 reverse() ;//��ת����
		8.2 sort() ; //��������
		ע�� ���в�֧��������ʵ������Ĳ�֧�ֱ�׼�㷨 ������ʹ�ó�Ա����L.sort()
<9>list�����������Զ�����������ͽ�������
		���Ȱ�����������Ȼ��������ͬʱ�����������
*/
// <9>list������

class Person
{
public:
	int _age;
	int _height;
	string _name;
	Person(string name, int age, int height)
	{
		this->_age = age;
		this->_height = height;
		this->_name = name;
	}
};
void printPerson(const list<Person>& lst)
{
	for (list<Person> ::const_iterator it = lst.begin(); it != lst.end(); it++)
	{
		cout << "������" << (*it)._name << "���䣺" << (*it)._age << "��ߣ�" << (*it)._height << endl;
	}
}
// ָ���������
bool comparePerson(Person &p1 , Person  &p2)
{
	// ������ͬʱ����������߽���
	if (p1._age == p2._age)
	{
		return p1._height > p2._height;
	}
	else
	{// ������������
		return p1._age < p2._age;
	}
	
}
void test_0031()
{
	list<Person> lst;
	Person p1("A",18,181);
	Person p2("B", 21, 181);
	Person p3("C", 30, 181);
	Person p4("D", 18, 178);
	Person p5("E", 19, 181);
	Person p6("F", 18, 188);
	lst.push_back(p1);
	lst.push_back(p2);
	lst.push_back(p3);
	lst.push_back(p4);
	lst.push_back(p5);
	lst.push_back(p6);
	printPerson(lst);
	cout << "�����" << endl;
	// lst.sort(); // �Զ��������������ָ������
	lst.sort(comparePerson);
	printPerson(lst);

}
bool myCompare(int v1 ,int v2)
{
	return v1 > v2; // bool���ͽ��򷵻���
}
void printlist(const list<int>  & lst)
{
	for (list<int> ::const_iterator it = lst.begin(); it != lst.end(); it++)
	{
		cout << *it << endl;
	}
}
void test_0030()
{
	//3.1 list<T> lst;
	list<int> L1;
	L1.push_back(10);
	L1.push_back(20);
	L1.push_back(30);
	//printlist(L1);
	//3.2 list(beg, end);
	list<int> L2(L1.begin(), L1.end());
	//printlist(L2);
	//3.3 list(n, elem);
	list<int> L4(10, 1000);
	//printlist(L4);
	//3.4 list(const list & lst);
	list<int> L3(L2);
	//printlist(L3);
	//6.5 insert(pos ,elem) ; // ����������λ��,������ָ��λ��pos����Ԫ��ele
	list<int> ::iterator it = L1.begin();
	L1.insert(++it, 1100);
	//printlist(L1);
	// 6.9 erase(pos);  // ɾ��ָ���λ��Ԫ��
	it = L1.begin();
	L1.erase(++it); // ����ɾ��1100
	//printlist(L1);
	// 6.11 remove(elem); // �Ƴ����к�elemƥ���Ԫ��
	L1.push_back(1000);
	L1.remove(1000);
	//printlist(L1);
	//8.1 reverse() ;//��ת����
	L1.reverse();
	//printlist(L1);
	//8.2 sort() ; //��������
	//���в�֧��������ʵ������Ĳ�֧�ֱ�׼�㷨
	//sort(L1.begin(), L1.end());
	L1.sort(); // ��Ա����֧�� 
	printlist(L1);
	//Ĭ��������Ը�Ϊ����
	L1.sort(myCompare);
	printlist(L1);
}
int list_containter()
//int main()
{
	//stack_queue_containter();
	test_0030();
	test_0031();
	return 0;
}