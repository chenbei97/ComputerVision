#include "primary.h"
using namespace cv;
Mat src=imread(imgAddr + "apple.jpg") , dst;
int maxval = 255;
int currval = 127;
int currtype = 0;
int max_threshold_type = 4;
const std::string barname1 = "thresholdValue";
const std::string barname2 = "thresholdType";
const std::string winname = "win";
void image_threshold_calculate_callback(int, void*);
void image_threshold_calculate()
{
	std::cout << THRESH_BINARY << THRESH_BINARY_INV << THRESH_TRUNC
		<< THRESH_TOZERO << THRESH_TOZERO_INV << std :: endl; // 0,1,2,3,4
	Mat gray;
	cvtColor(src,gray,COLOR_BGR2GRAY); // 必须灰度化
	Mat temp = Mat :: zeros(gray.size(), gray.type());
	double best_threshold = threshold(gray,temp,0,255,THRESH_OTSU | THRESH_BINARY); // 自动计算最佳阈值
	std::cout << "best_threshold(ostu) = " << best_threshold <<std::endl;// best_threshold = 115
	best_threshold = threshold(gray, temp, 0, 255, THRESH_TRIANGLE | THRESH_BINARY);
	std::cout << "best_threshold(triangle) = " << best_threshold << std::endl;// best_threshold = 172
	// THRESH_BINARY二值阈值：超过阈值等于255
	// THRESH_BINARY_INV反二值阈值：超过阈值等于0，其他为255
	// THRESH_TRUNC截断阈值：超过阈值等于阈值，其他不变
	//THRESH_OTSU：选择ostu算法自动计算最佳阈值
	// THRESH_MASK
	//THRESH_TRIANGLE ：使用triangle算法自动计算最佳阈值
	//THRESH_TOZERO零值化：超过阈值不变，其余为0
	//THRESH_TOZERO_INV反零值化：超过阈值为0，否则不变
	int* cval = &currval; // 阈值
	int* thresh = &currtype; // 阈值类型
	namedWindow(winname,WINDOW_FREERATIO);//必须有Assertion failed (scn == 1 && dcn == 1)
	createTrackbar(barname1,winname,cval,maxval, image_threshold_calculate_callback);
	createTrackbar(barname2, winname, thresh, max_threshold_type, image_threshold_calculate_callback);
	image_threshold_calculate_callback(0, 0);
	waitKey(0);
}
void image_threshold_calculate_callback(int,void*)
{
	Mat gray;
	cvtColor(src,gray,COLOR_BGR2GRAY);
	//threshold(gray,dst,currval,maxval,THRESH_BINARY); // 阈值当前值和最大值
	threshold(gray, dst, currval, maxval, currtype);
	std::cout << "current threshold type = " << currtype << "	current threshold value = " <<currval << std::endl;
	imshow(winname,dst);

}