#include "chapter7_linkedMatrix.h"
void _chapter7_linkedMatrix()
{
	linkedMatrix<double> m1;
	m1.output(); // 测试没有非0元素的稀疏矩阵
	const int Row = 20;
	const int Col = 20;
	const int n = 100; // 创建n个非0元素
	const int rn = n / Row; // 每行分rn个
	double values[n] = {};
	int cols[n] = {}; // n个列
	srand((unsigned)time(NULL));
	for (int j = 0; j < n; j++)
	{
		cols[j] = rand() % (Col)+1;// 随机生成1-40内的列坐标
		values[j] = (double)j + 1;
		//cout << "col = " << cols[j] << "  value = " << values[j] << "  ";
	}
	//cout << endl;
	rowLinkedListElement<double> * rLE  = new  rowLinkedListElement<double> [n] ; // 行链表的元素对象
	rowLinkedList<double> * rLL = new rowLinkedList<double> [Row]; // 行链表对象
	linkedMatrixChain<rowLinkedList<double>> headerChain;
	linkedMatrixChain<rowLinkedListElement<double>> *  rowChain =
		new linkedMatrixChain<rowLinkedListElement<double>> [Row];
	// 必须是开辟内存的,直接使用rLE/rLL/headerChain的实例地址不会变总是1个,那么析构就会出错
	// rLE是100个,rowChain有20个,每5个添加进1个rowChain[i],然后rLL[i].rowChain指向这个rowChain[i]
	// 最后headerChain是1个,push_back 每个 rLL[i] 即可
	// 这样headerChain的内部才能是不同的地址指向不同的行链表,否则出错
	int row = 0;
	for (int j = 0; j < n; j++)
	{
		rLE[j].col = cols[j];
		rLE[j].value = values[j];
		rowChain[row].push_back(rLE[j]);
		if ((j + 1) % rn == 0)
		{
			rLL[row].rowChain = rowChain[row];
			rLL[row].row = row + 1;
			headerChain.push_back(rLL[row]);
			row++;
		}
	}
	// cout << headerChain << endl;
	linkedMatrix<double> m2(Row,Col,headerChain);
	cout << "m2(1,"<<cols[3]<<") = " << m2(1, cols[3]) << endl;
	cout << "m2(1,2) = " << m2(1, 2) << endl;
	// m2.output(); // 和直接打印headerChain是一样的
	cout << "m2 is " << endl << m2 << endl;
	m2.transpose(m1);
	cout << "after transpose："<<endl<< m1 << endl;
}