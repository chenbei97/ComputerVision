#include "primary.h"
using namespace cv;
void image_gradient_canny()
{
	Mat src = imread(imgAddr + "apple.jpg"), dst;
	// 内部原理：高斯模糊->灰度转换->计算梯度sobel/scharr->非极大值抑制->高低阈值输出二值图像
	// Gx=[-1,0,1][-2,0,2][-1,0,1]、Gy=[-1,-2,-1][0,0,0][1,2,1]
	// Gz= sqrt(Gx^2+Gy^2)
	// theta = arctan(Gy/Gx)
	/*
      根据角度的取值规定为
	  黄色区域：0~22.5°/157.5°~180°
	  绿色区域：22.5~67.5°
	  黄色区域：67.5~112.5°
	  红色区域：112.5~157.5°
	
	像素检测规则：T1和T2为阈值，高于T2的都保留，低于T1的都丢弃
	高于T1的像素还要进一步取舍，与T2相关联的像素被保留，其他舍弃
	高低阈值比为3比1或者2比1
	canny API： src、dst、min、max、梯度算子的核大小一般取3、是否用L2归一化(否则L1归一化)
	*/
	double min, max;
	int ksize = 3;
	bool isL2 = false; // 一般L1
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