#include "primary.h"
using namespace cv;
void image_fixed_adaptive_threshold_segmentation()
{
	// 固定阈值
	enum types {THRESH_BINARY, THRESH_BINARY_INV, 
		THRESH_TRUNC, THRESH_TOZERO, THRESH_TOZERO_INV};
	std::vector<Mat>dsts(5);
	Mat src = imread(imgAddr + "lena.jpg");
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	for (int i = 0; i < dsts.size(); i++)
	{
		threshold(gray, dsts[i], 150,255,types(i));
		imshow("dst"+std::to_string(i+1),dsts[i]);
	}
	// 使用自适应阈值
	// 方法可选2种,阈值类型只能选择THRESH_BINARY, THRESH_BINARY_INV = 0 , 1
	enum  adaptive_methods { ADAPTIVE_THRESH_GAUSSIAN_C, ADAPTIVE_THRESH_MEAN_C}; // 0 , 1
	double C = 2; // 块邻域中高斯加权和或者平均后的数减去该常数 
	const int maxval = 255;
	int blocksize = 11; // 邻域块大小一般取奇数(>3),计算邻域块的平均值或者高斯加权和最后减去该常数
	std::vector<Mat>adadsts(4);
	int count = 0;
	for (int method = 0; method < 2; method++)
	{
		for (int type = 0; type < 2; type++)
		{
			adaptiveThreshold(gray, adadsts[count], maxval,adaptive_methods(method),types(type),blocksize,C);
			imshow("adadst" + std::to_string(count + 1), adadsts[count]);
			count++;
		}
	}
	waitKey(0);
	destroyAllWindows();
}