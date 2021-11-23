#include "primary.h"
using namespace cv;
#include <vector>
void image_contour_detection()
{
	/*
	 void findContours( InputArray image, OutputArrayOfArrays contours,
                              OutputArray hierarchy, int mode,
                              int method, Point offset = Point());
	void findContours( InputArray image, OutputArrayOfArrays contours,
                              int mode, int method, Point offset = Point());
	image：输入的二值图像
	contours：返回的轮廓
	hierarchy：该图的拓扑结构，可选这样发现算法基于图像的拓扑结构实现
	method ：寻找轮廓的方法：CHAIN_APPROX_NONE、CHAIN_APPROX_SIMPLE、
	CHAIN_APPROX_TC89_KCOS、CHAIN_APPROX_TC89_L1
	mode：轮廓返回的模式：RETR_CCOMP、RETR_FLOODFILL、RETR_LIST
	RETR_TREE 、RETR_EXTERNAL
	offset：轮廓像素的位移(默认无位移)

	void drawContours( InputOutputArray image, InputArrayOfArrays contours,
						int contourIdx, const Scalar& color,
						int thickness = 1, int lineType = LINE_8,
						InputArray hierarchy = noArray(),
						int maxLevel = INT_MAX, Point offset = Point() );
	image：绘制的图像
	contours：findContours返回的全部轮廓对象
	contourIdx：轮廓索引号
	color：颜色
	thickness、lineType ：厚度、线型
	hierarchy：图的拓扑结构
	maxLevel：最大层数，0表示只绘制当前，1表示绘制当前及其内嵌的轮廓
	offset：偏置
	*/
	// 灰度图->canny边缘检测->寻找轮廓->绘制轮廓
	Mat src = imread(imgAddr + "shape.jpg"),gray,canny;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	double threshold1 = 50;
	double threshold2 = 2 * threshold1;
	int  apertureSize = 3;
	bool L2gradient = true;
	Canny(gray,canny,threshold1,threshold2,apertureSize,L2gradient);
	std :: vector<std :: vector<Point>>contours; // 轮廓可能有多条，每条轮廓有多个点
	std::vector<Vec4i> hierarchy; // 拓扑结构4个值即可确定，需要多组4值向量
	int mode = RETR_TREE;
	int method = CHAIN_APPROX_SIMPLE;
	findContours(gray,contours,hierarchy,mode,method,Point(0,0));
	RNG rng;
	// 可以使用线取绘制轮廓
	for (std::vector<std::vector<Point>>::const_iterator it = contours.begin(); it != contours.end(); it++)
	{
		std::vector<Point> contour = *it;
		//Scalar color = Scalar(rng.uniform(0,255) ,rng.uniform(0,255) ,rng.uniform(0,255) );
		Scalar color(0, 0, 255);
		for (size_t it1 =1 ; it1 < contour.size() ; it1++)
		{
			Point point1 = contour[it1-1];
			Point point2 = contour[it1];
			line(src,point1,point2,color,2);
			std::cout << "point1 = " << point1 << "	point2 = " <<point2 << std::endl;
		}
	}

	 //也可以利用绘制轮廓的轮廓索引号contourIdx绘制
	Mat src_ = src.clone();
	for (size_t i = 0; i < contours.size(); i++)
	{
		//Scalar color (rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		Scalar color(0, 255, 0);
		int contourIdx = i;
		drawContours(src_,contours, contourIdx,color,2,8,hierarchy,0,Point(0,0));
	}
	
	imshow("line",src);
	imshow("drawContours", src_);
	waitKey(0);
	destroyAllWindows();
	
}