#include "contanter.h"
/*
5��ѡ��ABCDE 10����ί�ֱ��ÿһ��ѡ�ִ�֣�ȥ����߷ֺ���ͷ� ȡƽ����
1. ����5��ѡ�ַ���vector
2. ����vector��������һ��ѡ�ּ������� ��10�����ִ浽deque����
3. sort�㷨��deque������������ ��ȥ��������
4. deque���������ۼ��ܷ�
5. ƽ����
*/
class Person
{
public:
	string _name;
	int _score;
	Person(string name, int score)
	{
		this->_name = name;
		this->_score = score;
	}
};
void createPerson(vector<Person> &v)
{
	string nameSeed = "ABCDE";
	for (int i = 0; i < 5; i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];
		int score = 0;
		Person p(name, score);
		v.push_back(p);
	}
}
void createAvaScore(vector<Person>& v)
{
	// �ȱ�������5����
	for (vector<Person> ::iterator it = v.begin(); it != v.end(); it++)
	{
		// �ٱ���ÿ���˵ĵ÷� 
		deque<int>  d;
		for(int i = 0; i < 10; i++)
		{ 
			int score = rand() % 41 + 60;
			d.push_back(score);
		}
		// �Է�������
		sort(d.begin(), d.end());
		// ȥ�������ͷ�
		d.pop_back();
		d.pop_front();
		// ƽ����
		int sum = 0;
		for (deque<int> ::iterator it1 = d.begin(); it1 != d.end(); it1++)
		{
			sum += *it1;
		}
		int avg = sum / d.size();
		// ƽ���ָ�ֵ��ѡ��
		it->_score = avg;
	}
} 
void printScore( const vector<Person> & v)
{

	for (vector<Person> ::const_iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "����Ϊ��"<<it->_name <<"	"<<"����Ϊ��"<<it->_score <<endl;
	}
}
int stl_example1()
//int main()
{
	srand((unsigned int) time (NULL));
	//deque_containter();
	// 1. 5��ѡ��
	vector<Person>  v;
	createPerson(v);
	//2 .5��ѡ�ִ��
	createAvaScore(v);
	//3. ��ʾ�÷�
	printScore(v);
	return 0;
}