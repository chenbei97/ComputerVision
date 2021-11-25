#include "primary.h"
using namespace cv;
#include <vector>
void image__feature_detection_lbp()
{
	/*
		点、平坦区、线、边缘、角点
	
	*/
	Mat src = imread(imgAddr + "me.jpg"), gray; // ronaldo.png
	cvtColor(src, gray, COLOR_BGR2GRAY);
	int width = gray.cols;
	int height = gray.rows;

	Mat dst = Mat::zeros(height-2,width-2,CV_8UC1);
	for (int row = 1; row < height - 1; row++)
	{
		for (int col = 1; col < width - 1; col++)
		{
			uchar c = gray.at<uchar>(row, col);
			uchar code = 0;
			code |= (gray.at<uchar>(row - 1, col - 1) > c) << 7;
			code |= (gray.at<uchar>(row - 1, col - 0) > c) << 7;
			code |= (gray.at<uchar>(row - 1, col + 1) > c) << 7;
			code |= (gray.at<uchar>(row - 0, col + 1) > c) << 7;
			code |= (gray.at<uchar>(row + 1, col + 1) > c) << 7;
			code |= (gray.at<uchar>(row + 1, col - 0) > c) << 7;
			code |= (gray.at<uchar>(row + 1, col - 1) > c) << 7;
			code |= (gray.at<uchar>(row + 0, col - 1) > c) << 7;
			dst.at<uchar>(row - 1, col - 1) = code;
		}
	}
	imshow("src", src);
	imshow("dst", dst);
	waitKey(0);
	destroyAllWindows();
}