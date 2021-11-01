#include "_template.h"
#include "MyArray.hpp"
/*
<1>定义一个通用的数组类
1. 可以对内置数据类型和自定义数据类型进行存储
2. 将数组中数据存储到堆区
3. 构造函数可以传入数组的容量
4. 提供对应的拷贝构造函数以及operator= 防止浅拷贝问题
5. 提供尾插法和尾删法对数组中的数据增加和删除
6. 可以通过小标方式访问数组中元素
7. 可以获取数组中当前元素个数和容量
<2>与非模板类对比 ： 
	定义一个整型数组：
		int * p  = int arr[5] ;
	对于模板则是：
		T * p  = T arr[5] ;
<3> class MyArray
{
private:
		// 数组 T * pAddress ;
		// 容量 _Capacity
		// 大小  _Size
public:
		// 构造函数(容量)
		// 拷贝构造
		// operator=  解决浅拷贝问题
		// 析构释放堆区内存
		// 利用下标访问数组元素 ？
		// 尾插法、尾删法
		// 获取数组容量
		// 获取数组大小
}
*/
void test_0014()
{
	myArray<int> arr(18); // 有参构造和析构
	myArray<int> arr1(arr);//拷贝构造
	myArray <int> arr2(20);
	arr2 = arr1; // 运算符重载
}
void printArray(myArray<int>& arr) 
//数组模板指定类型：整型数组   引用传递
{
	for (int i = 0; i < arr.getArraySize(); i++)
	{
		cout << arr[i] << endl;
	}
}
void test_0015()
{
	myArray<int> arr(18);
	for (int i = 0; i < 18; i++)
	{
		arr.Push_Back(i); //尾插法插入数据
	}
	printArray(arr);
	cout<<"尾删前数组长度为："<<arr.getArraySize()<<endl;
	cout<< "尾删前数组容量为：" << arr.getCapacity()<<endl;
	arr.Pop_Back();
	cout << "尾删后数组长度为：" << arr.getArraySize() << endl;
	cout << "尾删后数组容量为：" << arr.getCapacity() << endl;
	arr[19];
}
// 测试自定义数据类型
class Person
{
public:
	string _name;
	int _age;
	Person() {};
	Person(string name, int age)
	{
		this->_age = age;
		this->_name = name;
	}
};
void prinPersontArray(myArray<Person>& arr)
{
	for (int i = 0; i < arr.getArraySize(); i++)
	{
		cout <<"Person数据类型的姓名为："<<arr[i]._name<< endl;
		cout << "Person数据类型的年龄为：" << arr[i]._age << endl;
	}
}
void test_0016()
{
	myArray<Person> arr(8);
	Person p1("cb",100);
	Person p2("ccbb", 1000);
	Person p3("cb", 200);
	Person p4("cb", 400);
	Person p5("cb", 600);
	arr.Push_Back(p1);
	arr.Push_Back(p2);
	arr.Push_Back(p3);
	arr.Push_Back(p4);
	arr.Push_Back(p5);
	prinPersontArray(arr);
	cout << "尾删前数组长度为：" << arr.getArraySize() << endl;
	cout << "尾删前数组容量为：" << arr.getCapacity() << endl;
	arr.Pop_Back();
	cout << "尾删后数组长度为：" << arr.getArraySize() << endl;
	cout << "尾删后数组容量为：" << arr.getCapacity() << endl;
	arr[5];
}
int main() 
{
	//friend_template();
	//test_0014();
	//test_0015();
	test_0016();
	return 0;
}