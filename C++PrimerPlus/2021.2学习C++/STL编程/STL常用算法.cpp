#include "contanter.h"
/*
<1>STL����ͷ�ļ�
		<algorithm> �漰�Ƚϡ����������ҡ����������ƺ��޸ĵ�
		<numeric>��Ҫ�Ǽ���ѧ�����ģ�庯��
		<functional> �ڽ�����
<2>STL�����㷨
		2.1 �����㷨(�����Լ�д��printvector()Ҳ����ʹ�����õ��㷨)
				2.1.1 for_each(iterator beg , iterator end , func) ; // ��������
				2.1.2 transform(iterator beg1 , iterator end1 , iterator beg2, func) ; // ������������һ������
				2.1.4 func��������ͨ����Ҳ�����Ƿº���ʵ��
		2.2 �����㷨
				2.2.1 find(beg,end,elem) // ���� ����ָ��Ԫ�ص��������߽���������
				2.2.2 findif(beg,end,func) // ���������� funcΪbool���͵ķº�������ν��
				2.2.3 adjacent_find(beg,end) // ���������ظ�Ԫ��
				2.2.4 binary_search(beg, end,value) // ���ֲ��ҷ� �鵽����true ������������������
				2.2.5 count(beg,end,value)  // ͳ�Ƹ���
				2,2,6 count_if(beg,end,func) // ������ͳ�Ƹ���
		2.3 �����㷨
				2.3.1 sort(beg,end,func)  // ����
				2.3.2 random_shuffe(beg,end) // �漴ϴ��
				2.3.3 merge(beg1,end1,beg2,end2,target.begin()) // �����������������1��2Ԫ�غϲ� �洢����һ������target
				2.3.4 reverse(beg,end,func) // ��תԪ�� func�������๹��º���Ҳ��������ͨ����
		2.4 �������滻�㷨
				2.4.1 copy(beg,end, target.begin()) // ����
				2.4.2 replace(beg,end,oldvalue,newvalue) // �滻
				2.4.3 replace_if(beg,end,func,newvalue) //ָ����Χ������������Ԫ���滻Ϊ��Ԫ��
				2.4.4 swap(containter1 containter2) // ����2��ͬ��������Ԫ��
		2.5 ���������㷨
				2.5.1 accumulate(beg,end,��ʼ�ۼ�ֵ) // ����������Ԫ���ۼӺ�
				2.5.2 fill(beg,end,value)  // �������Ԫ��
		2.6 �����㷨
				2.6.1 set_intersection(beg1,end1,beg2,end2,target,begin()) // ����
				2.6.2 set_union(beg1,end1,beg2,end2,target,begin()) // ����
				2.6.3 set_difference(beg1,end1,beg2,end2,target,begin()) // �
				*/
