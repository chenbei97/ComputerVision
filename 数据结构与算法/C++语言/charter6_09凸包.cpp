#include <iostream>
#include <vector>
#include "charter1_illegalInputData.h"
#include "charter6_point2D.h"
/*
͹���漰��ͺ����εĸ��Ҫ������(3���߼�����)���������˵�����߲��ܰ�������������˵㣬������Ƿ�ͺ�����
���ڰ��������ĵ㼯�ϣ��ҵ�һ����Сͺ������ܹ��������еĵ㣬�������͹�����⣬��͹���ϵĵ��Ϊ���㡣
͹���ĺ�����2����������1���Ƕ���Щ����б�ţ�������ݳ�ʼ��Ĵ�������������ʱ��ԵĽǶȴ�С�������򣬴���˫������
��2�������ݶ�����������˳��������3���㣬��1����x����3����rrx֮�����ʱ��н�С��180�㣬˵����2����rx���Ǽ��㣬������ɾ�������
�����2��������Ǽ���Ҳ���ܲ��Ǽ�����Ҫ��һ���жϣ������ƶ�x��rx��rrx��λ�á�
���͹����α�����£��㼯��ΪS��
if(S.size() < 3)
	return s ;
double k = (s[1].y-s[0].y)/(s[1].x-s[1].x) ; // ��ȡ2�������б��
double b = s[1].y - k * s[1].x ;
bool isCollinear = true; //Ĭ�Ϲ���
for(int i=2 ; i < S.size() ; i++)
{
	if (S[i].y != k*S[i].x+b)
		isCollinear =false ; // ֻ��������1���㲻�ڷ����ϾͲ�����
}
if (isCollinear == true)
	// �ҵ�����y����С��y��������x����С��x���ǹ��ߵ������˵�
	double max_x=0 , min_x=0 ; // ��ʼλ��
	for (int i=1;i<S.size();i++)
	{
		if (S[i].x>s[max_x])
			max_x = i ;
		if (S[i].x<s[min_x])
			min_x = i ;
	}
	return s[max_x],s[min_x]
else
{
	// ����������
	// 1.�ҵ�1����X,�����X�ǲο�ԭ������,X�Ĵ��ߺ�ÿһ���㶼��һ���нǾ��Ǽ���
	vector<double> angles; //����洢����
	// 2.�������㼫��
	for (int i = 0 ; i < S.size() ; i++)
	{
		double y_delta = s[i].y - X.y ;
		double x_delta = s[i].x - X.x;
		double theta = arctan(x_delta/y_delta) ;
		angles.push_back(theta);
	}
	// 3.���ü��ǽ��������ȵõ�����λ�ã�������λ��ȥ�ŵ㼯�ϵ�˫������
	// ʹ�õ�2������ʱ�临�Ӷ�O(n^2)��ʹ�õ�9/14��ʱ�临�Ӷ�O(nlogn)
}
// ��y��������С�ĵ�(p)��ʼ��������x�������ĵ�Ҳ���ԣ����Ա�֤�õ�һ���Ǽ���
min_y = 0;
for(int i =0 ; i<S.size();i++)
{
	if (S[i].y < S[min_y])
		min_y = i ;
}
p = S[min_y];
// ɾ���Ǽ���ĵ� ʱ�临�Ӷ�O(n)
for (x = p,rx = x�ұߵĵ�;p!=rx;)
{
	rrx = rx�ұߵĵ�;
	if (x,rx,rrx����ʱ��н�С�ڵ���180��)
	{
		����eraserx;
		rx = x ; x = rx��ߵĵ� ;// �������ƶ�
	}
	else {x = rx ; rx = rrx ;} //����ǰ���ƶ�
}
*/
using namespace std;
template<class T1,class T2>
void _charter6_calTriangleArea_by_Helen(const vector<T1> & Points,T2 & area);
void _charter6_convex_hull()
{
	// test Helon formula 
	typedef _charter6_point2D<double> Point2d;
	Point2d p1; // Ĭ�Ϲ���
	cout << p1.x << "   " << p1.y << endl;
	Point2d p2(1.0, 1.2); // ��������
	cout << p2.x << "   " << p2.y << endl;
	double x0 = 1.0, y0 = 1.2;
	Point2d p3(x0, y0);// ��������
	cout << p3.x << "   " << p3.y << endl;
	Point2d p4(p3);
	cout << p4.x << "   " << p4.y << endl; // ���ƹ���
	// 3������Ϊ�����ζ�������,���Ӧ��Ϊ1
	vector<Point2d> points = { Point2d(0, 2), Point2d(2, 0), Point2d(0,0) ,Point2d(1,1)};
	double area;
	_charter6_calTriangleArea_by_Helen(points,area);
	cout << "area = " << area << endl;
}
template<class T1, class T2>
void _charter6_calTriangleArea_by_Helen(const vector<T1>& Points, T2 &area)
{
	try
	{
		if (Points.size() != 3)
		{
			throw illegalInputData("Points.size() must be = 3");
		}
		// ���׹�ʽs=sqrt[p(p-a)(p-b)(p-c)],����p=(a+b+c)/2,a,b,c�������α߳�
		vector<double> lengths(3);
		T2 a = sqrt(pow(Points[0].x - Points[1].x, 2) + pow(Points[0].y - Points[1].y, 2));
		T2 b = sqrt(pow(Points[1].x - Points[2].x, 2) + pow(Points[1].y - Points[2].y, 2));
		T2 c = sqrt(pow(Points[2].x - Points[0].x, 2) + pow(Points[2].y - Points[0].y, 2));
		T2 p = (a + b + c) / 2;
		cout << "a = " << a << "  b = " << b << "  c = " << c <<"  p = "<<p<< endl;
		area = sqrt(p * (p - a) * (p - b) * (p - c));
	}
	catch(illegalInputData e)
	{
		e.outputMessage();
		return;
	}
}