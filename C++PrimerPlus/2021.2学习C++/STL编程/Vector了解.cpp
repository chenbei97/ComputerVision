#include <vector> 
#include <algorithm>
#include <iostream>
using namespace std;
 // 1.vector 访问元素
void myPrint(int  val)
{
    cout << val << endl;
}
void test_0017()
{
    vector<int>  v; // 模板类型
    // 容器插入数据
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    // 迭代器访问数据
    // 起始迭代器 指向容器第一个元素
    vector<int> ::iterator itBegin = v.begin();
    // 结束迭代器 指向容器最后一个元素的下一位置
    vector<int> ::iterator itEnd = v.end();
    // 第一种访问方式：可以把迭代器理解为指针
    while (itBegin != itEnd)
    {
        cout << *itBegin << endl;
        itBegin++;
    }
    // 第二种遍历方式
    for (vector<int> ::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << endl;
    }
    // 第三种遍历方式：利用STL提供的遍历算法
    for_each(v.begin() , v.end() , myPrint);
}
// 2. vector 存放自定义数据类型
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
        cout << "存放自定义数据的姓名：" << (*it)._name << endl;// 解引用访问
        cout << "存放自定义数据的年龄：" << it->_age <<endl; // 指针访问
    }
}
// 3. vector 存放自定义数据类型的指针
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
        cout << "存放自定义数据指针的姓名：" <<(*it)->_name<< endl;// 解引用访问
        cout << "存放自定义数据指针的年龄：" << (*it)->_age << endl; // 指针访问
    }

};
// 3. vector 嵌套vector 成为二维数组
void test_0020()
{
    vector<vector<int>>  v; // 大容器下边的小容器
    vector<int> v1;
    vector<int> v2;
    vector<int> v3;
    // 一次性给小容器赋值
    for (int i = 0; i < 3; i++)
    {
        v1.push_back(i + 1);
        v2.push_back(i + 2);
        v3.push_back(i + 3);;
    }
    // 将小容器插入到大容器
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);
    // 遍历大容器
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