// ��ͨ����ʵ��
void print01(int val)
{
	cout << val <<" ";
}
// �๹�캯����Ϊ�º���ʵ��
class print02
{
public :
	void operator()(int val)
	{
		cout << val << " ";
	}
};
class Transformfunc // ����()
{
public:
	int operator ()(int v)
	{
		return v;
	}

};
void test_0039()
{
	//2.1.1 for_each(iterator beg, iterator end, func); // ��������
	vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	//ֱ�Ӻ������ʵ��
	cout <<"ֱ�Ӻ������ʵ�֣�"<< endl;
	printvector(v);
	//spilit_line();
	// ��ͨ������Ϊ��������
	cout << "��ͨ������Ϊ��������ʵ�֣�" << endl;
	for_each(v.begin(),v.end(),print01);
	// �๹�캯����Ϊ�º���
	cout << "\n�๹�캯����Ϊ��������ʵ�֣�" << endl;
	for_each(v.begin(), v.end(), print02());

	//2.1.2 transform(iterator beg1, iterator end1, iterator beg2, func); // ������������һ������
	vector<int> v1;
	v1.resize(v.size());
	// �º���
	transform(v.begin(), v.end(), v1.begin(), Transformfunc());
	cout << "\ntransform���๹�캯����Ϊ��������ʵ�֣�" << endl;
	for_each(v1.begin(), v1.end(), print02());
}
class Car
{
public:
	string _name;
	int _age;
	Car(int age, string name)
	{
		this->_age = age;
		this->_name = name;
	}
	bool operator == (const Car& p)
	{
		if (this->_age == p._age  && this->_name == p._name)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
// count _if������
class greater2
{
public:
	bool operator ()(int val)
	{
		return val > 2;
	}
};
class agegreater18
{
public:
	bool operator()(const Car& p)
	{
		return p._age > 18;
	}

};
void test_0040()
{
	//2.2.1 find() // ���� ����ָ��Ԫ�ص��������߽���������
	// ����������������
	vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	vector<int> :: iterator pos =find(v.begin(), v.end(), 5);
	// �����Զ�����������
	vector<Car> v1;
	Car p1(18, "a");
	Car p2(20, "b");
	v1.push_back(p1);
	v1.push_back(p2);
	vector<Car> ::iterator  it = find(v1.begin(), v1.end(), p2);
	if (it == v1.end()) // ����Ƚ�ʱ�������رȽ������
	{
		cout << "û�ҵ�" << endl;
	}
	else
	{
		cout << "����Ϊ��" << (*it)._name << endl;
	}
	//	2.2.3 adjacent_find // ���������ظ�Ԫ��
	vector<int> v3;
	v3.push_back(0);
	v3.push_back(1);
	v3.push_back(1);
	v3.push_back(2);
	vector<int> ::iterator PP = adjacent_find(v3.begin(), v3.end());
	if (PP == v3.end())
	{
		cout << "δ�ҵ�" << endl;
	}
	else
	{
		cout << "�ҵ������ظ�Ԫ�أ�" <<*PP<< endl;
	}
	//	2.2.4 binary_search // ���ֲ��ҷ� �鵽����true ������������������
	if (binary_search(v.begin(), v.end(), 4))
	{
		cout << "�ҵ�Ԫ��" << endl;
	}
	else
	{
		cout << "û�ҵ�Ԫ��" << endl;
	}
	//	2.2.5 count  // ͳ�Ƹ���
	cout <<"v3Ԫ��1�ĸ���Ϊ"<< count(v3.begin(),v3.end(),1) << endl;
	Car c1(18, "chen");
	Car c2(20, "ccc");
	Car c3(20, "ccc");
	Car cc(20, "ccc");
	vector<Car> CV;
	CV.push_back(c1);
	CV.push_back(c2);
	CV.push_back(c3);
	// �Ƚ�֮ǰ��������==
	cout << "��cc��ͬ������ж����ˣ�" << count(CV.begin(), CV.end(), cc);
	//	2, 2, 6 count_if // ������ͳ�Ƹ���
	cout << endl;
	cout<<"v��Ԫ�ش���2�ĸ���Ϊ��"<<count_if(v.begin(),v.end(),greater2())<<endl;
	cout << "CV���������18�ĸ���Ϊ��" << count_if(CV.begin(), CV.end(), agegreater18()) << endl;

}
// �����㷨

void test_0041()
{
	//2.3.1 sort  // ����
	vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(-i);
	}
	sort(v.begin(), v.end(), greater<int>());//�ڽ���������
	//printvector(v);

	//	2.3.2 random_shuffe // �漴ϴ��
	random_shuffle(v.begin(), v.end());
	//printvector(v);

	//	2.3.3 merge // ����Ԫ�غϲ� �洢����һ������
	vector<int> v1;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i*i);
	}
	vector<int> v2;
	for (int i = 0; i < 10; i++)
	{
		v2.push_back(i );
	}
	vector<int> VV;
	printvector(v1);
	printvector(v2);
	// �����ڴ�
	VV.resize(v2.size() + v1.size());
	merge(v1.begin(), v1.end(), v2.begin(), v2.end(), VV.begin());
	printvector(VV);

	//	2.3.4 reverse // ��תԪ��
	reverse(v.begin(), v.end());
	//printvector(v);
}
// �������滻�㷨
void copy_func(int v1)
{
	cout << v1 << " ";
}
class greater45
{
public:
	bool operator() (int v1)
	{
		return v1 > 40;
	}

};
void test_0042()
{
	//2.4.1 copy // ����
	vector<int> v1;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i * i);
	}
	vector<int> v2;
	v2.resize(v1.size());
	copy(v1.begin(),v1.end(),v2.begin());
	for_each(v2.begin(), v2.end(), copy_func);
	cout << endl;
	printvector(v2);
	//2.4.2 replace // �滻
	spilit_line();
	replace(v2.begin(),v2.end(),49,50);
	printvector(v2);
	//2.4.3 replace_if //ָ����Χ������������Ԫ���滻Ϊ��Ԫ��
	spilit_line();
	// ʹ�÷º���ָ��func����
	replace_if(v2.begin(),v2.end(), greater45(),100);
	printvector(v2);
	//2.4.4 swap // ����2������Ԫ��
	spilit_line();
	swap(v1, v2);
	printvector(v2);
	printvector(v1);
}
// ���������㷨
void test_0043()
{
	//2.5.1 accumulate // ����������Ԫ���ۼӺ�
	vector<int> v1;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i * i);
	}
	cout<<"�ۼӺ�Ϊ��"<<accumulate(v1.begin(), v1.end(),0);
	//	2.5.2 fill  // �������Ԫ��
	cout << endl;
	spilit_line();
	fill(v1.begin(), v1.end(),100);
	printvector(v1);
}
// �����㷨
void myprint(int va)
{
	cout << va << " ";
}
void test_0044()
{
	// 2.6.1 set_intersection // ����
	//	2.6.2 set_union // ����
	//	2.6.3 set_difference // �
	vector<int>v1;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back( i);
	}
	vector<int>v2;
	for (int i = 0; i < 10; i++)
	{
		v2.push_back(i * i);
	}
	vector<int> v; // Ŀ������
	v.resize(min(v1.size() , v2.size())); // �������Ҳ������һ����С�����Ĵ�С
	vector<int> :: iterator  itEnd = set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),v.begin());
	cout << "�����Ľ���Ϊ" << endl;
	//ʹ����ͨ����ָ���������
	for_each(v.begin(), itEnd, myprint);
	cout << endl;
	// ֱ�����
	printvector(v);
	cout << "������СΪ��" << v.size() << endl;


	spilit_line();
	v.resize(v1.size() + v2.size());
	vector<int> ::iterator it1end = set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), v.begin());
	cout << "�����Ĳ���Ϊ" << endl;
	for_each(v.begin(), it1end, myprint);
	cout << endl;
	cout << "������СΪ��" << v.size() << endl;

	// � ��Ϊ˭��˭�Ĳ
	spilit_line();
	v.resize(max(v1.size() , v2.size())); // ȡ����
	vector<int> ::iterator it2end = set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), v.begin());
	cout << "v1��v2�������ĲΪ" << endl;
	for_each(v.begin(), it2end, myprint);
	cout << endl;
	cout << "���СΪ��" << v.size() << endl;
	vector<int> ::iterator it3end = set_difference(v2.begin(), v2.end(), v1.begin(), v1.end(), v.begin());
	cout << "v2��v1�������ĲΪ" << endl;
	for_each(v.begin(), it3end, myprint);
	cout << endl;
	cout << "���СΪ��" << v.size() << endl;
}
int common_algorithms()
//int main()
{
	//incline_function();
	// test_0039();
	//test_0040();
	//test_0041();
	//test_0042();
	//test_0043();
	test_0044();
	return 0;
}