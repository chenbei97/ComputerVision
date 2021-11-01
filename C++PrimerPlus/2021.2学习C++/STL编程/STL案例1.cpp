#include "contanter.h"
/*
5名选手ABCDE 10个评委分别对每一名选手打分，去除最高分和最低分 取平均分
1. 创建5名选手放入vector
2. 遍历vector容器，对一个选手继续遍历 将10个评分存到deque容器
3. sort算法对deque分数容器排序 并去除最高最低
4. deque容器遍历累加总分
5. 平均分
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
		string name = "选手";
		name += nameSeed[i];
		int score = 0;
		Person p(name, score);
		v.push_back(p);
	}
}
void createAvaScore(vector<Person>& v)
{
	// 先遍历容器5个人
	for (vector<Person> ::iterator it = v.begin(); it != v.end(); it++)
	{
		// 再遍历每个人的得分 
		deque<int>  d;
		for(int i = 0; i < 10; i++)
		{ 
			int score = rand() % 41 + 60;
			d.push_back(score);
		}
		// 对分数排序
		sort(d.begin(), d.end());
		// 去除最高最低分
		d.pop_back();
		d.pop_front();
		// 平均分
		int sum = 0;
		for (deque<int> ::iterator it1 = d.begin(); it1 != d.end(); it1++)
		{
			sum += *it1;
		}
		int avg = sum / d.size();
		// 平均分赋值给选手
		it->_score = avg;
	}
} 
void printScore( const vector<Person> & v)
{

	for (vector<Person> ::const_iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "姓名为："<<it->_name <<"	"<<"分数为："<<it->_score <<endl;
	}
}
int stl_example1()
//int main()
{
	srand((unsigned int) time (NULL));
	//deque_containter();
	// 1. 5名选手
	vector<Person>  v;
	createPerson(v);
	//2 .5名选手打分
	createAvaScore(v);
	//3. 显示得分
	printScore(v);
	return 0;
}