#include <iostream>
using namespace std;
/*
 ����ģ�����ģ��
 1.����ģ�� ������һ��ͨ�ú�������������ֵ���ͺ��β����Ϳ��Բ�����ָ��
   �﷨�� template<typename T>
 2. ģ�����Ҫȷ����T���������Ͳſ���ʹ��
	2.1�Զ������Ƶ� 
	2.2 ��ʽָ������
 3. ��ͨ���������Ƿ����Զ�����ת��(��ʽ����ת��)
	����ģ�����ʱ�����Զ������Ƶ����ᷢ����ʽ����ת��
	����������ʾָ�����ͷ�ʽ���Է�����ʽ����ת��
4. ��ͨ�����ͺ���ģ����ù���
	4.1 ��ͨ�������ȵ��ã�myAdd(a, b)
	4.2 ����ͨ����ģ������б�ǿ�Ƶ��ú���ģ�壺myAdd<>(a, b) 
	4.3 ����ģ��Ҳ��������  �� int myAdd(T a, T b,T c) �� int myAdd(T a, T b)
	4.4 ����ģ����Բ������õ�ƥ�� ������ʹ�ú���ģ��
5. ģ��ľ�����
	���縳ֵ���Ƚϣ������Զ�������������޷�ͨ�� ��Ҫ���廯������ʵ��
	����������������⻹����ʹ��template<> bool myCompare(Person &p1,Person &p2)ģ����廯
	*/
// ģ��ľ�����
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
//���廯Person�İ汾ʵ�ִ��� ���廯���ȵ���
// Ҳ����˵��myCompare��������Person������������(���ȵ���)
template<> bool myCompare(Person& a, Person& b)
{
	if (a._age == b._age && a._name == b._name)
	{
		cout << "���" << endl;
		return true;
	}
	else
	{
		cout << "�����" << endl;
		return false;
	}
}
void test_0005()
{
	Person p1("tom", 10);
	Person p2("tom", 10);
	// 1.���������
	// 2. ���廯Person�İ汾ʵ�ִ��� ���廯���ȵ���
	bool  T = myCompare(p1, p2);// ����ִ�о��廯�İ汾
}
// ��ͨ��������
int myAdd(int a, int b)
{
	cout << "��ͨ����" << endl;
	return a + b;
}
// ����ģ�����
template <class T>
T myAdd2(T a, T b) //û�е�ַ����&
{
	return a + b;//����ֵҲ��T���͵�
}

// ����ģ������ͨ�������� ���ȵ�����ͨ����
template<class T>
int myAdd(T a, T b)
{
	cout << "����ģ��" << endl;
	return a + b;
}
// ����ģ��Ҳ��������
template<class T>
int myAdd(T a, T b,T c)
{
	cout << "��������" << endl;
	return a + b+c;
}

void test_0004()
{
	int a = 10; int b = 20;
	cout << myAdd(a, b) << endl;// ���ȵ�����ͨ���� �����ͨ����û��ʵ�ֻᱨ��
	cout<<myAdd<>(a, b) << endl;// ��ģ������б� ǿ�Ƶ��ú���ģ��
	cout << myAdd(10, 20, 30) << endl;//  ����ģ��Ҳ��������
	cout << myAdd('a', 'b') << endl; // // ����ģ����Բ������õ�ƥ�� ������ʹ�ú���ģ��
}
void test_0003()
{
	
	int a = 10; int b = 20;
	char c='c';//ASCII�� 'a'=97
	// ��ͨ��������
	cout << myAdd(a,b) << endl;
	cout << myAdd(a, c) << endl;//�Զ���������ʽת�� �ַ��ͱ�Ϊ����
	
	// ����ģ�����
	// 1.�Զ������Ƶ�
	cout << myAdd2(a,b) <<endl; // ��������һ�µĿ���
	//�����Զ������Ƶ����ᷢ����ʽ����ת��
	//cout << myAdd2(a, c) << endl;// �������Ͳ�һ�²�����
	
	//2. ��ʾ����
	// ��ʾָ�����ͷ�ʽ���Է�����ʽ����ת��
	cout << myAdd2<int>(a, c) << endl;

}

template<typename T>//template <class T>����һ��
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
// ���������ú���ģ���װһ������ĺ��� �Բ�ͬ�������������������
// (ѡ������)�����򡢲���char��int���� 
template<class T>
void mySort(T arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		int max = i;// �趨���ֵ�±�
		for (int j = i + 1; j < len; j++)
		{
			if (arr[max] < arr[j])//�϶������ֵ�ȱ�����Ԫ��С ��������ֵ�±�
			{
				max = j;
			}
		}
		if (max != i) //����϶�����ֵλ�úͿ�ʼ������򽻻�λ��
		{
			// ���ý�������ģ��
			mySwap(arr[max], arr[i]); //�����±��ѽ��Ԫ��
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
	// 1.�Զ������Ƶ�
	mySwap(a, b);
	cout << a<<"\t"<<b << endl;
	//2.��ʽָ������
	mySwap<int>(a, b);
	cout << a << "\t" << b << endl;
	// 3.T����ȷ����������
	func<int>();
}
void test_0002()
{
	char charArr[] = "badcfe";
	int intArr[] = {23,43,12,56,1,3,0};
	int num = sizeof(charArr) / sizeof(char);
	mySort(charArr,num);//���ý���ģ��
	mySort(intArr, sizeof(intArr) / sizeof(int));
	printArray(charArr, num);//���ô�ӡ����ģ��
	printArray(intArr, sizeof(intArr) / sizeof(int));
}
int func_template()
//int main() 
{
	test_0001();
	test_0002();
	test_0003();
	//����ģ������ ���ȵ�����ͨ����
	test_0004();
	// ���廯ģ�庯�� ���ȵ���
	test_0005();
	return 0;
}