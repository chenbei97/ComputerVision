#include <iostream>
#include <vector>
#include "chapter1_illegalInputData.h"
#include "chapter6_point2D.h"
/*
凸包涉及到秃多边形的概念：要求多边形(3条边及以上)任意两个端点的连线不能包含多边形其它端点，否则就是非秃多边形
对于包含多个点的点集合，找到一个最小秃多边形能够包含所有的点，就是求解凸包问题，在凸包上的点称为极点。
凸包的核心有2个操作。第1个是对这些点进行标号，标号依据初始点的垂线与其它点逆时针对的角度大小进行升序，存入双向链表；
第2个是依据定理：如果按标号顺序连续的3个点，第1个点x到第3个点rrx之间的逆时针夹角小于180°，说明第2个点rx不是极点，则链表删除这个点
否则第2个点可能是极点也可能不是极点需要进一步判断，整体移动x、rx和rrx的位置。
求解凸包的伪码如下，点集合为S：
if(S.size() < 3)
	return s ;
double k = (s[1].y-s[0].y)/(s[1].x-s[1].x) ; // 任取2个点计算斜率
double b = s[1].y - k * s[1].x ;
bool isCollinear = true; //默认共线
for(int i=2 ; i < S.size() ; i++)
{
	if (S[i].y != k*S[i].x+b)
		isCollinear =false ; // 只有有这样1个点不在方程上就不共线
}
if (isCollinear == true)
	// 找到最大的y和最小的y或者最大的x和最小的x就是共线的两个端点
	double max_x=0 , min_x=0 ; // 初始位置
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
	// 按极角排序
	// 1.找到1个点X,这个点X是参考原点坐标,X的垂线和每一个点都有一个夹角就是极角
	vector<double> angles; //升序存储极角
	// 2.遍历计算极角
	for (int i = 0 ; i < S.size() ; i++)
	{
		double y_delta = s[i].y - X.y ;
		double x_delta = s[i].x - X.x;
		double theta = arctan(x_delta/y_delta) ;
		angles.push_back(theta);
	}
	// 3.利用极角进行排序，先得到排序位置，用排序位置去排点集合的双向链表
	// 使用第2章排序法时间复杂度O(n^2)，使用第9/14章时间复杂度O(nlogn)
}
// 从y坐标是最小的点(p)开始遍历或者x坐标最大的点也可以，可以保证该点一定是极点
min_y = 0;
for(int i =0 ; i<S.size();i++)
{
	if (S[i].y < S[min_y])
		min_y = i ;
}
p = S[min_y];
// 删除非极点的点 时间复杂度O(n)
for (x = p,rx = x右边的点;p!=rx;)
{
	rrx = rx右边的点;
	if (x,rx,rrx的逆时针夹角小于等于180°)
	{
		链表eraserx;
		rx = x ; x = rx左边的点 ;// 链表反向移动
	}
	else {x = rx ; rx = rrx ;} //链表前向移动
}
*/
using namespace std;
template<class T1,class T2>
void _chapter6_calTriangleArea_by_Helen(const vector<T1> & Points,T2 & area);
void _chapter6_convex_hull()
{
	// test Helon formula 
	typedef _chapter6_point2D<double> Point2d;
	Point2d p1; // 默认构造
	cout << p1.x << "   " << p1.y << endl;
	Point2d p2(1.0, 1.2); // 参数构造
	cout << p2.x << "   " << p2.y << endl;
	double x0 = 1.0, y0 = 1.2;
	Point2d p3(x0, y0);// 参数构造
	cout << p3.x << "   " << p3.y << endl;
	Point2d p4(p3);
	cout << p4.x << "   " << p4.y << endl; // 复制构造
	// 3个点作为三角形顶点坐标,面积应当为1
	vector<Point2d> points = { Point2d(0, 2), Point2d(2, 0), Point2d(0,0) ,Point2d(1,1)};
	double area;
	_chapter6_calTriangleArea_by_Helen(points,area);
	cout << "area = " << area << endl;
}
template<class T1, class T2>
void _chapter6_calTriangleArea_by_Helen(const vector<T1>& Points, T2 &area)
{
	try
	{
		if (Points.size() != 3)
		{
			throw illegalInputData("Points.size() must be = 3");
		}
		// 海伦公式s=sqrt[p(p-a)(p-b)(p-c)],其中p=(a+b+c)/2,a,b,c是三角形边长
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