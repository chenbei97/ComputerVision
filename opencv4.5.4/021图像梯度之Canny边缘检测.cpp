#include "primary.h"
using namespace cv;
void image_gradient_canny()
{
	Mat src = imread(imgAddr + "apple.jpg"), dst;
	// �ڲ�ԭ����˹ģ��->�Ҷ�ת��->�����ݶ�sobel/scharr->�Ǽ���ֵ����->�ߵ���ֵ�����ֵͼ��
	// Gx=[-1,0,1][-2,0,2][-1,0,1]��Gy=[-1,-2,-1][0,0,0][1,2,1]
	// Gz= sqrt(Gx^2+Gy^2)
	// theta = arctan(Gy/Gx)
	/*
      ���ݽǶȵ�ȡֵ�涨Ϊ
	  ��ɫ����0~22.5��/157.5��~180��
	  ��ɫ����22.5~67.5��
	  ��ɫ����67.5~112.5��
	  ��ɫ����112.5~157.5��
	
	���ؼ�����T1��T2Ϊ��ֵ������T2�Ķ�����������T1�Ķ�����
	����T1�����ػ�Ҫ��һ��ȡ�ᣬ��T2����������ر���������������
	�ߵ���ֵ��Ϊ3��1����2��1
	canny API�� src��dst��min��max���ݶ����ӵĺ˴�Сһ��ȡ3���Ƿ���L2��һ��(����L1��һ��)
	*/
	double min, max;
	int ksize = 3;
	bool isL2 = false; // һ��L1
	GaussianBlur(src, src, Size(3, 3), 1.0, 0.0, 4);
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	max = threshold(gray, dst, 0, 255, THRESH_OTSU);
	std::cout << "threshold = " << max << std::endl; // threshold = 114
	Mat dst1 = dst.clone();
	min = (int) max / 2;
	Canny(gray,dst1,min,max,ksize,isL2);
	imshow("dst",dst1);
	waitKey(0);
	destroyAllWindows();



}