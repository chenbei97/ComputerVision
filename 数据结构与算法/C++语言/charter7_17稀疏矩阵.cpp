#include <iostream>
#include "charter7_sparseMatrix.h"
using namespace std;
void _charter7_sparse_matrix()
{
	//sparseMatrix<int> a, b;
	//cout <<"a.nonZeroNum() = "<< a.nonZeroNum() << endl;
	//cout << "b.nonZeroNum() = " << b.nonZeroNum() << endl;
	//cout << "a.capacity() = " << a.capacity() << endl;
	//cout << "b.capacity() = " << b.capacity() << endl;
	//cin >> a;
	//cout << "Matrix a is" << endl << a;
	//b = a;  // 内部只是1个引用不会复制数据
	//cout << "Matrix b is" << endl << b;
	
	const int rows  = 60;
	const int cols = 20;
	const int size = 10;
	_charter6_point2D<int>  points[size] = {}; // 10个元素对应的坐标
	_charter6_point2D<int> point;
	for (int i = 0; i < size; i++)
	{
		point.x =  (1-i)*(i-13) +  15;
		point.y = i*i/2 + 6 - 3 * i ;
		cout << "point.x = " << point.x << "  point.y = " << point.y << endl;
		points[i] = point;
	}
	double value[size] = { 1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9,10.1 };
	try 
	{
		sparseMatrix<double> c(rows, cols, size, points, value);
		cout << "Matrix c is" << endl << c;
		
		sparseMatrix<double> d;
		d = c;
		cout << "after d = c  Matrix d is" << endl << d;
		cout << points[0].x << "   " << points[0].y << endl;
		cout <<"d("<<points[0].x <<","<< points[0].y<<") = "<< d(points[0].x, points[0].y) << endl;
		
		sparseMatrix<double> e;
		d.transpose(e);
		cout << "after d.transpose(e)  Matrix e is" << endl << e;
		
		sparseMatrix<double> f;
		e.t(f);
		cout << "after e.t(f)  Matrix f is" << endl << f;

		point.x = 15;
		point.y = 15;
		value[2] = -15;
		points[2] = point;
		sparseMatrix<double> g(rows, cols, size, points, value);
		cout << "Matrix g is" << endl << g;

		sparseMatrix<double> h;
		c.add(g, h);
		cout << "The sum of c and g is" << endl << h;

		sparseMatrix<double> k;
		c.add(f, k);
		cout << endl<<"The sum of c and f is" << endl << k;
		
		matrixTerm<double> term;
		term.col = 19;
		term.row = 59;
		term.value = -1.0;
		f.append(term);
		cout << "after f.append  Matrix f is" << endl << f; // 测试append函数

		sparseMatrix<double> m;
		c.add(f, m);
		cout << endl << "The sum of c and f.append is" << endl << m;

		sparseMatrix<double> n;
		g.append(term);
		c.add(g, n);
		cout << endl << "The sum of c and g.append is" << endl << n;

	}
	catch (matrixIndexOutOfBounds e) { e.outputMessage(); }

}