#include "function.h"
using namespace cv;
const std::string imgAddr = "C:/Users/chenbei/Documents/Visual Studio 2019/ItemFiles/Opencv4/images/";
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
	else if (str == "rng_uniform")
	{
		image_rng_uniform();
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
void image_rng_uniform()
{
	// 随机数的使用
	Mat im = imread(imgAddr + "eagle.jpg");
	RNG rng(123);

	int line_num = 1000;
	for (int i = 0; i < line_num; i++)
	{
		Scalar color(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		Point p1(rng.uniform(0, im.cols), rng.uniform(0, im.rows));// 随机点坐标
		Point p2(rng.uniform(0, im.cols), rng.uniform(0, im.rows));// 随机点坐标
		if (waitKey(10) > 0)
			break;
		line(im, p1, p2, color, 2, 8);
		namedWindow("random_line", WINDOW_FREERATIO);
		imshow("random_line", im);
	}
	destroyAllWindows();
}
