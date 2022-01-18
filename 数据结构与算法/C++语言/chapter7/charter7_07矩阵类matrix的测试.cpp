#include "charter7_matrix.h"
void _charter7_matrix_testCode()
{
	try
	{
		matrix<int> u(3,3) ,v(4,4) ,p; // 
		// p = 3 + p; // 测试 3+A重载 报未初始化错
		u = 100;
		u = 3 + u; // 初始化且size匹配不会报错
		//v = 3 + u; // size不匹配
		cout << "u is" << endl;
		cout << u << endl;
		// v = u; 尺寸不同不能相等会报错

		matrix<int> a1;// 未初始化时以下操作均非法
		//a1 = a1 + 5;  NotInitialized
		// a1 = a1 - 5;NotInitialized
		//a1 = 2;NotInitialized
		// a1 = u; sizeMisMatch
		//a1 = 3 + a1;  NotInitialized
		// a1 = 3 + u; sizeMisMatch

		//matrix<int> x(3, 2), y, z;
		matrix<double> x(3, 2), y, z; // 测试默认构造和参数构造
		int i, j;
		for (i = 1; i <= 3; i++) // 矩阵小标都是从1开始的
			for (j = 1; j <= 2; j++)
				 x(i, j) = 2 * (double)i + (double)j +0.2; // 测试(i,j)重载
				//x(i, j) = 2 * i + j + 0.2;
		cout << "x is" << endl;;
		cout << x << endl;
		cout << "output1 is" << endl;
		output1(x);
		cout << "output2 is" << endl;
		x.output2();
		cout << "output3 is" << endl;
		output3(x);
		// 测试索引(i,j)
		cout << "y(1, 1) = " << y(1, 1) << endl; // 会有警告,
		cout << "x.rows() = "<<x.rows() << "  x.cols() = " << x.cols() << endl;
		cout << "x(1, 1) = "<< x(1, 1) << endl;
		x(1, 1) = 2.5; // 元素赋值操作测试
		cout << "x(1, 1) = " << x(1, 1) << endl;
		cout << x << endl;
		// 测试复制构造
		matrix<double> w(x);
		cout << "w(x) is" << endl;;
		cout << w << endl;

		// 测试转置函数transpose()
		matrix<double> g;
		g = w.transpose();
		cout << "w.T is" << endl;;
		cout << g << endl;
		// 测试转置函数t()
		g.t();
		cout << "w.T.T is" << endl;;
		cout << g << endl;

		// 测试运算符= 重载 A=B
		y = w; // 
		cout << "y = w is" << endl;;
		cout << y << endl;
		y = y; // 自己等于自己时不会执行内部的赋值操作

		// 测试运算符= 重载 A=5
		y = 5.1;
		cout << "y = 5.1 is" << endl;;
		cout << y << endl;

		// 测试运算符+重载 A+B
		y = y + y;
		cout << "y + y = " << endl;;
		cout << y << endl;

		// 测试运算符+重载 A+5
		y = y + 5;
		cout << "y = y+5 is" << endl;;
		cout << y << endl;

		// 测试运算符+重载 5+A
		y = 0.8 + y;
		cout << "y = 0.8+y is" << endl;;
		cout << y << endl;

		// 测试运算符-重载 A-B
		matrix<double> e(3, 2) ;
		e = 1;
		y = y - e;
		cout << "y - e is" << endl;;
		cout << y << endl;
		
		// 测试运算符-重载 -A
		cout << "-y is" << endl;;
		cout << -y << endl;
		
		// 测试运算符-重载 A-5
		y = y - 8.2; // 还是会被强制为int型
		cout << "y - 8.2  is" << endl;;
		cout << y << endl;
		
		// 测试运算符-重载 5-A
		y = 5.8 - y;
		cout << "5.8 - y  is" << endl;;
		cout << y << endl;
		
		// 测试+= 重载 A+=5,A-=5
		matrix<double> L;
		//L += 3; +=是需要初始化过的 -=同理
		y += 3;
		y -= 1;
		y *= 2;
		y /= 3;
		cout << "y+=/-=/*=//= is" << endl;
		cout << y << endl;
		y++;
		y++;
		y--;
		
		// 测试++ --
		cout << "y++,y++,y-- is " << endl;
		cout << y << endl;
		
		// 测试矩阵乘法
		y = y * y;
		cout << "y*y is " << endl;
		cout << y << endl;
	}
	catch (matrixSizeNotInitialized e) 
	{
		e.outputMessage();
	}	
	catch (matrixIndexOutOfBounds e)
	{
		e.outputMessage();
	}
	catch (matrixSizeMismatch e)
	{
		e.outputMessage();
	}
	catch (...)
	{
		cerr << "Other exception has occurred" << endl;
	}
}