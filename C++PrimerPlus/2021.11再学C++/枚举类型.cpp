#include "all.h"

void Study_enum()
{
	enum color1  {blue,red,green}; // 定义枚举类型,默认blue=0,red=1,green=2
	color1 c11 =  red ; 
	// color1 c12 = 1; 不能使用整型作为枚举型进行赋值
	// c11 = c11 + 1; 枚举类型自身没有算术运算
	//color1 c14 = blue + red; 枚举之间的算术计算也是非法的
	cout <<"c11="<< c11 << endl; // c1 = 1 
	int c13 = red + 4; // 枚举型可以参与整型运算

	
	enum color2 { blue1 = 0, red1 = 2, green1 = 4 ,gray1=-6};// 显式的定义枚举值,指定值必须是整数
	enum color3 {blue2,red2,green2=1,gray2=1}; // 枚举值相同也可以
	color2 c21;
	c21 = color2(-65536); // 虽然6不是color1的枚举值,但是在范围内也是合法的
	/*
	枚举值范围的计算：
	上限：找到1个2的最小幂数使之大于最大枚举值+1，然后再减去1，如2^4>8+1，上限为16-1=15
	下限：如果枚举值没有小于0的则下限为0，否则找到1个负的2的最大幂数使之小于最小枚举值，然后+1,如-2^3<-6-1,下限为-8+1=-7
	不过从调试结果来看，范围似乎没有上下限
	*/
	cout << "c21=" << c21 << endl;
}