#include <vector> 
#include <algorithm>
#include <iostream>
using namespace std;
 // 1.vector ����Ԫ��
void myPrint(int  val)
{
    cout << val << endl;
}
void test_0017()
{
    vector<int>  v; // ģ������
    // ������������
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    // ��������������
    // ��ʼ������ ָ��������һ��Ԫ��
    vector<int> ::iterator itBegin = v.begin();
    // ���������� ָ���������һ��Ԫ�ص���һλ��
    vector<int> ::iterator itEnd = v.end();
    // ��һ�ַ��ʷ�ʽ�����԰ѵ��������Ϊָ��
    while (itBegin != itEnd)
    {
        cout << *itBegin << endl;
        itBegin++;
    }
    // �ڶ��ֱ�����ʽ
    for (vector<int> ::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << endl;
    }
    // �����ֱ�����ʽ������STL�ṩ�ı����㷨
    for_each(v.begin() , v.end() , myPrint);
}
// 2. vector ����Զ�����������
class Person
{
public:
    string _name;
    int _age;
    Person(string name, int age)
    {
        this->_age = age;
        this->_name = name;
    }
};
void test_0018()
{
    vector<Person>  v;
    Person p1("a", 10);
    Person p2("b", 20);
    Person p3("c", 30);
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    for (vector<Person> ::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << "����Զ������ݵ�������" << (*it)._name << endl;// �����÷���
        cout << "����Զ������ݵ����䣺" << it->_age <<endl; // ָ�����
    }
}
// 3. vector ����Զ����������͵�ָ��
void test_0019() 
{
    vector<Person *>  v;
    Person p1("a", 10);
    Person p2("b", 20);
    Person p3("c", 30);
    v.push_back(&p1);
    v.push_back(&p2);
    v.push_back(&p3);
    for (vector<Person*> ::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << "����Զ�������ָ���������" <<(*it)->_name<< endl;// �����÷���
        cout << "����Զ�������ָ������䣺" << (*it)->_age << endl; // ָ�����
    }

};
// 3. vector Ƕ��vector ��Ϊ��ά����
void test_0020()
{
    vector<vector<int>>  v; // �������±ߵ�С����
    vector<int> v1;
    vector<int> v2;
    vector<int> v3;
    // һ���Ը�С������ֵ
    for (int i = 0; i < 3; i++)
    {
        v1.push_back(i + 1);
        v2.push_back(i + 2);
        v3.push_back(i + 3);;
    }
    // ��С�������뵽������
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);
    // ����������
    for (vector < vector<int>> ::iterator it = v.begin(); it != v.end(); it++)
    {
        for (vector<int> ::iterator it1 = (*it).begin(); it1 != (*it).end(); it1++)
        {
            cout << (*it1) << endl;
        }

    }

}
int vector_preview()
//int main()
{
    test_0017();
    test_0018();
    test_0019();
    test_0020();
    return 0;
}
