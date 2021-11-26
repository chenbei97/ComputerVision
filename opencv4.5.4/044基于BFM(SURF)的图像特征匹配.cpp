#include "primary.h"
using namespace cv;
#include <vector>
void image_feature_match_bfm_surf()
{
	Mat src1 = imread(imgAddr + "goal1.png");
	Mat src2 = imread(imgAddr + "goal2.png");
	Mat dst;
	int minHessian = 400;
	Ptr<xfeatures2d::SURF> detector = xfeatures2d::SURF::create(minHessian);
	std::vector<KeyPoint> kps1,kps2;
	Mat descriptors1, descriptors2;
	detector->detectAndCompute(src1,Mat(),kps1, descriptors1);
	detector->detectAndCompute(src2, Mat(), kps2, descriptors2);
	BFMatcher matcher(NORM_L2);
	std::vector<DMatch> matches;
	matcher.match(descriptors1,descriptors2,matches);

	drawMatches(src1,kps1,src2,kps2,matches,dst);
	
	imshow("dst", dst);
	waitKey(0);
	destroyAllWindows();
}
