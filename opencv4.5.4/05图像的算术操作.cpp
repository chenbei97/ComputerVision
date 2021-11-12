#include "primary.h"
using namespace cv;

void image_arithmetic_operation()
{
	Mat src = imread("D:/VisualStudioItems/apple.jpg", IMREAD_COLOR);//IMREAD_GRAYSCALE
	int channels = src.channels();
	Mat newsrc = src - Scalar(50, 50, 50); // µ÷ÕûÁÁ¶È
	Mat msrc,dsrc,ssrc;
	multiply(src, Scalar(0.5), msrc);
	divide(src,Scalar(50, 50, 50) , dsrc);
	subtract(src,Scalar(50,50,50),ssrc);
	imshow("orgin", src);
	imshow("decrease", newsrc);
	imshow("multiply", msrc);
	imshow("subtract", ssrc);
	imshow("divide", dsrc);
	waitKey(0);
	destroyAllWindows();
}