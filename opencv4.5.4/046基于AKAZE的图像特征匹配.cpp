#include "primary.h"
using namespace cv;
#include <vector>
void image_feature_match_akaze()
{
	/*
	AOS构造尺度空间、Hessian矩阵特征点检测、方向指定一阶微分图像、描述子生成
	比SIFT、SURF更稳定、速度快、非线性空间
	*/
	Mat src = imread(imgAddr + "shape.jpg");
	Mat dst;
	int minHessian = 400;
	Ptr<cv::KAZE> detector = cv::KAZE::create(minHessian);
	std::vector<KeyPoint> kps;
	double t1 = getTickCount();
	detector->detect(src, kps, Mat());
	double t2 = getTickCount();
	double t = (t2 - t1) * 1000 / getTickFrequency();
	printf_s("花费时间：%f  ms", t);
	drawKeypoints(src,kps,dst,Scalar(0,0,255),DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	
	
	Mat src1 = imread(imgAddr + "goal1.png");
	Mat src2 = imread(imgAddr + "goal2.png");
	Mat dst1;
	Ptr<cv::AKAZE> detector1 = cv::AKAZE::create();
	std::vector<KeyPoint> kps1, kps2;
	Mat descriptors1, descriptors2;
	t1 = getTickCount();
	detector1->detectAndCompute(src1, Mat(), kps1, descriptors1);
	detector1->detectAndCompute(src2, Mat(), kps2, descriptors2);
	t2 = getTickCount();
	t = (t2 - t1) * 1000 / getTickFrequency();
	printf_s("花费时间：%f  ms", t);

	BFMatcher matcher(NORM_L2);
	std::vector<DMatch> matches;
	matcher.match(descriptors1, descriptors2, matches);
	drawMatches(src1, kps1, src2, kps2, matches, dst1);


	imshow("dst", dst);
	imshow("dst1", dst1);
	waitKey(0);
	destroyAllWindows();
}