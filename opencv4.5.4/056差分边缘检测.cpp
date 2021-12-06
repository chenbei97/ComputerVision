#include "primary.h"
using namespace cv;
void differential_edge_detection(const Mat& src,Mat & edgeX , Mat & edgeY);
void image_differential_edge_detection()
{
	Mat src = imread(imgAddr+"apple.jpg");
	Mat edgeX(src.size(),src.type());
	Mat edgeY(src.size(), src.type());
	differential_edge_detection(src,edgeX,edgeY);
	imshow("edgeX",edgeX);
	imshow("edgeY", edgeY);
	waitKey(0);
	destroyAllWindows();
}
void differential_edge_detection(const Mat& src, Mat& edgeX, Mat& edgeY)
{
	Mat temp = src.clone();
	for(int row =1 ;row<src.rows -1 ;row++) // row+1<=src.rows && row-1>=0
		for (int col = 1; col < src.cols - 1; col++) // col同理
		{
			for (int channel = 0; channel < src.channels(); channel++)
			{
				edgeX.at<uchar>(row, col) = abs(temp.at<uchar>(row + 1, col) - temp.at<uchar>(row - 1, col)) / 2; // 中心差分
				edgeY.at<uchar>(row, col) = abs(temp.at<uchar>(row, col + 1) - temp.at<uchar>(row, col - 1)) / 2;
			}
		}
}