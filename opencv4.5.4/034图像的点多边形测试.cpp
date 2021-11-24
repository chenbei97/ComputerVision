#include "primary.h"
using namespace cv;
#include <vector>
void image_pointer_in_polygon()
{
	/*
		检测仪一个点是否在多边形内部

		double pointPolygonTest( InputArray contour, Point2f pt, bool measureDist );
		measuredist：如果为true该函数估计从点到最近轮廓边的有符号距离，也就是返回距离
		否则，该函数仅检查点是否在轮廓内，返回1表示在内部，返回0在边界上，返回-1表示在外部

	*/
	Mat src = imread(imgAddr + "shape.jpg"), gray, canny;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	blur(gray, gray, Size(3, 3), Point(-1, -1));
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
	
	
	Point2f test_point(100, 100);
	bool measuredist = true;
	double result;
	for (size_t i = 0; i < contours.size(); i++)
	{
		result = pointPolygonTest(contours[i],test_point,measuredist);
		if (measuredist == false)
		{
			if (result < 0)
				std::cout << "点在轮廓外" << std::endl;
			else if (result > 0)
				std::cout << "点在轮廓内" << std::endl;
			else
				std::cout << "点在边界上" << std::endl;
		}
		else
			std::cout <<"该点到轮廓的距离为："<< result << std::endl;
		}

	
}