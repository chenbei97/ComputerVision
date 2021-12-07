#include "primary.h"
using namespace cv;
// 使用自适应阈值手动
enum adaptiveMethod { meanFilter, gaussianFilter, medianFilter };
void custom_adaptive_threshold(const Mat &src , Mat & dst , double maxval=255 ,double C=0 , double sigma = 0, Size size = Size(3,3),int method =meanFilter );
void image_fixed_adaptive_threshold_segmentation()
{
	// 固定阈值
	enum types {
		THRESH_BINARY, THRESH_BINARY_INV,
		THRESH_TRUNC, THRESH_TOZERO, THRESH_TOZERO_INV
	};
	std::vector<Mat>dsts(5);
	Mat src = imread(imgAddr + "lena.jpg");
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	for (int i = 0; i < dsts.size(); i++)
	{
		threshold(gray, dsts[i], 150, 255, types(i));
		imshow("dst" + std::to_string(i + 1), dsts[i]);
	}
	// 使用自适应阈值自动
	// 方法可选2种,阈值类型只能选择THRESH_BINARY, THRESH_BINARY_INV = 0 , 1
	enum  adaptive_methods { ADAPTIVE_THRESH_GAUSSIAN_C, ADAPTIVE_THRESH_MEAN_C }; // 0 , 1
	double C = 2; // 块邻域中高斯加权和或者平均后的数减去该常数 
	const int maxval = 255;
	int blocksize = 11; // 邻域块大小一般取奇数(>3),计算邻域块的平均值或者高斯加权和最后减去该常数
	std::vector<Mat>adadsts(4);
	int count = 0;
	for (int method = 0; method < 2; method++)
	{
		for (int type = 0; type < 2; type++)
		{
			adaptiveThreshold(gray, adadsts[count], maxval, adaptive_methods(method), types(type), blocksize, C);
			imshow("adadst" + std::to_string(count + 1), adadsts[count]);
			count++;
		}
	}
	std::vector<Mat>outputs(3);
	double sigma = 1.0;
	int subsize = 7;
	C = 10;
	for (int method = 0; method < 3; method++)
	{
		custom_adaptive_threshold(src, outputs[method], maxval, C, sigma,Size(subsize, subsize), adaptiveMethod(method));
		imshow("output" + std::to_string(method + 1), outputs[method]);
	}
	
	waitKey(0);
	destroyAllWindows();
}
void custom_adaptive_threshold(const Mat& src, Mat& dst, double maxval, double C, double sigma, Size size, int method )
{
	Mat gray;
	if (src.channels() > 1)
		cvtColor(src, gray, COLOR_BGR2GRAY);
	else
		gray = src.clone();
	Mat smooth;
	switch (method)
	{
	case 0: blur(gray, smooth, size); break;
	case 1: GaussianBlur(gray, smooth, size, sigma, 0); break;
	case 2: medianBlur(gray, smooth, size.width); break;
	default:break;
	}
	smooth = smooth - C;
	gray.copyTo(dst); // 复制一份数据
	for (int row = 0; row < src.rows; row++)
	{
		const uchar* psrc = src.ptr<uchar>(row);
		const uchar* psmooth= smooth.ptr<uchar>(row);
		uchar* psdst = dst.ptr<uchar>(row);
		for (int col = 0; col < src.cols; col++)
		{
			if (psrc[col] > psmooth[col])
				psdst[col] = maxval; //平滑以后的结果小于源图像时取为maxval
			else
				psdst[col] = 0;
		}
	}
}