#pragma once
#include <iostream>
using namespace std;
template <class T>
class myArray
{
private:
	T* pAddress; // 指向堆区的真实数组地址
	int _Capacity; // 数组容量
	int _Size; // 数组大小
public:
	myArray(int Capacity)
	{
		cout << "myArray有参构造函数运行到此--------------->" << endl;
		this->_Capacity = Capacity;
		this->_Size = 0;
		this->pAddress = new T[this->_Capacity];
	}
	myArray(const myArray& arr)
	{
		cout << "myArray深拷贝构造函数运行到此--------------->" << endl;
		this->_Capacity = arr._Capacity;
		this->_Size = arr._Size;
		// this->pAddress = arr.pAddress; 浅拷贝
		// 深拷贝
		this->pAddress= new T[arr._Capacity];
		for (int i = 0; i < this->_Size; i++)
		{
			this->pAddress[i] = arr.pAddress[i];
		}
	}
	// operator = 防止浅拷贝 运算符重载
	myArray& operator=(const myArray& arr)
	{
		cout << "myArray赋值运算符重载运行到此--------------->" << endl;
	    // 先判断原来堆区是否有数据 有先释放
		if (this->pAddress != NULL)
		{
			delete[] this->pAddress;
			this->pAddress = NULL;
			this->_Size = 0;
			this->_Capacity = 0;
		}
		this->_Capacity = arr._Capacity;
		this->_Size = arr._Size;
		this->pAddress = new T[arr._Capacity];
		for (int i = 0; i < this->_Size; i++)
		{
			this->pAddress[i] = arr.pAddress[i];
		}
		return *this;
	}
	~myArray()
	{
		if (this->pAddress != NULL)
		{
			cout << "myArray析构函数运行到此--------------->" << endl;
			delete[]  pAddress;
			pAddress = NULL;
		}
	}
	// 尾插法
	void Push_Back(const T& val)
	// 纯常用引用 尾插的元素可以是任意类型所以用T
	{
		if (this->_Capacity == this->_Size)
		{
			return;
		}
		this->pAddress[this->_Size] = val; //数组末尾插入数据
		this->_Size++; //更新数组大小
	}
	// 尾删法
	void Pop_Back()
	{
		// 用户访问不到最后一个元素 逻辑尾删
		if (this->_Size == 0)
		{
			return;
		}
		this->_Size--;
	}
	// 通过下标方式访问数组元素 重载引用[]运算符
	T & operator [](int index)
	{
		if (index > this->_Size)
		{
			cout << "访问数组越界，下标不能大于数据长度：" <<this-> _Size << endl;
		}
		else 
		{
			return this->pAddress[index]; // 返回是数据类型模板的地址
		}
	}
	// 获取数据容量
	int getCapacity()
	{
		return this->_Capacity;
	}
	// 获取数组大小
	int getArraySize()
	{
		return this->_Size;
	}
};