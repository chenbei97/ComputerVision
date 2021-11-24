#include "primary.h"
using namespace cv;
#include <vector>
void image_feature_extraction__TomasiCorner()
{
	/*
		����˹������
		det M = ��1 *  ��2 ;
		trace M =  ��1 +  ��2  ;
		R = det M - k (trace M)^2 ;
		
		����˹����
		ȡ R = min( ��1, ��2);

		void goodFeaturesToTrack( InputArray image, OutputArray corners,
									 int maxCorners, double qualityLevel, double minDistance,
									 InputArray mask = noArray(), int blockSize = 3,
									 bool useHarrisDetector = false, double k = 0.04 );
		corners�������������
		maxCorners�����ؽǵ����Ŀ��������������Ŀ�򷵻���Ӧֵ��ǿǰ�涨����Ŀ
		qualityLevel����ʾ�ɽ��ܵ���С����ֵ��1500��0.01��15
		minDistance�������ǵ�֮�����С����(L2)
		blockSize�����㵼��΢�ֲ�ͬ�Ĵ��ڴ�С

		void goodFeaturesToTrack( InputArray image, OutputArray corners,
                                     int maxCorners, double qualityLevel, double minDistance,
                                     InputArray mask, int blockSize,
                                     int gradientSize, bool useHarrisDetector = false,
                                     double k = 0.04 );
		gradientSize��
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
	int maxCorners = 100; // ����������صĽǵ���Ŀ,�㷨�������Ŀ����кֻܶ࣬Ҫ���صġ�������
	int blockSize = 3;
	int gradientSize = 3;
	bool useHarrisDetector = false;
	double k = 0.04;
	Mat mask = Mat();
	std::vector<Point2f > cornors;
	goodFeaturesToTrack(gray,cornors,maxCorners,qualityLevel,minDistance,
		mask,blockSize,useHarrisDetector,k);
	printf_s("�ǵ������Ϊ��%d",cornors.size());
	for (size_t i = 0; i < cornors.size(); i++)
	{
		circle(src,cornors[i],3,Scalar(0,0,255),2,8,0); //��ÿ���㻭Ȧ
	}
	imshow("src",src);
	waitKey(0);
	destroyAllWindows();
}