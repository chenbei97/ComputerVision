#pragma once
#include <iostream>
using namespace std;
template <class T>
class myArray
{
private:
	T* pAddress; // ָ���������ʵ�����ַ
	int _Capacity; // ��������
	int _Size; // �����С
public:
	myArray(int Capacity)
	{
		cout << "myArray�вι��캯�����е���--------------->" << endl;
		this->_Capacity = Capacity;
		this->_Size = 0;
		this->pAddress = new T[this->_Capacity];
	}
	myArray(const myArray& arr)
	{
		cout << "myArray������캯�����е���--------------->" << endl;
		this->_Capacity = arr._Capacity;
		this->_Size = arr._Size;
		// this->pAddress = arr.pAddress; ǳ����
		// ���
		this->pAddress= new T[arr._Capacity];
		for (int i = 0; i < this->_Size; i++)
		{
			this->pAddress[i] = arr.pAddress[i];
		}
	}
	// operator = ��ֹǳ���� ���������
	myArray& operator=(const myArray& arr)
	{
		cout << "myArray��ֵ������������е���--------------->" << endl;
	    // ���ж�ԭ�������Ƿ������� �����ͷ�
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
			cout << "myArray�����������е���--------------->" << endl;
			delete[]  pAddress;
			pAddress = NULL;
		}
	}
	// β�巨
	void Push_Back(const T& val)
	// ���������� β���Ԫ�ؿ�������������������T
	{
		if (this->_Capacity == this->_Size)
		{
			return;
		}
		this->pAddress[this->_Size] = val; //����ĩβ��������
		this->_Size++; //���������С
	}
	// βɾ��
	void Pop_Back()
	{
		// �û����ʲ������һ��Ԫ�� �߼�βɾ
		if (this->_Size == 0)
		{
			return;
		}
		this->_Size--;
	}
	// ͨ���±귽ʽ��������Ԫ�� ��������[]�����
	T & operator [](int index)
	{
		if (index > this->_Size)
		{
			cout << "��������Խ�磬�±겻�ܴ������ݳ��ȣ�" <<this-> _Size << endl;
		}
		else 
		{
			return this->pAddress[index]; // ��������������ģ��ĵ�ַ
		}
	}
	// ��ȡ��������
	int getCapacity()
	{
		return this->_Capacity;
	}
	// ��ȡ�����С
	int getArraySize()
	{
		return this->_Size;
	}
};