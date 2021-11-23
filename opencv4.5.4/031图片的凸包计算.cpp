#include "primary.h"
using namespace cv;
void image_convex_hull()
{
	/*
	一些点集合, 希望找到包含集合的最小凸多边形，即凸包：graham算法
	选择Y方向的最低点作为起始点，记为P0，开始极坐标扫描，依次添加P1、..Pn
	排序顺序依据极坐标角度的大小，逆时针方向
	对每个点Pi来说，添加该点导致凸包左转向时(逆时针)则可以添加，否则导致右转向则删除该点
	
	void convexHull( InputArray points, OutputArray hull,
                              bool clockwise = false, bool returnPoints = true );
	points：输入候选点，来自findContours
	clockwise：默认顺时针方向
	returnPoints：true表示返回点个数
	*/
	// 灰度图->canny边缘检测->寻找轮廓->凸包检测
	Mat src = imread(imgAddr + "shape.jpg"), gray, canny; 
	cvtColor(src, gray, COLOR_BGR2GRAY);
	blur(gray,gray,Size(3,3),Point(-1,-1));
	double threshold1 = 50;
	double threshold2 = 2 * threshold1;
	int  apertureSize = 3;
	bool L2gradient = true;
	Canny(gray, canny, threshold1, threshold2, apertureSize, L2gradient);
	std::vector<std::vector<Point>>contours;
	std::vector<Vec4i> hierarchy;
	int mode = RETR_TREE;
	int method = CHAIN_APPROX_SIMPLE;
	findContours(gray, contours, hierarchy, mode, method, Point(0, 0));
	for (size_t i = 0; i < hierarchy.size(); i++)
	{
		std::cout << hierarchy[i] << std::endl;
	}
	bool clockwise=false, returnPoints=true;
	std::vector<std::vector<Point>>hull(contours.size());
	for (size_t  i = 0; i < hull.size(); i++)
	{
		convexHull(contours[i], hull[i], clockwise, returnPoints);
	}
	
	Scalar color1(0, 0, 255);
	Scalar color2(0, 255, 0);
	int contourIdx;
	Mat src_ = src.clone();
	for (size_t i = 0; i < hull.size(); i++)
	{
		contourIdx = i;
		drawContours(src, hull, contourIdx, color1, 2, 8, hierarchy, 0, Point(0, 0));
		drawContours(src_, contours, contourIdx, color2, 2, 8, hierarchy, 0, Point(0, 0));
	}
	imshow("hull", src);
	imshow("contours", src_);
	waitKey(0);
	destroyAllWindows();
}