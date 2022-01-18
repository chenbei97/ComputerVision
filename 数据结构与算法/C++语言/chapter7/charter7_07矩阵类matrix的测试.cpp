#include "charter7_matrix.h"
void _charter7_matrix_testCode()
{
	try
	{
		matrix<int> u(3,3) ,v(4,4) ,p; // 
		// p = 3 + p; // ���� 3+A���� ��δ��ʼ����
		u = 100;
		u = 3 + u; // ��ʼ����sizeƥ�䲻�ᱨ��
		//v = 3 + u; // size��ƥ��
		cout << "u is" << endl;
		cout << u << endl;
		// v = u; �ߴ粻ͬ������Ȼᱨ��

		matrix<int> a1;// δ��ʼ��ʱ���²������Ƿ�
		//a1 = a1 + 5;  NotInitialized
		// a1 = a1 - 5;NotInitialized
		//a1 = 2;NotInitialized
		// a1 = u; sizeMisMatch
		//a1 = 3 + a1;  NotInitialized
		// a1 = 3 + u; sizeMisMatch

		//matrix<int> x(3, 2), y, z;
		matrix<double> x(3, 2), y, z; // ����Ĭ�Ϲ���Ͳ�������
		int i, j;
		for (i = 1; i <= 3; i++) // ����С�궼�Ǵ�1��ʼ��
			for (j = 1; j <= 2; j++)
				 x(i, j) = 2 * (double)i + (double)j +0.2; // ����(i,j)����
				//x(i, j) = 2 * i + j + 0.2;
		cout << "x is" << endl;;
		cout << x << endl;
		cout << "output1 is" << endl;
		output1(x);
		cout << "output2 is" << endl;
		x.output2();
		cout << "output3 is" << endl;
		output3(x);
		// ��������(i,j)
		cout << "y(1, 1) = " << y(1, 1) << endl; // ���о���,
		cout << "x.rows() = "<<x.rows() << "  x.cols() = " << x.cols() << endl;
		cout << "x(1, 1) = "<< x(1, 1) << endl;
		x(1, 1) = 2.5; // Ԫ�ظ�ֵ��������
		cout << "x(1, 1) = " << x(1, 1) << endl;
		cout << x << endl;
		// ���Ը��ƹ���
		matrix<double> w(x);
		cout << "w(x) is" << endl;;
		cout << w << endl;

		// ����ת�ú���transpose()
		matrix<double> g;
		g = w.transpose();
		cout << "w.T is" << endl;;
		cout << g << endl;
		// ����ת�ú���t()
		g.t();
		cout << "w.T.T is" << endl;;
		cout << g << endl;

		// ���������= ���� A=B
		y = w; // 
		cout << "y = w is" << endl;;
		cout << y << endl;
		y = y; // �Լ������Լ�ʱ����ִ���ڲ��ĸ�ֵ����

		// ���������= ���� A=5
		y = 5.1;
		cout << "y = 5.1 is" << endl;;
		cout << y << endl;

		// ���������+���� A+B
		y = y + y;
		cout << "y + y = " << endl;;
		cout << y << endl;

		// ���������+���� A+5
		y = y + 5;
		cout << "y = y+5 is" << endl;;
		cout << y << endl;

		// ���������+���� 5+A
		y = 0.8 + y;
		cout << "y = 0.8+y is" << endl;;
		cout << y << endl;

		// ���������-���� A-B
		matrix<double> e(3, 2) ;
		e = 1;
		y = y - e;
		cout << "y - e is" << endl;;
		cout << y << endl;
		
		// ���������-���� -A
		cout << "-y is" << endl;;
		cout << -y << endl;
		
		// ���������-���� A-5
		y = y - 8.2; // ���ǻᱻǿ��Ϊint��
		cout << "y - 8.2  is" << endl;;
		cout << y << endl;
		
		// ���������-���� 5-A
		y = 5.8 - y;
		cout << "5.8 - y  is" << endl;;
		cout << y << endl;
		
		// ����+= ���� A+=5,A-=5
		matrix<double> L;
		//L += 3; +=����Ҫ��ʼ������ -=ͬ��
		y += 3;
		y -= 1;
		y *= 2;
		y /= 3;
		cout << "y+=/-=/*=//= is" << endl;
		cout << y << endl;
		y++;
		y++;
		y--;
		
		// ����++ --
		cout << "y++,y++,y-- is " << endl;
		cout << y << endl;
		
		// ���Ծ���˷�
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