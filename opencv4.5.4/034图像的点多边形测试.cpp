#include "primary.h"
using namespace cv;
#include <vector>
void image_pointer_in_polygon()
{
	/*
		�����һ�����Ƿ��ڶ�����ڲ�

		double pointPolygonTest( InputArray contour, Point2f pt, bool measureDist );
		measuredist�����Ϊtrue�ú������ƴӵ㵽��������ߵ��з��ž��룬Ҳ���Ƿ��ؾ���
		���򣬸ú����������Ƿ��������ڣ�����1��ʾ���ڲ�������0�ڱ߽��ϣ�����-1��ʾ���ⲿ

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
				std::cout << "����������" << std::endl;
			else if (result > 0)
				std::cout << "����������" << std::endl;
			else
				std::cout << "���ڱ߽���" << std::endl;
		}
		else
			std::cout <<"�õ㵽�����ľ���Ϊ��"<< result << std::endl;
		}

	
}