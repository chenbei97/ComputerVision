#include "contanter.h"
/*
<1>vector�����ĸ���
	v.rend() ; // ��һ��Ԫ��λ�õ�ǰһ��
	v.begin();// ��һ��Ԫ��λ��
	v.insert(); // ����
	v.rbegin();// ���һ��Ԫ��λ��
	v.end(); // ���һ��Ԫ��λ�õĺ�һ��
	v.push_back(); // ���
	v.pop_back(); // ɾ��
	֧��������ʵĵ�����
<2>vector�����Ĺ��캯��
	2.1 vector<T> v ; // ģ��ʵ����ʵ�� ��Ĭ�Ϲ��캯��  vector<int>  v 
	2.2 vector(v.begin() , v.end()) ; // ��[ v.begin() , v.end() )����(ǰ�պ�)��Ԫ�ؿ���������
	2.3 vector(n , elem) ; // ���캯����n��elem����������
	2.4 vector(const vector &vec) ; // �������캯��
<3>vector�����ĸ�ֵ����
	3.1 vector & operator=(const vector &vec) ; // v2 =v1 ;
	3.2 assign(beg,end) ; // [beg ,end) ��������
	3.3 assign(n,elem) ; // n��elem������ֵ
<4>vector�����������ʹ�С
	4.1 empty() ; // �ж������Ƿ�Ϊ��
	4.2 capacity();  // ����
	4.3 size(); // ����
	4.4 resize(int num) ; // �����䳤����Ĭ��ֵ0�����λ�� �����ɾ��
	4.5 resize(int num ,elem) ;  // �����䳤elem�����λ��,���ɾ��
<5>vector�����Ĳ����ɾ��
	5.1 push_back(ele) ; // β������Ԫ��ele
	5.2 pop_back() ; // ɾ�����һ��Ԫ��
	5.3 insert(const_iterator pos , ele) ; // ������ָ��λ��pos����Ԫ��ele
	5.4 insert(const_iterator pos , int count , ele) ; // ����count��
	5.5 erase(const_iterator pos) ;  // ɾ��ָ���λ��Ԫ��
	5.6 erase(const_iterator start , const_iterator end) ;  // ɾ����start��end֮��Ԫ��
	5.7 clear(); // ���
<6>vector���������ݴ�ȡ
	6.1 at(int idx) ; //��������idx������
	6.2 operator[] ; // ����
	6.3 front() ; // ��һ������Ԫ��
	6.4 back() ; // ���һ������Ԫ��
<7>vector�����Ļ�������
	7.1 swap(vec) ; // ��vec�뱾���Ԫ�ػ���
	7.2 �������������ڴ�
<8>vector������Ԥ���ռ�
	8.1 ����vector��̬��չ����ʱ����չ����
	8.2 reserve(int len) ; // ����Ԥ��len��Ԫ�� ��Ԥ��λ�ò���ʼ�� Ԫ�ز��ɷ���
	8.3 ֻ�����ڴ治��ʼ��
*/
void printVector(vector<int>& v);
void test_0027()
{
	// 7.1 swap(vec) ; // ��vec�뱾���Ԫ�ػ���
	vector<int> v1;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i * i);
	}
	vector<int> v2;
	for (int i = 0; i < 10; i++)
	{
		v2.push_back(i );
	}
	v1.swap(v2);
	//printVector(v1);
	//printVector(v2);
	// 7.2 �������������ڴ�
	vector<int> v3;
	for (int i = 0; i < 100000; i++)
	{
		v3.push_back(i);
	}
	cout << "v3������Ϊ��" <<v3.capacity()<< endl;
	cout << "v3�ĳ���Ϊ��" << v3.size() << endl;
	v3.resize(3);
	cout << "v3������Ϊ��" << v3.capacity() << endl;	// ���������
	cout << "v3�ĳ���Ϊ��" << v3.size() << endl;
	vector<int>(v3).swap(v3);
	// vector<int>(v3) Ϊ�������� ָ���С���ڴ�
	// ����������v3���������� ԭ����v3ָ����С�ڴ� ������������ڴ��Զ�������
	cout << "v3������Ϊ��" << v3.capacity() << endl;	// 
	cout << "v3�ĳ���Ϊ��" << v3.size() << endl;

	// 8.2 reserve(int len); // ����Ԥ��len��Ԫ�� ��Ԥ��λ�ò���ʼ�� Ԫ�ز��ɷ���
	
	
	int num = 0; // ͳ�ƶ�̬�����ڴ�Ĵ���
	int* p = NULL;
	vector<int> v4;
	// ����reserve()Ԥ���ռ� �����÷�����̬����
	v4.reserve(100000);// ��̬�����ڴ����Ϊ��1
	for (int i = 0; i < 100000; i++)
	{
		v4.push_back(i);
		if (p != &v4[0]) // ���pָ�벻�����������׵�ַ
		{
			p = &v4[0];
			num++;// ��̬����ʱ�׵�ַ���Ǳ仯 ÿ�α仯�Ժ�+1��������ָ���һ��Ԫ���׵�ַ
		}
	}
	cout << "��̬�����ڴ����Ϊ��" << num << endl;//��̬�����ڴ����Ϊ��30
}
void printVector(vector<int>& v) // ��������
{
	for (vector<int> ::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << (*it) << endl;
	}
}
void test_0026()
{
	//2.1 vector<T> v; // ģ��ʵ����ʵ�� ��Ĭ�Ϲ��캯��  vector<int>  v 
	vector<int> v1;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i * i);
	}
	//printVector(v1);
	//2.2 vector v(v.begin(), v.end()); // ��[ v.begin() , v.end() )����(ǰ�պ�)��Ԫ�ؿ���������
	vector<int>v2(v1.begin(), v1.end());
	//printVector(v2);
	//2.3 vector(n, elem); // ���캯����n��elem����������
	vector<int> v3(10, 100);
	//printVector(v3);
	//2.4 vector(const vector & vec); // �������캯�� ָ�򴿳���������
	vector<int> v4(v3);
	//printVector(v4);
	//3.1 vector & operator=(const vector & vec); // v2 =v1 ;
	vector<int> v5 = v1;
	//printVector(v5);
	//3.2 assign(beg, end); // [beg ,end) ��������
	vector<int> v6;
	v6.assign(v1.begin(), v1.end());
	//printVector(v6);
	//3.3 assign(n, elem); // n��elem������ֵ
	vector<int> v7;
	v7.assign(5, 10); // ��ֵ��Ϊ �ϱ��ǹ�����Ϊ
	//printVector(v7);
	//4.1 empty(); // �ж������Ƿ�Ϊ��
	//cout <<v1.empty() << endl;
	//4.2 capacity();  // ����
	//cout << v1.capacity() << endl; // ��̬�����
	//4.3 size(); // ����
	//cout << v1.size()<< endl;
	//4.4 resize(int num); // �����䳤����Ĭ��ֵ�����λ�� �����ɾ��
	v1.resize(8);
	//cout << v1.capacity() << endl;  // 19
	//cout << v1.size() << endl; //15
	//printVector(v1);
	//4.5 resize(int num, elem);  // �����䳤elem�����λ��,���ɾ��
	v1.resize(15,100);
	//printVector(v1);
	//5.4 insert(const_iterator pos, int count, ele); // ����count��
	v1.insert(v1.begin(), 2, -40);
	//printVector(v1);
	//5.6 erase(const_iterator start, const_iterator end);  // ɾ����start��end֮��Ԫ��
	v1.erase(v1.begin());
	//printVector(v1);
	// 6.4 back(); // ���һ������Ԫ��
	cout << v1.back() << endl;
	

}
int vector_containter()
//int main()
{
	//string_containter();
	//test_0026();
    test_0027();
	return 0;
}