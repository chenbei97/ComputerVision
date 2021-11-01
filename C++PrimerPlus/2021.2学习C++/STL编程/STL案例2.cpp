#include "contanter.h"
/*
<����˵��>
		1. 10��Ա��ABCDE FGHIJ
		2. Ա����Ϣ������ �������
		3. ���ŷ�Ϊ ���߻����������з�
		4. �����10��Ա�����䲿�ź͹���
		5. ͨ��multimap������Ϣ�Ĳ��� key(���ű��) value(Ա��)
		6. �ֲ�����ʾԱ����Ϣ
		<2>����
		1. ����10��Ա�� ������vector
		2. ����vecto������ÿ��Ա������������鵽��������
		3. �����Ա�����ű����Ϊkey������Ա����Ϊvalue������multimap
		4. �ֲ�����ʾԱ����Ϣ
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
		worker._name = "Ա��";
		worker._name += nameSeed[i];;
		worker._salary = rand() % 10000 + 10000;//10000~19999
		v.push_back(worker); // ��Ա������vecotr
	}
}
void printWorker(const vector<Worker>& v)
{
	for (vector<Worker> ::const_iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "Ա��������" << (*it)._name << "		" << "Ա�����ʣ�" << (*it)._salary <<endl;
	
	}
}
void setGroup(const vector<Worker>& v, multimap<int, Worker>& w)
{
	for (vector<Worker> ::const_iterator it = v.begin(); it != v.end(); it++)
	{
		// ����������ű��
		int DepartId = rand() % 3 + 1; // 1,2,3
		// �����ź�Ա��
		w.insert(make_pair(DepartId , *(it) ));
	}
}
void showMultimapPerson(multimap<int,Worker> & w)
{
	// 1. �߻�������Ϣ
	int n1 = w.count(CE_HUA);
	int idx1 = 0;
	cout << "�߻�����Ա��������" <<n1<< endl;
	multimap<int ,Worker> :: iterator pos1  = w.find(CE_HUA);
	for (; pos1 != w.end()&& idx1<n1 ; idx1++,pos1++)
	{
		cout<< "\tԱ��������"<<(*pos1).second._name<<"		"
		<<"Ա�����ʣ�"<<(*pos1).second._salary<< endl;
	}
	spilit_line();
	// 2. ����������Ϣ
	int n2 = w.count(MEI_SHU);
	int idx2 = 0;
	cout << "��������Ա����������" << n2 << endl;
	multimap<int, Worker> ::iterator pos2 = w.find(MEI_SHU);
	for (; pos2 != w.end() &&  idx2< n2 ; idx2 ++ ,pos2++)
	{
		cout << "\tԱ��������" << (*pos2).second._name << "		"
			<< "Ա�����ʣ�" << (*pos2).second._salary << endl;
	}
	spilit_line();
	
	// 3. �з�������Ϣ
	int n3 = w.count(YAN_FA);
	int idx3 = 0;
	cout << "�з�����Ա��������" << n3 << endl;
	multimap<int, Worker> ::iterator pos3 = w.find(YAN_FA);
	for (; pos3 != w.end() && idx3 < n3; idx3++,  pos3++)
	{
		cout << "\tԱ��������" << (*pos3).second._name << "		"
			<< "Ա�����ʣ�" << (*pos3).second._salary << endl;
	}
}
int stl_example2()
//int main()
{
	srand((unsigned int)time(NULL));
	// 1. ����Ա������
	vector<Worker> v;
	createWorker(v);
	printWorker(v);
	spilit_line();
	// 2. Ա������ : ���ű��Ϊkey valueΪԱ��
	//������ȥ����ÿ��Ա��������Ҫv,Ȼ���������multimapҲ��Ҫmworker
	multimap<int, Worker> mworker; 
	setGroup(v, mworker);
	// 3. ������ʾԱ��
	showMultimapPerson(mworker);

	return 0;
}