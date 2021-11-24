#include "primary.h"
using namespace cv;
#include <vector>
void image_feature_detection_surf()
{
	/*
	选择图像感兴趣的点->不同的尺度空间发现关键点->
	非极大值抑制->发现特征点方法、旋转不变性要求->生成特征向量
	有几个方向的掩膜，xx,yy,xy


	create(double hessianThreshold=100,
				  int nOctaves = 4, int nOctaveLayers = 3,
				  bool extended = false, bool upright = false);
	hessianThreshold：默认值在300-500之间
	nOctaves：尺度空间(金字塔)数目
	nOctaveLayers：每个尺度空间(金字塔)层数
	extended：
	upright：表示计算选择不变形,默认计算,速度更慢
	*/
	double hessianThreshold = 100;
	int nOctaves = 4;
	int nOctaveLayers = 3;
	bool extended = false;
	bool upright = false;
	Mat src = imread(imgAddr + "tajmahal.jpg"), gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	Ptr< xfeatures2d::SURF> detector =  // 返回值是Ptr< xfeatures2d::SURF>类型
		xfeatures2d::SURF::create(hessianThreshold,nOctaves,nOctaveLayers,extended,upright);
	std::vector<KeyPoint> kps;
	detector->detect(src,kps,Mat()); // 检测关键点
	std::cout << "kps.size() = " << kps.size()<<"   kps[0].pt = "<< kps[0].pt << std::endl;
	Mat kps_img;
	drawKeypoints(src,kps,kps_img,Scalar(0,0,255));
	for (size_t i = 0; i < kps.size(); i++)
	{
		if (i < 200) // 自行画圆
		{
			Point2f center = kps[i].pt;
			circle(src,center,3,Scalar(255,0,0),2,8,0);
		}	
	}
	imshow("src",src);
	imshow("kps_img", kps_img); // 利用API画圆
	waitKey(0);
	destroyAllWindows();


}