#include "primary.h"
using namespace cv;
void image_histogram_equalization()
{
	// һ�����ͼ��Աȶȵķ���
	// ͨ��ֱ��ͼ����֪����ͬǿ�ȵ����ظ���,��߽ϵͺͽϸ�ǿ�����ص�����������߶Աȶ�
	Mat src = imread(imgAddr + "apple.jpg"), dst;
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);//Assertion failed (scn == 1 && dcn == 1)

	equalizeHist(gray,dst);// src.type() == CV_8UC1 8λ��ͨ���Ҷ�ͼ
	imshow("gray",gray);
	imshow("dst", dst);
	waitKey(0);
	destroyAllWindows();

}