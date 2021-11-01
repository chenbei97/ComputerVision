#include <iostream>
using namespace std;
//#include "quote_pointer.h"
// �������  �� �Կ���cpu���ڴ���(3������)
// ÿ������в�ͬ�ĳ���(��չ�� ��д����ĺ���)
// ��������������ͳ�����ȥʵ�־���Ĺ���
// �������ʼ��ʱ����ʹ��3�������ָ�� Ȼ���ú���ȥʵ��
class CPU 
{
public:
	virtual void calculate() = 0;
};
class GraphicCard
{
public:
	virtual void display() = 0;
};
class MemoryCard
{
public:
	virtual void storage() = 0;
};
class IntelCPU : public CPU
{
public:
	// ��д����
	virtual void calculate()
	{
		cout << "Ӣ�ض���CPU��ʼ��ת�ˣ�" << endl;
	}
};
class IntelGraphicCard : public GraphicCard
{
public:
	// ��д����
	virtual void display()
	{
		cout << "Ӣ�ض����Կ���ʼ��ʾ�ˣ�" << endl;
	}
};
class IntelMemoryCard : public MemoryCard
{
public:
	// ��д����
	virtual void storage()
	{
		cout << "Ӣ�ض����ڴ�����ʼ�����ˣ�" << endl;
	}
};
class LenovoCPU : public CPU
{
public:
	// ��д����
	virtual void calculate()
	{
		cout << "Lenovo��CPU��ʼ��ת�ˣ�" << endl;
	}
};
class LenovoGraphicCard : public GraphicCard
{
public:
	// ��д����
	virtual void display()
	{
		cout << "Lenovo���Կ���ʼ��ʾ�ˣ�" << endl;
	}
};
class LenovoMemoryCard : public MemoryCard
{
public:
	// ��д����
	virtual void storage()
	{
		cout << "Lenovo���ڴ�����ʼ�����ˣ�" << endl;
	}
};
class Computer 
{
public:
	// ���캯��ʵ�ֵ���3������
	Computer(CPU* cpu, GraphicCard* graphiccard, MemoryCard* memory)
	{
		_cpu = cpu;
		_graphiccard = graphiccard;
		_memory = memory;
	}
	// ��������ʵ�ֹ���
	void  Work()
	{
		_cpu->calculate();
		_graphiccard->display();
		_memory->storage();
	}
	// �ṩ�������� �ͷ�3������Ķ����ڴ�
	~Computer() 
	{
		if (_cpu != NULL){delete _cpu;_cpu = NULL;}
		if (_graphiccard != NULL) { delete _graphiccard; _graphiccard = NULL; }
		if (_memory != NULL) { delete _memory; _memory = NULL; }
	
	}
private:
	CPU* _cpu;
	GraphicCard * _graphiccard;
	MemoryCard* _memory;
};
void testComputer()
{
	CPU* intel_cpu = new IntelCPU;
	GraphicCard* intel_graphic_card = new IntelGraphicCard;
	MemoryCard* intel_menmory_card = new IntelMemoryCard;
	Computer *intel_computer = new Computer(intel_cpu, intel_graphic_card, intel_menmory_card);
	intel_computer->Work();
	delete intel_computer;

	Computer* lenovo_computer = new Computer(new LenovoCPU, new LenovoGraphicCard, new LenovoMemoryCard);
	lenovo_computer->Work();
	delete lenovo_computer;
}
int computer_operator()
//int main()
{
	testComputer();

	return 0;

}