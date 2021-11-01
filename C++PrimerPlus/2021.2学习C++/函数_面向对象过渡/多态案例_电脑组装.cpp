#include <iostream>
using namespace std;
//#include "quote_pointer.h"
// 电脑组件  ： 显卡、cpu、内存条(3个基类)
// 每个组件有不同的厂商(拓展类 重写基类的函数)
// 电脑类调用组件类和厂商类去实现具体的功能
// 电脑类初始化时可以使用3个基类的指针 然后用函数去实现
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
	// 重写父类
	virtual void calculate()
	{
		cout << "英特尔的CPU开始运转了！" << endl;
	}
};
class IntelGraphicCard : public GraphicCard
{
public:
	// 重写父类
	virtual void display()
	{
		cout << "英特尔的显卡开始显示了！" << endl;
	}
};
class IntelMemoryCard : public MemoryCard
{
public:
	// 重写父类
	virtual void storage()
	{
		cout << "英特尔的内存条开始储存了！" << endl;
	}
};
class LenovoCPU : public CPU
{
public:
	// 重写父类
	virtual void calculate()
	{
		cout << "Lenovo的CPU开始运转了！" << endl;
	}
};
class LenovoGraphicCard : public GraphicCard
{
public:
	// 重写父类
	virtual void display()
	{
		cout << "Lenovo的显卡开始显示了！" << endl;
	}
};
class LenovoMemoryCard : public MemoryCard
{
public:
	// 重写父类
	virtual void storage()
	{
		cout << "Lenovo的内存条开始储存了！" << endl;
	}
};
class Computer 
{
public:
	// 构造函数实现调用3个基类
	Computer(CPU* cpu, GraphicCard* graphiccard, MemoryCard* memory)
	{
		_cpu = cpu;
		_graphiccard = graphiccard;
		_memory = memory;
	}
	// 公共函数实现功能
	void  Work()
	{
		_cpu->calculate();
		_graphiccard->display();
		_memory->storage();
	}
	// 提供析构函数 释放3个零件的堆区内存
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