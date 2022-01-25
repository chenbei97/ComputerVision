#include "chapter9_arrayQueue.h"
#include <assert.h>
#include <string>
#include <iostream>
using namespace std;
void _chapter9_arrayQueue()
{
	arrayQueue<string> F(4);
	if (F.empty())
		cout << "The queue is empty" << endl;
	//F.log(true);
	F.push("A"); F.push("B"); F.push("C");
	cout << "F.size is " << F.size() << endl;
	cout << "F is \n"<< F << endl; // 测试没有拓展过容量时的cout
	cout << "--------------------------------------------------------------------" << endl;
	F.push("D"); F.push("E");  F.push("F"); F.push("G");
	cout << "F is \n" << F << endl;// 测试拓展过容量时的cout
	cout << "--------------------------------------------------------------------" << endl;
	F.pop(); F.pop(); F.pop(); cout << "F is \n" << F << endl; // pop过再进行测试
	cout << "--------------------------------------------------------------------" << endl;
	F.push("H"); cout << "F is \n" << F << endl;// pop且再push进行测试
	cout << "--------------------------------------------------------------------" << endl;
	F.push("I"); F.push("J"); F.log(true);  F.push("K"); cout << "F is \n" << F << endl; // push到临界点再进行测试
	cout << "--------------------------------------------------------------------" << endl;
	
	cout << "\n\n--------------------------------------------------------------------" << endl;
	const int n = 4;
	arrayQueue<string> q(n);
	const int m = 26;
	string str[m] = {"A","B","C","D","E",
							  "F","G","H","I","J",
							  "K","L","M","N","O",
							  "P","Q","R","S","T",
							  "U","V","W","X","Y","Z"};
	//q.log(true);
	for (int i = 1; i <= m; i++)
	{
		q.push(str[i-1]);
		cout <<"Push "<< i << " =>>>>>>>\n" << q << endl;
	}
	//cout << q << endl;
	cout << "now q.size() is " << q.size() << endl;
	int idx = 0;
	while (!q.empty())
	{
		q.pop(); 
		cout <<"Pop "<< idx << " =>>>>>>>\n" << q << endl;
		idx++;
	}
	try { q.pop(); }
	catch (queueEmpty message)
	{
		cout << "Last pop failed " << endl;
		message.outputMessage();
	}

	
	cout << "\n--------------------------------------------------------------------" << endl;
	// 创建一个环绕队列并执行数组加倍
	//arrayQueue<string> r(4);
	//r.log(true);
	//for (int i = 1; i <= 9; i++)
	//{
	//	r.push(str[i-1]); // push到第4个容量会加倍
	//	if (i == 4) // 删除2个之后再加剩余的5个,实际上有7个元素
	//		for (int j = 1; j <= 2; j++)
	//		{
	//			r.pop();
	//		}				
	//}
	//assert(r.size() == 7);
}