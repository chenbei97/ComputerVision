#include "primary.h"
using namespace cv;
#include <vector>
void image_feature_detection_sift()
{
	/*
		�����߶ȿռ�Ѱ�Ҽ�ֵ->�ؼ��㶨λ(Ѱ�ҹؼ���λ����ɾ������Ե)->�ؼ��㷽��ָ��->�ؼ���������
		����ͼ���˹��������DOG��ÿһ�㷢��������Сֵ
		�����ĸ�˹������ÿһ�����sigma�Ĳ�ͬ���ٿ��Է�Ϊ4���ȼ�

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
	detector->detect(src, kps, Mat()); // ���ؼ���
	std::cout << "kps.size() = " << kps.size() << "   kps[0].pt = " << kps[0].pt << std::endl;
	Mat kps_img;
	drawKeypoints(src, kps, kps_img, Scalar(0, 0, 255));
	for (size_t i = 0; i < kps.size(); i++)
	{
		if (i <5000) // ���л�Բ
		{
			Point2f center = kps[i].pt;
			circle(src, center, 3, Scalar(255, 0, 0), 2, 8, 0);
		}
	}
	imshow("src", src);
	imshow("kps_img", kps_img); // ����API��Բ
	waitKey(0);
	destroyAllWindows();
}