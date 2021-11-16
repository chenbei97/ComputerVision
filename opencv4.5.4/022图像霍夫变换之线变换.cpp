#include "primary.h"
#include <vector>
using namespace cv;
void image_hough_transform_line()
{
	// 前提条件边缘检测已经完成 
	// 原理：平面空间转换为极坐标空间
	// 直线上的点变换到极坐标空间可以得到一个距离R
	// 同一直线的点(R,theta)群会有一个最强的信号(像素强度),根据此反算到平面坐标从而得到直线
	// HoughLines ：霍夫变换，返回霍夫空间(theta,R)
	// HoughLinesP：直线概率，并返回直线的两点
	Mat src = imread(imgAddr + "line.jpg"), dst;
	Mat gray;
	unsigned short int thresh = 100;
	Canny(src,gray, thresh,  2 * thresh );
	std::vector<Vec4f> lines1; // 返回的是2个点,也就是4个值
	std::vector<Scalar> lines2;
	double rho = 1; // 生成极坐标时像素的扫描步长
	double theta= CV_PI / 180.0; // 生成极坐标时的角度步长，一般取CV_PI/180
	double srn = 0.0 ,stn =0.0; // 是否应用多尺度的霍夫变换,不是设置0表示经典霍夫变换
	double  min_theta=0, max_theta=CV_PI; // 默认角度扫描范围为0-180°
	int threshold = 10; // 交点数目阈值,只有获得足够交点的极坐标才能看成直线
	double minLineLength = 0; // 最小线长
	double maxLineGap = 0; // 最大的线间距
	HoughLinesP(gray,lines1,rho,theta,threshold,minLineLength,maxLineGap);// 输入必须是8位灰度图像
	HoughLinesP(gray, lines2, rho, theta, threshold, minLineLength, maxLineGap);
	std::vector<Vec4f> ::const_iterator  it; // 可以防止修改原有值
	RNG rng;
	for (it = lines1.begin(); it != lines1.end(); it++)
	{
	   Vec4f T1;
	   T1 = *it;
		std::cout << T1<< "		" << T1[0] <<"	" << T1[1] << std::endl;
		line(src,Point(T1[0],T1[1]),Point(T1[2],T1[3]),Scalar(rng.uniform(0,255),rng.uniform(0,255),255),2); // 返回的这些线的坐标确实正确
	}
	Mat src_T;
	bitwise_not(src, src_T);
	std::cout << "T2：" << std::endl;
	Mat src_ = src.clone();
	for (std::vector<Scalar>::const_iterator it1 = lines2.begin(); it1 != lines2.end(); it1++)
	{
		Scalar T2;
		T2 = *it1;
		std::cout << T2[0] << std :: endl; // 从结果来看 使用Scalar接收也是可以的
		line(src_, Point(T2[0], T2[1]), Point(T2[2], T2[3]), Scalar(rng.uniform(0, 255), rng.uniform(0, 255), 255), 2);
	}
	Mat src_TT;
	bitwise_not(src_, src_TT);
	//imshow("src_T", src_T);
	//imshow("src_TT", src_TT); // 完全证明使用Vec4f和Scalar结果是一样的


	Mat input = imread(imgAddr + "line1.jpg");
	Mat canny;
	Canny(input,canny,50,100);
	threshold = 1;
	srn = 0;
	std::vector<Vec2f> lines; 
	HoughLines(canny, lines, theta, threshold, srn, stn, min_theta, max_theta);
	std::cout << "T3：" << lines.size() << std::endl;
	for (size_t i = 0; i < lines.size(); i++) // 另一种遍历方式
	{
		//size_t是标准C库中定义的，在64位系统中为long long unsigned int
		Vec2f T3 = lines[i]; // 返回的是theta , r  这里没出现结果
		 // r = cos(theta)*x + sin(theta)*y
		std::cout << T3 <<"   "<< T3[0] <<"   " << T3[1] << std::endl;
		/*line()*/
	}
	imshow("canny", canny);
	waitKey(0);
	destroyAllWindows();
}