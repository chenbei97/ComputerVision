#include "contanter.h"
/*
1. ����bool���͵ķº���Ϊν��
2. operator()����һ������ΪһԪν�ʣ���������Ϊ��Ԫν��
3. ������֮ǰ�ĺ�����������()��ͬ��������������Ĺ��캯������
*/
// 1. һԪν��
void print_weici(const vector<int>& v);
class behindfive
{
public:
	bool operator()( int val)
	{
		return val > 5;
	}

};
// 2.��Ԫν��
class two_sort
{
public:
	bool operator() (int v1 ,int v2)
	{
		return  v1 > v2;// ��Ԫν������
	}


};
void test_0037()
{
	vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(- i * 10 );
	}
	print_weici(v);
	sort(v.begin(), v.end());
	spilit_line();
	print_weici(v);
	// ���ö�Ԫ�º����ı��������
	sort(v.begin(), v.end(), two_sort());
	spilit_line();
	print_weici(v);
}
void print_weici(const vector<int> & v)
{
	for (vector<int> ::const_iterator it = v.begin(); it != v.end(); it++)
	{
		cout <<   (*it) << " ";
	}
	cout << endl;
}
void test_0036()
{
	vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	// fnd_if����Ϊ ����������Χ��ν�ʣ����ص�����
	vector<int> ::iterator pos  = find_if(v.begin(), v.end(), behindfive());
	if (pos == v.end())
	{
		cout << "δ�ҵ�"<<endl;
	}
	else
	{
		cout << "�ҵ��˴���5���ֵ�Ϊ��" <<(*pos)<< endl;
	}
}
int one_two_predicate()
//int main()
{
	// stl_func_object();
	test_0036();
	test_0037();
	return 0;
}