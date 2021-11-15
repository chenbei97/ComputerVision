#include "primary.h"
using namespace cv;
void image_linear_filtering()
{
	// 常见算子
	// robert算子[1,0][0,-1]，[0,1][-1,0]
	// sobel算子[-1,0,1][-2,0,2][-1,0,1] 或 [-1,-2,-1][0,0,0][1,2,1]
	// 拉普拉斯算子 [0,-1,0][-1,4,-1][0,-1,0]
	Mat src = imread(imgAddr + "apple.jpg"), dst1,dst2;
	Mat kernel1 = (Mat_<float>(3, 3) << 0, -1, 0, -1, 4, -1, 0, -1, 0);
	Mat kernel2 = Mat::ones(Size(3, 3), CV_32F) / 9; 
	//Mat_< double > ( 3,3 )只是构建显式Mat的一种方法
	double delta = 0;
	filter2D(src, dst1, -1, kernel1,Point(-1,-1),delta,4); // delta参数是计算出来的像素+delta
	filter2D(src, dst2, -1, kernel2, Point(-1, -1), delta, 4);
	bitwise_not(dst1,dst1);
	//bitwise_not(dst2, dst2);
	imshow("dst1",dst1);
	imshow("dst2", dst2);
	waitKey(0);
	destroyAllWindows();
}