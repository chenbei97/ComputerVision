#include "primary.h"
using namespace cv;
void image_hough_transform_circle()
{
	// 原理：平面上属于圆的点转换到极坐标后C(x0,y0,r)方程处有极大值
	// 对噪声敏感，需要先中值滤波
	// 方法内部是基于图像梯度的实现，首先检测边缘发现可能的圆心
	// 然后从候选圆心计算对应最佳半径找到整圆
	Mat src = imread(imgAddr + "shape.jpg");
	std::cout << imgAddr + "shape.jpg" << std::endl;
	Mat msrc;
	medianBlur(src,msrc,3);
	Mat gray_src;
	cvtColor(msrc, gray_src, COLOR_BGR2GRAY);
	//if (src.empty() != 1)
	//	std::cout << "image load successful..." << std::endl;
	//else
	//{
	//	std::cout << "image null..." << std::endl;
	//	return;
	//}
	
	Mat gray;
	unsigned int threshold = 50 ;
	Canny(gray_src,gray, threshold, (double)threshold * 2);
	std::cout << "gray.empty() = " << gray.empty() << std :: endl; // =0 不为空
	int minR = 2, maxR = 200; // 圆处于的最小和最大半径
	double minDist = 2; //两个圆心之间的最短距离, 如果小于2认为是同心圆
	double param1 = (double)threshold * 2, param2 =30; // param1  边缘检测中edge使用的高阈值param2 中心点累加器阈值-候选圆心
	// 默认都是100
	int method = HOUGH_GRADIENT; // 检测方法，梯度最常用
	// HOUGH_GRADIENT_ALT,HOUGH_MULTI_SCALE,HOUGH_STANDARD
	double dp = 1;
	std::vector<Vec3f> circles; // 返回圆心坐标和R
	HoughCircles(gray, circles,method,dp,minDist ,param1,param2,minR,maxR);
	for (size_t i = 0; i < circles.size(); i++)
	{
		std::cout << circles[i] << std::endl;
		Point center(circles[i][0], circles[i][1]);
		double radius = circles[i][2];
		if ( radius > 120 && radius < 130)
			circle(src, center, radius, Scalar(0, 0, 255), 1);
	}
	imshow("gray", gray);
	imshow("src",src);
	waitKey(0);
	destroyAllWindows();

}