#include "primary.h"
using namespace cv;
#include <vector>
void image_feature_match_brisk()
{
	/*
		构建尺度空间->特征点检测->Fast9-16寻找特征点->特征点定位->关键描述子
	*/
	Mat src = imread(imgAddr + "shape.jpg");
	Mat dst;
	std::vector<KeyPoint> kps;
	Ptr<Feature2D> detector = cv::BRISK::create();
	detector->detect(src,kps,Mat());
	drawKeypoints(src, kps, dst, Scalar::all(-1), DrawMatchesFlags::DEFAULT);

	Mat src1 = imread(imgAddr + "goal1.png");
	Mat src2 = imread(imgAddr + "goal2.png");
	Mat dst1;
	std::vector<KeyPoint> kps1, kps2;
	Mat descriptors1, descriptors2;
	BFMatcher matcher(NORM_L2);
	std::vector<DMatch> matches;
	detector->detectAndCompute(src1, Mat(), kps1, descriptors1);
	detector->detectAndCompute(src2, Mat(), kps2, descriptors2);
	matcher.match(descriptors1, descriptors2, matches);
	drawMatches(src1, kps1, src2, kps2, matches, dst1);
	
	imshow("dst1", dst1);
	imshow("dst",dst);
	waitKey(0);
	destroyAllWindows();
}