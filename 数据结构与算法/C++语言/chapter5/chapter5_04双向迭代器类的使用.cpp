#include "chapter5_bidirectIterator.h"
#include <iostream>
void _chapter5_bidirectional_iterator()
{
	// �����ʵ�ֺ�����д��1��ͷ�ļ��Ϳ���ֱ��ʹ����
	_chapter5_bidirectIterator<int> iterator;
	int x[5] = { 3,7,9,2,6 };
	int count = 0;
	// ����˵��charter5_03�������ĸ���.cpp�еĵ�����y��Ҫ�Լ��ȶ���ָ��һ������
	// �����y����++,--,*�Ȳ�����,��Ϊָ�뱾���Ǵ�����Щ������
	// ���ļ����Ƕ���һ���Լ���ָ������,Ҳ���Խе�����
	// ���������и��ƹ���
	for (iterator = x; iterator != x + 5; iterator++)
	{
		std::cout << "x[" << count << "] =" << *iterator<< "   ";
		count++;
	}
	std::cout << std::endl;
	iterator = x; // ����ָ��ͷ
	// �Ƚ�ǰ+�ͺ�+������
	printf("iterator++�ı��ʽֵû��,"
		"ʹ�õı�����Ȼ������֮ǰ��Ϊx[0]=3,��*iterator++ = %d\n", *iterator++);
	printf("���ʽ���������,iterator����,��ʱ�����Ƿ����x[1]=7,*iterator = %d\n", *iterator);
	printf("��ʱʹ��*++iterator,���Ӧ����x[2]=9,������+Ȼ��ʹ��,���ʽΪ+��Ľ��,����*++iterator = %d\n", *++iterator);
    // --������ͬ��  
	iterator.print_position(); // the current pointer position value is 9
	_chapter5_bidirectIterator<int>* piterator = &iterator;
	piterator->print_position(); // the current pointer position value is 9
	// ����->��ͷ�����
	(&iterator)->print_position();// the current pointer position value is 9
}