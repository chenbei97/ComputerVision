#include "primary.h"
using namespace cv;
void image_blur()
{   // 线性滤波
	// 均值滤波、高斯滤波、中值滤波 blur and GaussianBlur and medianBlur
	Mat im = imread(imgAddr + "eagle.jpg");
	// blur 参数  是输入、输出、窗口横轴大小、纵轴大小，和锚点坐标
	// GaussianBlur 参数 是输入、输出、窗口大小size、sigmax、sigmay
	// medianBlur 对椒盐噪声好用 , 输入、输出、ksize，对核内的元素统计排序
	// 窗口大小为了避免选择问题，应当为奇数
	Mat im_blur, im_GaussianBlur, im_medianBlur;
	blur(im,im_blur,Size(11,11),Point(-1,-1),4);// 
	GaussianBlur(im,im_GaussianBlur,Size(11,11),11.0,11.0,4);
	medianBlur(im,im_medianBlur,13); // ksize > 1 and 奇数
	// 双边滤波参数：输入、输出、像素半径d(提供-1则根据最后一个参数计算)
	//  多少差值以内的像素会被计算、sigmaSpace(像素半径＞0,否则根据此参数计算像素半径)
	Mat im_bilateralFilter;
	int d = 15;
	double sigmaColor = 150;
	double sigmaSpace = 5;
	bilateralFilter(im,im_bilateralFilter,d, sigmaColor,sigmaSpace);
	namedWindow("ava", WINDOW_FREERATIO);
	namedWindow("gaussian", WINDOW_FREERATIO);
	namedWindow("median", WINDOW_FREERATIO);
	namedWindow("bilateral", WINDOW_FREERATIO);
	imshow("bilateral", im_bilateralFilter);
	imshow("ava", im_blur);
	imshow("gaussian", im_GaussianBlur);
	imshow("median", im_medianBlur);
	waitKey(0);
	destroyAllWindows();
}