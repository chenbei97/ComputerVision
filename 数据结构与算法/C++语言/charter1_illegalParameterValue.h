#pragma once
#include <string>
#include <iostream>
// 定义一个异常类用于参数抛出异常
// 这个异常类可以专门用于传递各类字符串信息
class illegalParameterValue
{
public:
	illegalParameterValue() :
		message("illegal parameter value") {} // 默认构造使用列表构造
	// 冒号后边使用(),用小括号内的值，来初始化成员变量值
	/*
	举例：
	对于class TEST，存在成员变量int a,b,c
	构造函数：TEST(int x, int y):a(x),b(y),c(0){}
	表示使用x,y,0来初始化a,b,c
	注意：初始化的顺序并不是依赖于a,b,c在初始化列表中出现的顺序，而是与类中定义a,b,c的顺序相同
	如果类像下方这样定义，实际上列表初始化的是b,c,a，即x初始化b,y初始化c,0初始化a
	class TEST
	{
		public:
		int b;
		int c;
		int a;
		TEST(int x, int y):a(x),b(y),c(0){}
	};
	*/
	illegalParameterValue(const char* theMessage) // 保证可以直接使用字符串实例化
	{
		// 复制构造
		message = theMessage;
	}
	void outputMessage() { std::cout << message << std::endl; }
		
private:
	std::string message;
};
