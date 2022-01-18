#include "charter6_chainListWithIterator.h"
#include "charter6_studentRecord1.h"
// ���򷽷��Ƕ���ʵ�ֵ�û����Ϊ������ĳ�Ա����
// ע��ʹ�õ��Ǵ��������ĵ�������������չ�ĵ���������ߵ���ѭ������
// ʹ�õ�ѧ���������Գ�����_charter6_studentRecord1(ֻ��!=��<<����)
void _charter6_studentRecord_binsort(_charter6_chainListWithIterator<_charter6_studentRecord1>& theChain, int range);
void _charter6_StudentRecord1_binSort_testCode()
{
	typedef _charter6_chainListWithIterator<_charter6_studentRecord1> chain; // ����̫��ȡ������
	typedef  _charter6_studentRecord1 stu; // ����ֻ�ھֲ�������Ч
	stu s;
	chain c;
	int aidx = 97; // �ַ�a��ASCII��λ��
	for (int i = 1; i <= 20; i++)  // ��20��ѧ����ʼ��
	{
		s.score = i / 2; 
		s.name = new string (1,aidx++); // ��������
		c.insert(0, s); // ����ͷ�ͷ��,��ô��߷�������λ,��ͷ���β�ڵ�,����Ĳ�������
	}
	cout << "The unsorted chain is" << endl;
	cout << "  "<<c << endl;
	_charter6_studentRecord_binsort(c, 10); // 10������ߵ�����
	cout << "The sorted chain is" << endl;
	cout << "  " << c << endl;
}
void _charter6_studentRecord_binsort(_charter6_chainListWithIterator<_charter6_studentRecord1>& theChain, int range)
{
	// �������1��ѧ���������͵�����,range�Ƿ����ĵ�λ������˵�����С
	typedef _charter6_chainListWithIterator<_charter6_studentRecord1> chain; // ����̫��ȡ������
	typedef  _charter6_studentRecord1 stu; // ����ֻ�ھֲ�������Ч
	chain* bin; // ÿ�����Ӷ���1������,һ��ָ�����������ַ��ָ��
	
	// Ψһ��������ʧ�ܵ����,��Ϊ�ڴ���ܷ��䲻��
	bin = new chain[range+1]; // new 1����������,������range+1,��score��ͬ,���볡��Ϊ0,1,2,3,4,5
	
	int size = theChain.size(); // ��д��forѭ����,��ΪtheChain.size()��̬�ı��
	// Ϊ��ִ��size��,��Ϊ��size��Ԫ��,ÿ�ζ�ȡ��1��
	for (int i = 1; i <=size ; i++) // ������ĵ�1��ѧ����ʼ,ʱ�临�ӶȦ�(n)
	{
		stu x = theChain.get(0); // �õ���0��ѧ������Ϣ ��(1)
		theChain.erase(0); // �Ѵ���������0��ѧ����ȥ ��(1)
		// =>����ִ�����ǵõ�����ĵ�0��ѧ��,������Խ��Խ�� 
		bin[x.score].insert(0, x);//���õ���ѧ����Ϣ���ݷ������뵽��������Ĳ�ͬ������ ��(1)

		// ��ʱ��ɺ��˲�ͬ����ѧ���ķּ�
		// ������ֻ��Ҫѭ��ȡ����������������
	}

	// �������ռ�ѧ����Ϣ
	for (int j = range; j >= 0; j--) // j=5,4,3,2,1,0,���δӲ�ͬ����ȡ��Ԫ��,ʱ�临�ӶȦ�(n+range)
	{
		while (!bin[j].empty()) // ����ȡ1����Ҫ����1��,�����ж��������ǲ�Ϊ�վ�ִ��while
		{
			stu x = bin[j].get(0);// �õ�j���ӵ��׸�ѧ�� ��(1)
			bin[j].erase(0);// j���Ӳ��� ��(1)
			theChain.insert(0, x); // theChain�Ǹ���������,���ǿ��Լ���ͷ���,β�廹Ҫָ����������ͷ�� ��(1)
		}// ��Ϊj�Ӹ߷ֱ���,������ͷ��,���Ը߷����ں���,��������������
	}
	delete[] bin; // ���������� new ��delete��������
}