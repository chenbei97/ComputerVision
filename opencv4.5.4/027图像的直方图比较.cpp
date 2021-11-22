#include "primary.h"
#include <vector>
#include <iostream>
using namespace cv;
std :: string  convertToString(double d);
void image_histogram_comparison()
{
	// 对输入的2个图像计算直方图H1和H2，归一化到相同的尺度空间
	// 计算H1、H2的距离比较相似程度，进而比较图像的相似程度
	// 比较方法：
	/*
	   Correlation ：相关性比较 HISTCMP_CORREL
	   Chi-Square：卡方比较 HISTCMP_CHISQR,HISTCMP_CHISQR_ALT
	   Intersection：十字交叉 HISTCMP_INTERSECT
	   Bhattacharyya distance ： 巴氏距离 HISTCMP_BHATTACHARYYA
	*/
	/*
	BGR->HSV
	计算直方图 归一化到0-1之间(y方向.也就是不同强度的频率)
	使用4种方法进行比较compareHist
	*/
	const std :: string imgName1 = "goal1.png";
	const std::string imgName2 = "goal2.png";
	Mat src1 = imread(imgAddr + "basketball1.jpg");
	Mat src2 = imread(imgAddr + "basketball2.jpg");
	//selectROI("win",src2,true,true);
	resize(src2,src2,src1.size());
	//cvtColor(src1, src1,COLOR_BGRA2RGB);
	//cvtColor(src2, src2, COLOR_BGRA2RGB);
	cvtColor(src1, src1, COLOR_BGR2HSV);
	cvtColor(src2, src2, COLOR_BGR2HSV);
	
	
	int channels[] = {2,1}; // 指明2个图像计算哪几个通道,图像1第3通道,图像2第2通道
	int* chan = channels;
	int dims = 1; // 直方图通道数 
	int nimages = 1; // 1个图像
	int histsize[] = {256,128}; // 256个bin 
	float range1[] = { 0,256 }; // 通道范围
	float range2[] = { 0,128 };
	const float* ranges[] = { range1 , range2 }; // 一个数组指针,数组内的元素是3个数组

	// 用于存储直方图的矩阵
	MatND dst1,dst1_, dst2;
	calcHist(&src1,nimages,&channels[0],Mat(),dst1,dims,histsize,ranges,true,false); 
	calcHist(&src1, nimages, channels, Mat(), dst1_, dims, histsize, ranges, true, false);
	//std::cout << dst1 << std::endl; // [1 x 256] 传入不同的通道可以分别得到首元素为6678，3177，1
	// std::cout << dst1_ << std::endl; // 结果一样，证明传递channels和传递&channels[0]是一样的
	// 进一步说明一次只能处理1个通道，而不是想象的函数内部会对channels++同时处理多个通道
	double alpha = 0, beta = 1; // 标准归一化
	// dst = (src - min(src)) * (beta - alpha) / [ max(src) - min(src)] + alpha
	normalize(dst1,dst1,alpha,beta,NORM_MINMAX,-1,Mat()); // 归一化到0-1
	calcHist(&src2, nimages, &channels[1], Mat(), dst2, dims, histsize, ranges, true, false);
	normalize(dst2, dst2, alpha, beta, NORM_MINMAX, -1, Mat());
	int method = HISTCMP_CORREL;
	double match_coeff = compareHist(dst1,dst2,HISTCMP_CORREL);
	std::cout << "match_coeff = " << match_coeff << std::endl;
	
	std::vector<int> methods = { HISTCMP_BHATTACHARYYA,HISTCMP_CHISQR,
		HISTCMP_CHISQR_ALT,HISTCMP_HELLINGER,HISTCMP_INTERSECT,HISTCMP_KL_DIV };
	for (std::vector<int> ::const_iterator it = methods.begin(); it != methods.end(); it++)
	{
		std::cout << compareHist(dst1, dst2, *it) << std::endl;
	}
	putText(src2, convertToString(match_coeff),Point(50,50),FONT_HERSHEY_SCRIPT_COMPLEX,1.5,Scalar(0,255,0),2,8);
	imshow("src1", src1);
	imshow("src2", src2);
	waitKey(0);
	destroyAllWindows();
}
std::string  convertToString(double d)
{
	std::ostringstream os;
	if (os << d)
		return os.str();
	else
		return "input is null";
}