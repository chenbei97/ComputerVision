#include "primary.h"
using namespace cv;
#include <vector>
void image_geometric_central_moment()
{
	/*
	中心矩、几何矩与归一化中心矩

	Moments moments( InputArray array, bool binaryImage = false );
	binaryImage：是否为二值图像

	double contourArea( InputArray contour, bool oriented = false );
	contour：输入轮廓数据
	oriented：默认返回绝对值
	返回轮廓区域面积

	double arcLength( InputArray curve, bool closed );
	curve：输入曲线数据
	closed：曲线是否是闭合的
	返回轮廓曲线弧长

	提取边缘->发现轮廓->计算每个轮廓的中心(矩)、弧长和面积
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

	std::vector<Moments> contour_moments(contours.size());
	std::vector<Point2f> centers(contours.size());// 存储每个矩计算出来的中心位置
	bool binaryImage = false;
	bool oriented = false; // 计算面积返回绝对值
	bool closed = true;
	int radius = 100;
	for (size_t i = 0; i < contour_moments.size(); i++)
	{
		contour_moments[i] = moments(contours[i],binaryImage);
		float x0 = static_cast<float>(contour_moments[i].m10 / contour_moments[i].m00);
		// m10是一阶x方向矩,m01是一阶y方向矩,m00是零阶矩
		// x0 = m10/m00  ;  y0 = m01 / m00
		float y0 = static_cast<float>(contour_moments[i].m01 / contour_moments[i].m00);
		centers[i] = Point(x0,y0);
		std::cout << "centers[i] = " << centers[i] << std::endl;
		double area = contourArea(contours[i],oriented);
		double _length =arcLength(contours[i],closed);
		circle(src, centers[i], radius, Scalar(0, 0, 255), 2, 21, 0);
		std::cout << "area = " << area << "   length = " << _length << std::endl;
	}
	imshow("src",src);
	waitKey(0);
	destroyAllWindows();


	
}