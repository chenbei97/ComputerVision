#include "all.h"
void printVector1(vector<int>& v) // ��������
{
	for (vector<int> ::iterator it = v.begin(); it != v.end(); it++) // front��back��Ӧ,begin��end��Ӧ
	{
		if (it != v.end() - 1)
			cout << (*it) << ", "; // it��ָ��
		else
			cout << (*it)<<endl;
	}
}
void printVector2(vector<int>& v)
{
	vector<int> ::iterator itBegin = v.begin();
	vector<int> ::iterator itEnd = v.end();
	while (itBegin != itEnd)
	{
		cout << *itBegin << endl;
		itBegin++;
	}
}
void printVector3(int  val) // ʹ�ú���
{
	cout << val << endl;
}
class printVector4 // ʹ��������()��Ϊ��������
{
public:
	void operator()(int  val)
	{
		cout << val << endl;
	}
};
void Study_STL_String()
{
	cout << "Study_STL_String()��" << endl;
	const char* c = "cb";
	string s1() ,s2 , s3(c) ,s4(s3); // ��ͬ�Ĺ��췽ʽ
	string s5 = s4 + "great";// ���������
	s5.append("!"), s5.assign("hello c++"); // һЩ������ʹ��,׷�Ӻ͸���
	cout <<"	"<< s5 << endl;
}
void printDeque(const deque<int>& d) // �������deque�������͵����ô��� ���Ǵ���������
{
	for (deque<int> ::const_iterator it = d.begin(); it != d.end(); it++)
	{
		// const ���Է�ֹ���ʱ��д����
		// * it =100;
		cout << (*it) << " ";
	}
	cout << endl;
}
void Study_STL_Vector()
{
	vector<int> v1, v2(v1.begin(), v1.end()), v3(10, 100), v4(v3), v5 = v1;// ��ͬ�Ĺ��췽ʽ

	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i * i); // һЩ����ʵ�����������Ԫ�أ�����pop_backɾ��Ԫ��
	}
	cout <<"v1.empty()="<<v1.empty() <<" v1.capacity()="<< v1.capacity() 
		<< " v1.size()="<<v1.size() <<" v1.front()="<< v1.front() << " v1.back()="<<v1.back()<<endl;// ��������ʵ������
	printVector1(v1);
	v1.erase(v1.begin(),v1.end()-1); // ����ָ����������Χ
	printVector2(v1);
	// �����ֱ�����ʽ������STL�ṩ�ı����㷨
	for_each(v1.begin(), v1.end(), printVector3);
	for_each(v1.begin(), v1.end(), printVector4());
}
void Study_STL_Deque()
{
	deque<int> d1;
	for (int i = 0; i < 5; i++)
	{
		d1.push_back(-i);
	}
	printDeque(d1);
	// ����������vector����
}
void Study_STL()
{
	Study_STL_String();
	Study_STL_Vector();
	Study_STL_Deque();
}