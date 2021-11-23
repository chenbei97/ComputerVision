#include "primary.h"
using namespace cv;
#include <vector>
void image_rectangularand_circular_boxes()
{
	/*
	轮廓周围绘制矩形
	基于RDP算法实现，目的是减少多边形轮廓点数
	void approxPolyDP( InputArray curve,
								OutputArray approxCurve,
								double epsilon, bool closed );
	curve：来自于findContours的某一条轮廓的点集合
	approxCurve：RFP算法输出的点集合,和输入相同
	epsilon：指定原始曲线与其近似值之间的最大距离
	closed：是否闭合

	Rect boundingRect( InputArray array );
	该函数计算并返回指定点集或灰度图像非零像素的最小右上边界矩形
	输入可以是findContours得到的点集合,也可以是RDP进一步筛选后的点集合，总之是1个容器

	void minEnclosingCircle( InputArray points,
									  CV_OUT Point2f& center, CV_OUT float& radius );
	points：输入的点集合
	center：圆心坐标存储容器
	radius：半径存储容器
	该函数使用迭代算法查找二维点集的最小封闭圆

	RotatedRect minAreaRect( InputArray points );
	返回一个旋转的矩形中心、角度等

	RotatedRect fitEllipse( InputArray points );
	返回最小椭圆，但是点集合至少5个点

	double minEnclosingTriangle( InputArray points, CV_OUT OutputArray triangle );
	函数找到一个最小面积的三角形，该三角形包围给定的2D点集，并返回其面积
	二维点用*红色*表示，封闭三角形用*黄色表示*
	Output vector of three 2D points defining the vertices of the triangle. The depth
	of the OutputArray must be CV_32F.
	*/
	Mat src = imread(imgAddr + "shape.jpg"),gray,canny; //balloon.jpg
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

	// 使用RDP算法减少轮廓点
	std::vector<std::vector<Point>>contours_approxPoly(contours.size());
	double epsilon = 3; //原始曲线与其近似值之间的最大距离
	bool closed = true;
	for (int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(contours[i] , contours_approxPoly[i],epsilon,closed);
		//std::cout << "contours：" << contours[i] << std::endl;
		//std :: cout << "contours_approxPoly：" <<contours_approxPoly[i] << std::endl;
	}
	std::vector<Rect> rects(contours_approxPoly.size()); // 矩形区域
	std::vector<Point2f> centers(contours_approxPoly.size()); //  多个圆区域的圆心
	std::vector<float> radiuses(contours_approxPoly.size()); // 注意必须要指定容器的容量
	std::vector<RotatedRect> ellipses(contours_approxPoly.size());// 椭圆区域

	std::vector<RotatedRect> minRects(contours_approxPoly.size()); // 最小矩形区域
	Point2f pts[4]; // 4个点：坐标+宽高
	
	std::vector<std::vector<Point2f>> triangles(contours_approxPoly.size());// 三角形区域,一个容器存放3个点坐标
	for (int i = 0; i < contours_approxPoly.size(); i++)
	{
		for (int j = 0 ; j < 3 ; j++)
			triangles[i].push_back(Point2f(CV_32F));
	}

	for (int i = 0; i < contours_approxPoly.size(); i++)
	{
		rects[i] = boundingRect(contours_approxPoly[i]);// 把筛选后的点集合赋值给容器
		// std::cout << "i = " << i << "   rect = "<< rects[i] << std::endl; // 每个轮廓返回1个点坐标和宽高对象
		// [669 x 521 from (0, 0)]
		minEnclosingCircle(contours_approxPoly[i],centers[i],radiuses[i]);
		
		//ellipses[i] = fitEllipse(contours_approxPoly[i]);
		// There should be at least 5 points to fit the ellipse
		//std::cout << "i = " << i << "    ellipses[i].center = "<<ellipses[i].center <<"   ellipses[i].angle = " << ellipses[i].angle << std::endl;
		
		minRects[i] = minAreaRect(contours_approxPoly[i]);
		//std::cout << "i = " << i << "    minRects[i].center = " << minRects[i].center << "   ellipses[i].angle = " << minRects[i].center << std::endl;
		minRects[i].points(pts);
		std::cout << "i = " << i << "   pts = " << *pts << std::endl;


		//minEnclosingTriangle(contours_approxPoly[i], triangles[i]);
		//std::cout << "i = " << i << "    triangles[i]= " << triangles[i]<< std::endl;
		
	}

	// 依据返回的必要参数绘制矩形和圆形
	for (int i = 0; i < contours_approxPoly.size(); i++)
	{
		rectangle(src,rects[i],Scalar(0,0,255),2,8,0);
		circle(src,centers[i],radiuses[i],Scalar(0,255,0),2,8,0);
		for (int r = 0; r < 4; r++)
		{
			line(src,pts[r],pts[(r+1)%4],Scalar(255,0,0),2,8,0);
		}
	}
	imshow("src",src);
	waitKey(0);
	destroyAllWindows();
}