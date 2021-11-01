#include <iostream>
using namespace std;
/*
 函数模板和类模板
 1.函数模板 ：建立一个通用函数，函数返回值类型和形参类型可以不具体指定
   语法： template<typename T>
 2. 模板必须要确定出T的数据类型才可以使用
	2.1自动类型推导 
	2.2 显式指定类型
 3. 普通函数调用是发生自动类型转换(隐式类型转换)
	函数模板调用时利用自动类型推导不会发生隐式类型转换
	但是利用显示指定类型方式可以发生隐式类型转换
4. 普通函数和函数模板调用规则
	4.1 普通函数优先调用：myAdd(a, b)
	4.2 可以通过空模板参数列表强制调用函数模板：myAdd<>(a, b) 
	4.3 函数模板也可以重载  ： int myAdd(T a, T b,T c) 和 int myAdd(T a, T b)
	4.4 函数模板可以产生更好的匹配 则优先使用函数模板
5. 模板的局限性
	例如赋值、比较，对于自定义的数据类型无法通用 需要具体化方特殊实现
	除了运算符重载以外还可以使用template<> bool myCompare(Person &p1,Person &p2)模板具体化
	*/
// 模板的局限性
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
template <class T>
bool myCompare(T &a , T &b)
{
	if (a == b)
	{
		return true;
	}
	else
	{  
		return false;
	}
}
//具体化Person的版本实现代码 具体化优先调用
// 也就是说明myCompare函数遇到Person数据类型做法(优先调用)
template<> bool myCompare(Person& a, Person& b)
{
	if (a._age == b._age && a._name == b._name)
	{
		cout << "相等" << endl;
		return true;
	}
	else
	{
		cout << "不相等" << endl;
		return false;
	}
}
void test_0005()
{
	Person p1("tom", 10);
	Person p2("tom", 10);
	// 1.运算符重载
	// 2. 具体化Person的版本实现代码 具体化优先调用
	bool  T = myCompare(p1, p2);// 优先执行具体化的版本
}
// 普通函数调用
int myAdd(int a, int b)
{
	cout << "普通函数" << endl;
	return a + b;
}
// 函数模板调用
template <class T>
T myAdd2(T a, T b) //没有地址传递&
{
	return a + b;//返回值也是T类型的
}

// 函数模板与普通函数重名 优先调用普通函数
template<class T>
int myAdd(T a, T b)
{
	cout << "函数模板" << endl;
	return a + b;
}
// 函数模板也可以重载
template<class T>
int myAdd(T a, T b,T c)
{
	cout << "函数重载" << endl;
	return a + b+c;
}

void test_0004()
{
	int a = 10; int b = 20;
	cout << myAdd(a, b) << endl;// 优先调用普通函数 如果普通函数没有实现会报错
	cout<<myAdd<>(a, b) << endl;// 空模板参数列表 强制调用函数模板
	cout << myAdd(10, 20, 30) << endl;//  函数模板也可以重载
	cout << myAdd('a', 'b') << endl; // // 函数模板可以产生更好的匹配 则优先使用函数模板
}
void test_0003()
{
	
	int a = 10; int b = 20;
	char c='c';//ASCII码 'a'=97
	// 普通函数调用
	cout << myAdd(a,b) << endl;
	cout << myAdd(a, c) << endl;//自动发生了隐式转换 字符型变为整型
	
	// 函数模板调用
	// 1.自动类型推导
	cout << myAdd2(a,b) <<endl; // 两个类型一致的可以
	//利用自动类型推导不会发生隐式类型转换
	//cout << myAdd2(a, c) << endl;// 两个类型不一致不可以
	
	//2. 显示类型
	// 显示指定类型方式可以发生隐式类型转换
	cout << myAdd2<int>(a, c) << endl;

}

template<typename T>//template <class T>基本一致
void mySwap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}
template <class T>
void func()
{
	cout << "------------"<<endl;
}
// 案例：利用函数模板封装一个排序的函数 对不同数据类型数组进行排序
// (选择排序)、降序、测试char和int数组 
template<class T>
void mySort(T arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		int max = i;// 设定最大值下标
		for (int j = i + 1; j < len; j++)
		{
			if (arr[max] < arr[j])//认定的最大值比遍历的元素小 则更新最大值下标
			{
				max = j;
			}
		}
		if (max != i) //如果认定的最值位置和开始不相等则交换位置
		{
			// 调用交换数组模板
			mySwap(arr[max], arr[i]); //交换下标对呀的元素
		}
	}
}
template<class T>
void printArray(T arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << arr[i]<< endl;
	}

}
void test_0001()
{
	int a = 1;
	int b = 2;
	// 1.自动类型推导
	mySwap(a, b);
	cout << a<<"\t"<<b << endl;
	//2.显式指定类型
	mySwap<int>(a, b);
	cout << a << "\t" << b << endl;
	// 3.T必须确定数据类型
	func<int>();
}
void test_0002()
{
	char charArr[] = "badcfe";
	int intArr[] = {23,43,12,56,1,3,0};
	int num = sizeof(charArr) / sizeof(char);
	mySort(charArr,num);//调用交换模板
	mySort(intArr, sizeof(intArr) / sizeof(int));
	printArray(charArr, num);//调用打印数组模板
	printArray(intArr, sizeof(intArr) / sizeof(int));
}
int func_template()
//int main() 
{
	test_0001();
	test_0002();
	test_0003();
	//函数模板重载 优先调用普通函数
	test_0004();
	// 具体化模板函数 优先调用
	test_0005();
	return 0;
}