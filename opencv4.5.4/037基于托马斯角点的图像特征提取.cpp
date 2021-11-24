#include "primary.h"
using namespace cv;
#include <vector>
void image_feature_extraction__TomasiCorner()
{
	/*
		哈里斯法计算
		det M = λ1 *  λ2 ;
		trace M =  λ1 +  λ2  ;
		R = det M - k (trace M)^2 ;
		
		托马斯法：
		取 R = min( λ1, λ2);

		void goodFeaturesToTrack( InputArray image, OutputArray corners,
									 int maxCorners, double qualityLevel, double minDistance,
									 InputArray mask = noArray(), int blockSize = 3,
									 bool useHarrisDetector = false, double k = 0.04 );
		corners：点坐标的容器
		maxCorners：返回角点的数目，如果大于最大数目则返回响应值最强前规定的数目
		qualityLevel：表示可接受的最小向量值，1500、0.01、15
		minDistance：两个角点之间的最小距离(L2)
		blockSize：计算导数微分不同的窗口大小

		void goodFeaturesToTrack( InputArray image, OutputArray corners,
                                     int maxCorners, double qualityLevel, double minDistance,
                                     InputArray mask, int blockSize,
                                     int gradientSize, bool useHarrisDetector = false,
                                     double k = 0.04 );
		gradientSize：
		void goodFeaturesToTrack(
			InputArray image, OutputArray corners,
			int maxCorners, double qualityLevel, double minDistance,
			InputArray mask, OutputArray cornersQuality, int blockSize = 3,
			int gradientSize = 3, bool useHarrisDetector = false, double k = 0.04);
	*/
	Mat src = imread(imgAddr + "tajmahal.jpg"),gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	double qualityLevel=0.01;
	double minDistance=10;
	int maxCorners = 100; // 调整这个返回的角点数目,算法检测出来的可能有很多，只要返回的≤它即可
	int blockSize = 3;
	int gradientSize = 3;
	bool useHarrisDetector = false;
	double k = 0.04;
	Mat mask = Mat();
	std::vector<Point2f > cornors;
	goodFeaturesToTrack(gray,cornors,maxCorners,qualityLevel,minDistance,
		mask,blockSize,useHarrisDetector,k);
	printf_s("角点的数量为：%d",cornors.size());
	for (size_t i = 0; i < cornors.size(); i++)
	{
		circle(src,cornors[i],3,Scalar(0,0,255),2,8,0); //给每个点画圈
	}
	imshow("src",src);
	waitKey(0);
	destroyAllWindows();
}