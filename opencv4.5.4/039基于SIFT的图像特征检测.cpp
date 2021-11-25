#include "primary.h"
using namespace cv;
#include <vector>
void image_feature_detection_sift()
{
	/*
		建立尺度空间寻找极值->关键点定位(寻找关键点位置与删除弱边缘)->关键点方向指定->关键点描述子
		构建图像高斯金字塔求DOG，每一层发现最大和最小值
		构建的高斯金字塔每一层根据sigma的不同至少可以分为4个等级

		static Ptr<SIFT> (int nfeatures = 0, int nOctaveLayers = 3,
		double contrastThreshold = 0.04, double edgeThreshold = 10,
		double sigma = 1.6);
	
	*/
	Mat src = imread(imgAddr + "tajmahal.jpg"), gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	int nfeatures = 0;
	int nOctaveLayers = 3;
	double contrastThreshold = 0.04;
	double edgeThreshold = 10;
	double sigma = 1.6;
	Ptr<cv::SIFT> detector = cv::SIFT::create
							(nfeatures, nOctaveLayers, contrastThreshold, edgeThreshold, sigma);
	std::vector<KeyPoint> kps;
	detector->detect(src, kps, Mat()); // 检测关键点
	std::cout << "kps.size() = " << kps.size() << "   kps[0].pt = " << kps[0].pt << std::endl;
	Mat kps_img;
	drawKeypoints(src, kps, kps_img, Scalar(0, 0, 255));
	for (size_t i = 0; i < kps.size(); i++)
	{
		if (i <5000) // 自行画圆
		{
			Point2f center = kps[i].pt;
			circle(src, center, 3, Scalar(255, 0, 0), 2, 8, 0);
		}
	}
	imshow("src", src);
	imshow("kps_img", kps_img); // 利用API画圆
	waitKey(0);
	destroyAllWindows();
}