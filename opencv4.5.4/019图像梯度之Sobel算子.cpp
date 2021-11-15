#include "primary.h"
using namespace cv;
void image_gradient_sobel()
{
	// 一阶导数梯度
	// 改进版本为Scharr函数
	// APT：输入、输出、图像深度、x方向导数阶数dx、y方向导数阶数dy、算子核大小ksize(必须是奇数)
	// scale、delta、boardType
	int dx=1, dy = 1;
	int ksize = 5;
	int depth = -1;
	Mat src = imread(imgAddr + "apple.jpg"), dst;
	GaussianBlur(src, src, Size(3, 3), 1.0, 0.0, 4); // sigmaX
	Mat gray;
	cvtColor(src,gray,COLOR_BGR2GRAY);
	/*
	 输出深度：
	 输入为CV_8U,输出为-1/CV_16S/CV_32F/CV_64F
	 CV_16U/CV_16S  --- > -1/CV_32F/CV_64F
	 CV_32F  --> -1/CV_32F/CV_64F
	 CV_64F --> -1/CV_64F
	*/
	int ddepth = CV_16S;//-1,CV_32F 图像深度是指存储每个像素所用的位数,也用于量度图像的色彩分辨率
	// 当ddepth = -1时，输出图像将具有与源相同的深度
	double scale = 1.0;
	double delta = 3.0;
	Mat temp, dst2;
	Sobel(gray,dst,ddepth,dx,0,ksize,scale,delta);
	Sobel(dst, dst, ddepth, 0, dy, ksize, scale, delta);
	// 用于实现对整个图像数组中的每一个元素 实现saturate(alpha*x+beta)
	double alpha = 1.0, beta = 0;
	temp = dst.clone();
	convertScaleAbs(dst,dst,alpha,beta);
	// 类似的out = saturate(α * im1 + β * im2 + gamma)
	
	addWeighted(temp, 1.0, temp, 0, 0, dst2,ddepth); // 图片大小必须一致

	Mat ddst;
	Scharr(gray, ddst, ddepth, dx, 0, scale, delta,4);//dx >= 0 && dy >= 0 && dx+dy == 1
	Scharr(ddst, ddst, ddepth, 0, dy, scale, delta,4);// 没有ksize参数
	convertScaleAbs(ddst, ddst, alpha, beta);
	imshow("dst",dst);
	imshow("dst2", dst2);
	imshow("ddst", ddst);
	waitKey(0);
	destroyAllWindows();
}