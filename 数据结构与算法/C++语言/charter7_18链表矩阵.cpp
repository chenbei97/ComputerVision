#include "charter7_linkedMatrix.h"
void _charter7_linkedMatrix()
{
	linkedMatrix<double> m1;
	m1.output(); // ����û�з�0Ԫ�ص�ϡ�����
	const int Row = 20;
	const int Col = 20;
	const int n = 100; // ����n����0Ԫ��
	const int rn = n / Row; // ÿ�з�rn��
	double values[n] = {};
	int cols[n] = {}; // n����
	srand((unsigned)time(NULL));
	for (int j = 0; j < n; j++)
	{
		cols[j] = rand() % (Col)+1;// �������1-40�ڵ�������
		values[j] = (double)j + 1;
		//cout << "col = " << cols[j] << "  value = " << values[j] << "  ";
	}
	//cout << endl;
	rowLinkedListElement<double> * rLE  = new  rowLinkedListElement<double> [n] ; // �������Ԫ�ض���
	rowLinkedList<double> * rLL = new rowLinkedList<double> [Row]; // ���������
	linkedMatrixChain<rowLinkedList<double>> headerChain;
	linkedMatrixChain<rowLinkedListElement<double>> *  rowChain =
		new linkedMatrixChain<rowLinkedListElement<double>> [Row];
	// �����ǿ����ڴ��,ֱ��ʹ��rLE/rLL/headerChain��ʵ����ַ���������1��,��ô�����ͻ����
	// rLE��100��,rowChain��20��,ÿ5����ӽ�1��rowChain[i],Ȼ��rLL[i].rowChainָ�����rowChain[i]
	// ���headerChain��1��,push_back ÿ�� rLL[i] ����
	// ����headerChain���ڲ������ǲ�ͬ�ĵ�ַָ��ͬ��������,�������
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
	// m2.output(); // ��ֱ�Ӵ�ӡheaderChain��һ����
	cout << "m2 is " << endl << m2 << endl;
	m2.transpose(m1);
	cout << "after transpose��"<<endl<< m1 << endl;
}