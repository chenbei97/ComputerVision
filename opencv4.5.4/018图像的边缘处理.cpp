#include "primary.h"
using namespace cv;
void image_edge_processing()
{
	/*
	BORDER_CONSTANT����������Ե
	BORDER_DEFAULT��Ĭ�ϲ����
	BORDER_WRAP��ʹ����һ���������
	BORDER_REPLICATE��ʹ����֪��Ե�������
	��ͼ����ӱ�Ե�����롢�����top��bottom��left��right��boardtype��scalar
	*/
	Mat src = imread(imgAddr + "apple.jpg"), dst1, dst2;
	int top=(int) src.rows * 0.05, bottom= src.rows * 0.05, left=(int)src.cols * 0.05, right= (int)src.cols * 0.05;
	int boardtype = BORDER_REPLICATE; // BORDER_DEFAULT =4
	std::cout << "BORDER_DEFAULT = " << boardtype << std::endl; // =1
	RNG rng;
	Scalar color(rng.uniform(0,255), rng.uniform(0, 255), rng.uniform(0, 255));
	copyMakeBorder(src,dst1,top,bottom,left,right,boardtype,color);
	imshow("src",src);
	Rect rect(Point(top,top),Point(src.cols,src.rows));
	rectangle(dst1,rect,Scalar(0,0,255),2);
	double fontscale = 1; // �����С
	putText(dst1,"original",Point(top,top),FONT_HERSHEY_COMPLEX,fontscale,Scalar(255,0,0),2);
	imshow("dst",dst1);
	waitKey(0);
}