#include "primary.h"
using namespace cv;
#include <vector>
void image_feature_detection_surf()
{
	/*
	ѡ��ͼ�����Ȥ�ĵ�->��ͬ�ĳ߶ȿռ䷢�ֹؼ���->
	�Ǽ���ֵ����->���������㷽������ת������Ҫ��->������������
	�м����������Ĥ��xx,yy,xy


	create(double hessianThreshold=100,
				  int nOctaves = 4, int nOctaveLayers = 3,
				  bool extended = false, bool upright = false);
	hessianThreshold��Ĭ��ֵ��300-500֮��
	nOctaves���߶ȿռ�(������)��Ŀ
	nOctaveLayers��ÿ���߶ȿռ�(������)����
	extended��
	upright����ʾ����ѡ�񲻱���,Ĭ�ϼ���,�ٶȸ���
	*/
	double hessianThreshold = 100;
	int nOctaves = 4;
	int nOctaveLayers = 3;
	bool extended = false;
	bool upright = false;
	Mat src = imread(imgAddr + "tajmahal.jpg"), gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	Ptr< xfeatures2d::SURF> detector =  // ����ֵ��Ptr< xfeatures2d::SURF>����
		xfeatures2d::SURF::create(hessianThreshold,nOctaves,nOctaveLayers,extended,upright);
	std::vector<KeyPoint> kps;
	detector->detect(src,kps,Mat()); // ���ؼ���
	std::cout << "kps.size() = " << kps.size()<<"   kps[0].pt = "<< kps[0].pt << std::endl;
	Mat kps_img;
	drawKeypoints(src,kps,kps_img,Scalar(0,0,255));
	for (size_t i = 0; i < kps.size(); i++)
	{
		if (i < 200) // ���л�Բ
		{
			Point2f center = kps[i].pt;
			circle(src,center,3,Scalar(255,0,0),2,8,0);
		}	
	}
	imshow("src",src);
	imshow("kps_img", kps_img); // ����API��Բ
	waitKey(0);
	destroyAllWindows();


}