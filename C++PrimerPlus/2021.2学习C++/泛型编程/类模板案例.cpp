#include "_template.h"
#include "MyArray.hpp"
/*
<1>����һ��ͨ�õ�������
1. ���Զ������������ͺ��Զ����������ͽ��д洢
2. �����������ݴ洢������
3. ���캯�����Դ������������
4. �ṩ��Ӧ�Ŀ������캯���Լ�operator= ��ֹǳ��������
5. �ṩβ�巨��βɾ���������е��������Ӻ�ɾ��
6. ����ͨ��С�귽ʽ����������Ԫ��
7. ���Ի�ȡ�����е�ǰԪ�ظ���������
<2>���ģ����Ա� �� 
	����һ���������飺
		int * p  = int arr[5] ;
	����ģ�����ǣ�
		T * p  = T arr[5] ;
<3> class MyArray
{
private:
		// ���� T * pAddress ;
		// ���� _Capacity
		// ��С  _Size
public:
		// ���캯��(����)
		// ��������
		// operator=  ���ǳ��������
		// �����ͷŶ����ڴ�
		// �����±��������Ԫ�� ��
		// β�巨��βɾ��
		// ��ȡ��������
		// ��ȡ�����С
}
*/
void test_0014()
{
	myArray<int> arr(18); // �вι��������
	myArray<int> arr1(arr);//��������
	myArray <int> arr2(20);
	arr2 = arr1; // ���������
}
void printArray(myArray<int>& arr) 
//����ģ��ָ�����ͣ���������   ���ô���
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
		arr.Push_Back(i); //β�巨��������
	}
	printArray(arr);
	cout<<"βɾǰ���鳤��Ϊ��"<<arr.getArraySize()<<endl;
	cout<< "βɾǰ��������Ϊ��" << arr.getCapacity()<<endl;
	arr.Pop_Back();
	cout << "βɾ�����鳤��Ϊ��" << arr.getArraySize() << endl;
	cout << "βɾ����������Ϊ��" << arr.getCapacity() << endl;
	arr[19];
}
// �����Զ�����������
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
		cout <<"Person�������͵�����Ϊ��"<<arr[i]._name<< endl;
		cout << "Person�������͵�����Ϊ��" << arr[i]._age << endl;
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
	cout << "βɾǰ���鳤��Ϊ��" << arr.getArraySize() << endl;
	cout << "βɾǰ��������Ϊ��" << arr.getCapacity() << endl;
	arr.Pop_Back();
	cout << "βɾ�����鳤��Ϊ��" << arr.getArraySize() << endl;
	cout << "βɾ����������Ϊ��" << arr.getCapacity() << endl;
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