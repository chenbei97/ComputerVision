#include "primary.h"
using namespace cv;
void image_edge_processing()
{
	/*
	BORDER_CONSTANT：常数填充边缘
	BORDER_DEFAULT：默认不填充
	BORDER_WRAP：使用另一边像素填充
	BORDER_REPLICATE：使用已知边缘像素填充
	给图像添加边缘：输入、输出、top、bottom、left、right、boardtype、scalar
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
	double fontscale = 1; // 字体大小
	putText(dst1,"original",Point(top,top),FONT_HERSHEY_COMPLEX,fontscale,Scalar(255,0,0),2);
	imshow("dst",dst1);
	waitKey(0);
}