#include "contanter.h"
/*
<1>map��������
		1.1 map������Ԫ�ض���pair����һ��Ϊkey �ڶ���Ϊvalue
		1.2 ����Ԫ�ػ���ݼ�ֵ�Զ�����
		1.3 map/muitimap���ڹ���ʽ�������ײ�Ϊ��������multimap�������ظ�keyֵ��Ԫ��
<2>map����͸�ֵ
		2.1 map<T1,T2> mp ; // Ĭ�Ϲ���
		2.2 map(const map &mp) ; //��������
		2.3 map& operator = (const map & mp) ; // ���ظ�ֵ
<3>map��С�ͽ���
		3.1 size();
		3.2 empty();
		3.3 swap(mp);
<4>map�����ɾ��
		4.1 insert(elem) ;
					4.1.1 m.insert(pair<int, int>(1, 10)); //������ֵ
					4.1.2 m.insert(make_pair(5, 50)); // �ɶԸ�ֵ
					4.1.3 m.insert(map<int, int> ::value_type(6, 60)); //������ֵ
					4.1.4 m[7] = 70; // �������ظ�ֵ(������ʹ��)����ȫ���ʹ��cout<<m[8]<<endl;�ֻ��½��µ�ֵ
		4.2 clear();
		4.3 erase(pos) ; //ɾ��posָ��Ԫ�� ������һ��Ԫ�صĵ�����
		4.4 erase(beg ,end) ; // ɾ��[beg,end)Ԫ�� ������һ��Ԫ�ص�����
		4.5 erase(key) ;// ɾ��key��Ԫ��
<5>map���Һ�ͳ��
		5.1 find(key) ; // ����key�Ƿ���ڣ����ڷ���key�ĵ��������򷵻�set.end();
		5.2 count(key) ; // ͳ��key����
<6>map����
		6.1 Ĭ�ϰ���key��С��������

<7>map����Ա������
	

*/
class comparemap
{
public:
	bool operator () (int v1, int v2) const
	{
		return v1 > v2; // ����
	}

};
void printmap(const map<int , int ,comparemap> & mp)
{
	for (map<int, int,comparemap> ::const_iterator it = mp.begin(); it != mp.end(); it++)
	{
		cout << "map�ļ�Ϊ��" << (*it).first << "	" << "map��ֵΪ��" << (*it).second<< endl;;
	}
}
void test_0034()
{
	// 6.1 Ĭ�ϰ���key��С�������� �º�������
	map <int, int ,comparemap> m;
	m.insert(pair<int, int>(1, 10)); //������ֵ
	m.insert(pair<int, int>(2, 20));
	m.insert(pair<int, int>(3, 30));
	m.insert(pair<int, int>(4, 40));
	m.insert(make_pair(5, 50)); // �ɶԸ�ֵ
	m.insert(map<int, int> ::value_type(6, 60)); //������ֵ
	m[7] = 70; // �������ظ�ֵ ����ȫ���ʹ��cout<<m[8]<<endl;�ֻ��½��µ�ֵ
	map<int, int ,comparemap>m2(m);
	map<int, int,comparemap>m3;
	m3 = m2;
	printmap(m3);
	//cout << "-------------------------�ָ���------------------------------" << endl;
	spilit_line();
	m3.erase(m3.begin());//��λ��ɾ��
	m3.erase(3); // ��keyɾ��
	printmap(m3);
	multimap<int, int > m5;
	m5.insert(pair<int, int>(100, 100));
	m5.insert(pair<int, int>(100, 100));
	spilit_line();
	// 5.1 find(key); // ����key�Ƿ���ڣ����ڷ���key�ĵ��������򷵻�set.end();
	map<int, int> ::iterator pos = m5.find(100);
	if (pos != m5.end())
	{
		cout << "�ҵ�Ԫ��key=100��ֵΪ��" <<(*pos).second<< endl;
	}
	else
	{
		cout << "û���ҵ���" << endl;
	}
	//5.2 count(key); // ͳ��key����
	cout << "key=100�ĸ���Ϊ��" << m5.count(100) << endl;
}
int map_containter()
//int main()
{
	//set_containter();
	test_0034();
	return 0;
}