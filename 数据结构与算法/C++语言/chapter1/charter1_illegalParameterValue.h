#pragma once
#pragma once
#include <string>
#include <iostream>
// ����һ���쳣�����ڲ����׳��쳣
// ����쳣�����ר�����ڴ��ݸ����ַ�����Ϣ
class illegalParameterValue
{
public:
	illegalParameterValue() :
		message("illegal parameter value") {} // Ĭ�Ϲ���ʹ���б���
	// ð�ź��ʹ��(),��С�����ڵ�ֵ������ʼ����Ա����ֵ
	/*
	������
	����class TEST�����ڳ�Ա����int a,b,c
	���캯����TEST(int x, int y):a(x),b(y),c(0){}
	��ʾʹ��x,y,0����ʼ��a,b,c
	ע�⣺��ʼ����˳�򲢲���������a,b,c�ڳ�ʼ���б��г��ֵ�˳�򣬶��������ж���a,b,c��˳����ͬ
	��������·��������壬ʵ�����б��ʼ������b,c,a����x��ʼ��b,y��ʼ��c,0��ʼ��a
	class TEST
	{
		public:
		int b;
		int c;
		int a;
		TEST(int x, int y):a(x),b(y),c(0){}
	};
	*/
	illegalParameterValue(const char* theMessage) // ��֤����ֱ��ʹ���ַ���ʵ����
	{
		// ���ƹ���
		message = theMessage;
	}
	
	illegalParameterValue(const std::string theMessage) { message = theMessage; }
	void outputMessage() { std::cout << message << std::endl; }

private:
	std::string message;
};
