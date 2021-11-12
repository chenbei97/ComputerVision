#include "function.h"
using namespace cv;
// <1>bitwiseÏµÁÐº¯Êý
void image_bitwise();
void image_convertTo();
void image_functions_using(const std :: string str)
{
	if (str == "bitwise")
	{
		image_bitwise();
	}
	else if (str == "convertTo")
	{
		image_convertTo();
	}
	//{
	//
	//}
	//else
	//{
	//}
	

}
void image_bitwise()
{
	Mat src = imread("D:/VisualStudioItems/apple.jpg", IMREAD_COLOR);
	Mat dst;
	bitwise_not(src, dst);
	//bitwise_and 
	//bitwise_or
	//bitwise_xor
	imshow("src", src);
	imshow("dst", dst);
	waitKey(0);
	destroyAllWindows();
}
void image_convertTo()
{
	Mat src = imread("D:/VisualStudioItems/apple.jpg", IMREAD_COLOR);
	Mat dst;
	src.convertTo(dst , CV_32FC3);
	//std::cout << src << std::endl;
	std::cout << dst << std::endl;

}