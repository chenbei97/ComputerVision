#include "contanter.h"
/*
<1>stack��������
		�Ƚ���������ݽṹ ��ֻ��һ������
		ջ�������б�����Ϊ
		ջ��push�Ƚ� , Ȼ����������ջ�׺� ջ��û�г���
		ɾ������popҲ��ɾ��ջ��Ԫ��
		ע��ջ����λ�������±� ���Զ�����
<2>stack�ӿ�
		stack<T> stk ; // Ĭ�Ϲ���
		stack(const stack &stk) ; // ��������
		stack & operator = (const stack & stk) ;
		push(elem);
		pop();
		top();
		empty();
		sizie();
<3>queue��������
		�Ƚ��ȳ������ݽṹ����2�����ڣ�������
		���з����ɶ�βָ���ͷ����ͷ���Խ���pop��������β����push
		��һ��ֻ�ܳ����ݣ���һ�˽����� ����Ҳû�б�����Ϊ ��ֻ�ܶ�ͷ�Ͷ�β������
<4>queue�ӿ�
		queue<T> que;
		queue(const queue &que) ;
		queue& operator =(const queue &que) ; // ���صȺŲ�����
		push(elem) ; 
		pop() ;
		back();
		front();
		size();
		empty();
*/
class Person
{
public:
	int _age;
	string _name;
	Person(int age , string name)
	{
		this->_age = age;
		this->_name = name;
	}
};
void test_0029()
{
	stack<int> stk;
	stk.push(10);
	stk.push(20);
	stk.push(30);
	while (!stk.empty())
	{
		cout << "ջ��Ԫ��Ϊ��" << stk.top() << endl;
		stk.pop();//��ջ
	}
	cout << "ջ�Ĵ�С��"<<stk.size() << endl;

	queue <Person> q;
	Person p1(18 , "a");
	Person p2(19, "b");
	Person p3(20, "c");
	q.push(p1);
	q.push(p2);
	q.push(p3);
	while (!q.empty())
	{
		cout << "��ͷ������" <<q.front()._name<<"	"<<"��ͷ���䣺"<<q.front()._age<< endl;
		cout << "��β������" << q.back()._name << "	" << "��β���䣺" << q.back()._age << endl;
		q.pop();
	}
}
int stack_queue_containter()
//int main()
{
	//stl_example();

	test_0029();

	return 0;
}