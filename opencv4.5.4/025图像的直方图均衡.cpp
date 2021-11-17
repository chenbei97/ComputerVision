#include "primary.h"
using namespace cv;
void image_histogram_equalization()
{
	// 一种提高图像对比度的方法
	// 通过直方图可以知道不同强度的像素个数,提高较低和较高强度像素的数量可以提高对比度
	Mat src = imread(imgAddr + "apple.jpg"), dst;
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);//Assertion failed (scn == 1 && dcn == 1)

	equalizeHist(gray,dst);// src.type() == CV_8UC1 8位单通道灰度图
	imshow("gray",gray);
	imshow("dst", dst);
	waitKey(0);
	destroyAllWindows();

}