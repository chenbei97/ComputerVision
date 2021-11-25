#include "primary.h"
using namespace cv;
#include <vector>
void image_feature_match_flann_surf()
{
	/*
	 快速最近邻逼近搜索函数库
	*/
	Mat src1 = imread(imgAddr + "goal1.png");
	Mat src2 = imread(imgAddr + "goal2.png");
	Mat dst;
	int minHessian = 400;
	Ptr<xfeatures2d::SURF> detector = xfeatures2d::SURF::create(minHessian);
	std::vector<KeyPoint> kps1, kps2;
	Mat descriptors1, descriptors2;
	detector->detectAndCompute(src1, Mat(), kps1, descriptors1);
	detector->detectAndCompute(src2, Mat(), kps2, descriptors2);
	FlannBasedMatcher matcher;
	std::vector<DMatch> matches;
	matcher.match(descriptors1, descriptors2, matches);

	double minDist = 1000;
	double maxDist = 0;
	double dist;
	for (int i = 0; i < descriptors1.rows; i++)
	{
		dist = matches[i].distance;
		if (dist > maxDist)
		{
			maxDist = dist;
		}
		if (dist < minDist)
		{
			minDist = dist;
		}
	}
	printf_s("max_dist = %f     min_dist = %f" , maxDist,minDist);
	// max_dist = 0.547070     min_dist = 0.001776
	std::vector<DMatch> goodMatches;
	for (int i = 0; i < descriptors1.rows; i++)
	{
		dist = matches[i].distance;
		if (dist < max(maxDist , 0.001))
		{
			goodMatches.push_back(matches[i]);
		}
	}
	drawMatches(src1, kps1, src2, kps2, goodMatches, dst);

	imshow("dst", dst);
	waitKey(0);
	destroyAllWindows();
}