#include "contanter.h"
/*
<1>stack容器概念
		先进后出的数据结构 且只有一个出口
		栈不允许有遍历行为
		栈顶push先进 , 然后慢慢到达栈底后 栈底没有出口
		删除函数pop也是删除栈顶元素
		注：栈顶的位置是在下边 即自顶向上
<2>stack接口
		stack<T> stk ; // 默认构造
		stack(const stack &stk) ; // 拷贝构造
		stack & operator = (const stack & stk) ;
		push(elem);
		pop();
		top();
		empty();
		sizie();
<3>queue容器概念
		先进先出的数据结构，有2个出口，即队列
		队列方向由队尾指向队头，对头可以进行pop操作，队尾则是push
		即一端只能出数据，另一端进数据 队列也没有遍历行为 且只能队头和队尾被访问
<4>queue接口
		queue<T> que;
		queue(const queue &que) ;
		queue& operator =(const queue &que) ; // 重载等号操作符
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
		cout << "栈顶元素为：" << stk.top() << endl;
		stk.pop();//出栈
	}
	cout << "栈的大小："<<stk.size() << endl;

	queue <Person> q;
	Person p1(18 , "a");
	Person p2(19, "b");
	Person p3(20, "c");
	q.push(p1);
	q.push(p2);
	q.push(p3);
	while (!q.empty())
	{
		cout << "队头姓名：" <<q.front()._name<<"	"<<"队头年龄："<<q.front()._age<< endl;
		cout << "队尾姓名：" << q.back()._name << "	" << "队尾年龄：" << q.back()._age << endl;
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