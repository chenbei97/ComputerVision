#include "primary.h"
using namespace cv;
void image_fixed_adaptive_threshold_segmentation()
{
	// �̶���ֵ
	enum types {THRESH_BINARY, THRESH_BINARY_INV, 
		THRESH_TRUNC, THRESH_TOZERO, THRESH_TOZERO_INV};
	std::vector<Mat>dsts(5);
	Mat src = imread(imgAddr + "lena.jpg");
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	for (int i = 0; i < dsts.size(); i++)
	{
		threshold(gray, dsts[i], 150,255,types(i));
		imshow("dst"+std::to_string(i+1),dsts[i]);
	}
	// ʹ������Ӧ��ֵ
	// ������ѡ2��,��ֵ����ֻ��ѡ��THRESH_BINARY, THRESH_BINARY_INV = 0 , 1
	enum  adaptive_methods { ADAPTIVE_THRESH_GAUSSIAN_C, ADAPTIVE_THRESH_MEAN_C}; // 0 , 1
	double C = 2; // �������и�˹��Ȩ�ͻ���ƽ���������ȥ�ó��� 
	const int maxval = 255;
	int blocksize = 11; // ������Сһ��ȡ����(>3),����������ƽ��ֵ���߸�˹��Ȩ������ȥ�ó���
	std::vector<Mat>adadsts(4);
	int count = 0;
	for (int method = 0; method < 2; method++)
	{
		for (int type = 0; type < 2; type++)
		{
			adaptiveThreshold(gray, adadsts[count], maxval,adaptive_methods(method),types(type),blocksize,C);
			imshow("adadst" + std::to_string(count + 1), adadsts[count]);
			count++;
		}
	}
	waitKey(0);
	destroyAllWindows();
}