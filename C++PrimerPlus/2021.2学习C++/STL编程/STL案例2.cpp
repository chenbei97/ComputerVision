#include "contanter.h"
/*
<需求说明>
		1. 10个员工ABCDE FGHIJ
		2. 员工信息：姓名 工资组成
		3. 部门分为 ：策划、美术、研发
		4. 随机给10名员工分配部门和工资
		5. 通过multimap进行信息的插入 key(部门编号) value(员工)
		6. 分部门显示员工信息
		<2>步骤
		1. 创建10名员工 放入如vector
		2. 遍历vecto容器对每个员工进行随机分组到三个部门
		3. 分组后员工部门编号作为key，具体员工作为value，放入multimap
		4. 分部门显示员工信息
*/
#define CE_HUA 1 
#define MEI_SHU 2
#define YAN_FA 3
class Worker
{
public:
	string _name;
	int _salary;
};
void createWorker(vector<Worker> & v)
{
	string nameSeed = "ABCDEFGHIJ";
	for (int i = 0; i < 10; i++)
	{
		Worker worker;
		worker._name = "员工";
		worker._name += nameSeed[i];;
		worker._salary = rand() % 10000 + 10000;//10000~19999
		v.push_back(worker); // 把员工放入vecotr
	}
}
void printWorker(const vector<Worker>& v)
{
	for (vector<Worker> ::const_iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "员工姓名：" << (*it)._name << "		" << "员工工资：" << (*it)._salary <<endl;
	
	}
}
void setGroup(const vector<Worker>& v, multimap<int, Worker>& w)
{
	for (vector<Worker> ::const_iterator it = v.begin(); it != v.end(); it++)
	{
		// 产生随机部门编号
		int DepartId = rand() % 3 + 1; // 1,2,3
		// 插入编号和员工
		w.insert(make_pair(DepartId , *(it) ));
	}
}
void showMultimapPerson(multimap<int,Worker> & w)
{
	// 1. 策划部门信息
	int n1 = w.count(CE_HUA);
	int idx1 = 0;
	cout << "策划部门员工人数：" <<n1<< endl;
	multimap<int ,Worker> :: iterator pos1  = w.find(CE_HUA);
	for (; pos1 != w.end()&& idx1<n1 ; idx1++,pos1++)
	{
		cout<< "\t员工姓名："<<(*pos1).second._name<<"		"
		<<"员工工资："<<(*pos1).second._salary<< endl;
	}
	spilit_line();
	// 2. 美术部门信息
	int n2 = w.count(MEI_SHU);
	int idx2 = 0;
	cout << "美术部门员工信人数：" << n2 << endl;
	multimap<int, Worker> ::iterator pos2 = w.find(MEI_SHU);
	for (; pos2 != w.end() &&  idx2< n2 ; idx2 ++ ,pos2++)
	{
		cout << "\t员工姓名：" << (*pos2).second._name << "		"
			<< "员工工资：" << (*pos2).second._salary << endl;
	}
	spilit_line();
	
	// 3. 研发部门信息
	int n3 = w.count(YAN_FA);
	int idx3 = 0;
	cout << "研发部门员工人数：" << n3 << endl;
	multimap<int, Worker> ::iterator pos3 = w.find(YAN_FA);
	for (; pos3 != w.end() && idx3 < n3; idx3++,  pos3++)
	{
		cout << "\t员工姓名：" << (*pos3).second._name << "		"
			<< "员工工资：" << (*pos3).second._salary << endl;
	}
}
int stl_example2()
//int main()
{
	srand((unsigned int)time(NULL));
	// 1. 创建员工容器
	vector<Worker> v;
	createWorker(v);
	printWorker(v);
	spilit_line();
	// 2. 员工分组 : 部门编号为key value为员工
	//函数中去调用每个员工所以需要v,然后分组存放于multimap也需要mworker
	multimap<int, Worker> mworker; 
	setGroup(v, mworker);
	// 3. 分组显示员工
	showMultimapPerson(mworker);

	return 0;
}